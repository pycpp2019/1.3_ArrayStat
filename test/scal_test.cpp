#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>
//#include <thread>
//#include <chrono>

#include <cstdlib>
#include <cmath>

#include "rng.hh"
#include "hash.hh"
#include "parse.hh"

#include <ArrayStat.h>


#define EPS 1e-4

bool f_eq(double a, double b, double eps=EPS) {
    return fabs(a - b) < eps;
}

class TempFile {
private:
    std::string path;
public:
    TempFile(std::string path) {
        this->path = path;
    }
    ~TempFile() {
        std::remove(this->path.c_str());
    }
    const char *name() {
        return this->path.c_str();
    }
};

class Redir {
private:
    std::ostringstream stream;
    std::streambuf *stdoutbuf;
public:
    Redir() {
        this->stdoutbuf = std::cout.rdbuf(this->stream.rdbuf());
    }
    ~Redir() {
        std::cout.rdbuf(this->stdoutbuf);
    }
    std::string content() {
        return this->stream.str();
    }
};

std::string write_file(const std::vector<int> &data) {
    std::stringstream ss;
    std::hash<std::vector<int>> hasher;
    ss << "test/array_" << std::hex << hasher(data) << ".txt";

    std::ofstream file;
    file.open(ss.str(), std::ios::out | std::ios::trunc);

    file << data.size() << std::endl;
    for (int v : data) {
        file << v << " ";
    }
    file << std::endl;

    file.close();

    return ss.str();
}

std::vector<int> make_array(Rng *rng,int size, int begin, int end) {
    std::vector<int> v;
    v.resize(size);
    for (int i = 0; i < size; ++i) {
        v[i] = (rng->rand_int() % (end - begin)) + begin;
    }
    return v;
}

template <typename F>
void add_files_test(
    std::vector<std::pair<std::string, std::function<bool(Rng*)>>> *tests,
    std::string prefix, F test_func
) {
    tests->push_back(
        make_pair(prefix + std::string("_empty"), [&](Rng *rng) -> bool {
            std::vector<int> data = std::vector<int>();
            TempFile tfile(write_file(data));
            return test_func(&data, tfile.name(), rng);
        })
    );

    tests->push_back(
        make_pair(prefix + std::string("_one"), [&](Rng *rng) -> bool {
            std::vector<int> data = make_array(rng, 1, -5, 10);
            TempFile tfile(write_file(data));
            return test_func(&data, tfile.name(), rng);
        })
    );

    tests->push_back(
        make_pair(prefix + std::string("_100"), [&](Rng *rng) -> bool {
            std::vector<int> data = make_array(rng, 100, -500, 1000);
            TempFile tfile(write_file(data));
            return test_func(&data, tfile.name(), rng);
        })
    );

    tests->push_back(
        make_pair(prefix + std::string("_million"), [&](Rng *rng) -> bool {
            std::vector<int> data = make_array(rng, 1000000, -50000000, 100000000);
            TempFile tfile(write_file(data));
            return test_func(&data, tfile.name(), rng);
        })
    );
}


int main() {
    std::vector<std::pair<std::string, std::function<bool(Rng*)>>> tests = {
        make_pair(std::string("exception"), [](Rng *rng) -> bool {
            try {
                ArrayStat stat("out/nonexistent.txt");
            } catch (...) {
                return true;
            }
            return false;
        }),
    };
    add_files_test(&tests, "constructor", [](
        std::vector<int> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);
        return true;
    });
    add_files_test(&tests, "print", [](
        std::vector<int> *data, const char *fname, Rng *rng
    ) -> bool {
        std::string output;
        
        {
            Redir redir;

            ArrayStat stat(fname);
            stat.print();

            output = redir.content();
        }

        std::sort(data->begin(), data->end());
        std::vector<int> parsed = parse_int(output);

        if (data->size() != parsed.size()) {
            return false;
        }
        for (int i = 0; i < data->size(); ++i) {
            if ((*data)[i] != parsed[i]) {
                return false;
            }
        }

        return true;
    });
    add_files_test(&tests, "min_max", [](
        std::vector<int> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);

        if (data->size() <= 0) {
            try {
                stat.min();
            } catch (...) {
                try {
                    stat.max();
                } catch (...) {
                    return true;
                }
            }
            return false;
        }

        int min = *std::min_element(data->begin(), data->end());
        int max = *std::max_element(data->begin(), data->end());

        if (stat.min() != min || stat.max() != max) {
            return false;
        }

        return true;
    });
    add_files_test(&tests, "mean", [](
        std::vector<int> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);

        if (data->size() <= 0) {
            try {
                stat.mean();
            } catch (...) {
                return true;
            }
            return false;
        }

        double mean = 0.0;
        for (int x : *data) {
            mean += x;
        }
        mean /= data->size();

        if (!f_eq(stat.mean(), mean)) {
            return false;
        }

        return true;
    });
    add_files_test(&tests, "rms", [](
        std::vector<int> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);

        if (data->size() <= 1) {
            try {
                stat.rms();
            } catch (...) {
                return true;
            }
            return false;
        }

        double mean = 0.0;
        for (int x : *data) {
            mean += x;
        }
        mean /= data->size();

        if (!f_eq(stat.mean(), mean)) {
            return false;
        }

        double rms = 0.0;
        for (int x : *data) {
            rms += (x - mean)*(x - mean);
        }
        rms = sqrt(rms/(data->size() - 1));

        if (!f_eq(stat.rms(), rms)) {
            return false;
        }

        return true;
    });
    add_files_test(&tests, "count_larger", [](
        std::vector<int> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);

        std::sort(data->begin(), data->end());

        int lval = 0;
        int lcnt = 0;
        for (int j = 0; j < data->size(); ++j) {
            int i = data->size() - j - 1;
            int val = (*data)[i];
            if (j == 0 || lval != val) {
                lval = val;
                lcnt = j;
            }
            if (stat.countLarger(val) != lcnt) {
                return false;
            }
            
            if (j != 0) {
                int diff = (*data)[i + 1] - val;
                if (diff >= 2) {
                    if (stat.countLarger(val + diff/2) != lcnt) {
                        return false;
                    }
                }
            }
        }

        return true;
    });

    /*
    volatile bool done = false;
    int test_timeout = 60; //seconds
    std::thread timer([&]() {
        for (int i = 0; i < test_timeout; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (done) {
                return;
            }
        }
        std::cerr << std::endl << "[error] test execution time exceeded" << std::endl;
        std::cerr << "maybe you should try to use faster algorithms" << std::endl << std::flush;
        exit(1);
    });
    */

    Rng rng(0xDEADBEEF);

    int total = tests.size();
    int failed = 0;
    int counter = 0;

    for (std::pair<std::string, std::function<bool(Rng*)>> &pair : tests) {
        std::cout << "(" << counter << "/" << total << ") ";
        std::cout << pair.first << " ... " << std::flush;

        bool ok;
        try {
            ok = pair.second(&rng);
        } catch (...) {
            ok = false;
            std::cout << "unexpected exception caught" << std::endl;
        }

        if (ok) {
            std::cout << "ok";
        } else {
            failed += 1;
            std::cout << "fail";
        }
        std::cout << std::endl;
        counter += 1;
    }

    int ret = 0;
    std::cout << "result: ";
    if (failed > 0) {
        std::cout << "fail";
        ret = 1;
    } else {
        std::cout << "ok";
    }
    std::cout << ". " << total - failed << " passed, " << failed << " failed." << std::endl;
    
    //done = true;
    //timer.join();

    return ret;
}

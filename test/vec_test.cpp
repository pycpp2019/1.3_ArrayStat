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

#include <VecArrayStat.h>


#define EPS 1e-6

bool f_eq(double a, double b, double eps=EPS) {
    return fabs(a - b) < eps;
}

#define REPS 1e-4

bool f_req(double a, double b, double reps=REPS) {
    double aa = fabs(a), ab = fabs(b);
    return (aa < 1e-8 && ab < 1e-8) || 2.0*fabs(a - b)/(aa + ab) < reps;
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

std::string write_file(const std::vector<Vec3> &data) {
    std::stringstream ss;
    std::hash<std::vector<Vec3>> hasher;
    ss << "test/vec_array_" << std::hex << hasher(data) << ".txt";

    std::ofstream file;
    file.open(ss.str(), std::ios::out | std::ios::trunc);

    file << data.size() << std::endl;
    for (Vec3 v : data) {
        file << v.x << " " << v.y << " " << v.z << std::endl;
    }

    file.close();

    return ss.str();
}

std::vector<Vec3> make_array(Rng *rng, int size, double mean, double var) {
    std::vector<Vec3> v;
    v.resize(size);
    for (int i = 0; i < size; ++i) {
        int vv[3];
        for (int j = 0; j < 3; ++j) {
            vv[j] = int(var*rng->normal() + mean);
        }
        v[i] = Vec3(vv[0], vv[1], vv[2]);
    }
    return v;
}

std::vector<double> map_norm(const std::vector<Vec3> &data) {
    std::vector<double> ns;
    ns.resize(data.size());
    for (int i = 0; i < data.size(); ++i) {
        ns[i] = data[i].norm();
    }
    return ns;
} 

template <typename F>
void add_files_test(
    std::vector<std::pair<std::string, std::function<bool(Rng*)>>> *tests,
    std::string prefix, F test_func
) {
    tests->push_back(
        make_pair(prefix + std::string("_empty"), [&](Rng *rng) -> bool {
            std::vector<Vec3> data;
            TempFile tfile(write_file(data));
            std::vector<double> ndata;
            return test_func(&ndata, tfile.name(), rng);
        })
    );

    tests->push_back(
        make_pair(prefix + std::string("_100"), [&](Rng *rng) -> bool {
            std::vector<Vec3> data = make_array(rng, 100, 0.0, 1e4);
            TempFile tfile(write_file(data));
            std::vector<double> ndata = map_norm(data);
            return test_func(&ndata, tfile.name(), rng);
        })
    );

    tests->push_back(
        make_pair(prefix + std::string("_million"), [&](Rng *rng) -> bool {
            std::vector<Vec3> data = make_array(rng, 1000000, 0.0, 1e8);
            TempFile tfile(write_file(data));
            std::vector<double> ndata = map_norm(data);
            return test_func(&ndata, tfile.name(), rng);
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
        std::vector<double> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);
        return true;
    });
    add_files_test(&tests, "print", [](
        std::vector<double> *data, const char *fname, Rng *rng
    ) -> bool {
        std::string output;
        
        {
            Redir redir;

            ArrayStat stat(fname);
            stat.print();

            output = redir.content();
        }

        std::sort(data->begin(), data->end());
        std::vector<double> parsed = parse_double(output);

        if (data->size() != parsed.size()) {
            return false;
        }
        for (int i = 0; i < data->size(); ++i) {
            if (!f_req((*data)[i], parsed[i])) {
                return false;
            }
        }

        return true;
    });
    add_files_test(&tests, "min_max", [](
        std::vector<double> *data, const char *fname, Rng *rng
    ) -> bool {
        if (data->size() <= 0) {
            return true;
        }

        double min = *std::min_element(data->begin(), data->end());
        double max = *std::max_element(data->begin(), data->end());

        ArrayStat stat(fname);

        if (!f_eq(stat.min(), min) || !f_eq(stat.max(), max)) {
            return false;
        }

        return true;
    });
    add_files_test(&tests, "mean_rms", [](
        std::vector<double> *data, const char *fname, Rng *rng
    ) -> bool {
        if (data->size() <= 0) {
            return true;
        }

        double mean = 0.0;
        double rms = 0.0;
        for (double x : *data) {
            mean += x;
            rms += double(x)*double(x);
        }
        mean /= data->size();
        rms = sqrt(rms/data->size());

        ArrayStat stat(fname);

        if (!f_eq(stat.mean(), mean)) {
            return false;
        }
        if (!f_eq(stat.rms(), rms)) {
            return false;
        }

        return true;
    });
    add_files_test(&tests, "count_larger", [](
        std::vector<double> *data, const char *fname, Rng *rng
    ) -> bool {
        ArrayStat stat(fname);

        std::sort(data->begin(), data->end());

        double lval = 0;
        int lcnt = 0;
        for (int j = 0; j < data->size(); ++j) {
            int i = data->size() - j - 1;
            double val = (*data)[i];
            if (j == 0 || lval != val) {
                lval = val;
                lcnt = j;
            }
            if (stat.countLarger(val) != lcnt) {
                return false;
            }
            
            if (j != 0) {
                double diff = (*data)[i + 1] - val;
                if (diff >= EPS) {
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

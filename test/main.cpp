#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>

#include <cstdlib>
#include <cmath>

#include "rng.hh"
#include "hash.hh"
#include "parse.hh"

#include <ArrayStat.h>


static const int N_TRIES = 16; 

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

int main() {
    std::vector<std::pair<std::string, std::function<bool(Rng*)>>> tests = {
        make_pair(std::string("constructor"), [](Rng *rng) -> bool {
            std::vector<int> data = make_array(rng, 10, 0, 100);
            TempFile tfile(write_file(data));
            {
                ArrayStat stat(tfile.name());
            }
            return true;
        }),

        make_pair(std::string("constructor_empty"), [](Rng *rng) -> bool {
            TempFile tfile(write_file(std::vector<int>()));
            {
                ArrayStat stat(tfile.name());
            }
            return true;
        }),

        make_pair(std::string("exception"), [](Rng *rng) -> bool {
            try {
                ArrayStat stat("out/nonexistent.txt");
            } catch (...) {
                return true;
            }
            return false;
        }),

        make_pair(std::string("print"), [](Rng *rng) -> bool {
            std::vector<int> data = make_array(rng, 100, -1000, 1001);
            TempFile tfile(write_file(data));
            std::string output;
            
            {
                Redir redir;

                ArrayStat stat(tfile.name());
                stat.print();

                output = redir.content();
            }

            std::sort(data.begin(), data.end());
            std::vector<int> parsed = parse_int(output);

            if (data.size() != parsed.size()) {
                return false;
            }
            for (int i = 0; i < data.size(); ++i) {
                if (data[i] != parsed[i]) {
                    return false;
                }
            }

            return true;
        }),

        make_pair(std::string("print_empty"), [](Rng *rng) -> bool {
            TempFile tfile(write_file(std::vector<int>()));
            std::string output;
            
            {
                Redir redir;

                ArrayStat stat(tfile.name());
                stat.print();

                output = redir.content();
            }

            std::vector<int> parsed = parse_int(output);

            if (parsed.size() != 0) {
                return false;
            }

            return true;
        }),

        make_pair(std::string("print_many"), [](Rng *rng) -> bool {
            std::vector<int> data = make_array(rng, 1000000, -100000000, 100000001);
            TempFile tfile(write_file(data));
            std::string output;
            
            {
                Redir redir;

                ArrayStat stat(tfile.name());
                stat.print();

                output = redir.content();
            }

            std::sort(data.begin(), data.end());
            std::vector<int> parsed = parse_int(output);

            if (data.size() != parsed.size()) {
                return false;
            }
            for (int i = 0; i < data.size(); ++i) {
                if (data[i] != parsed[i]) {
                    return false;
                }
            }

            return true;
        }),
    };

    Rng rng(0xDEADBEEF);

    int total = tests.size();
    int failed = 0;
    int counter = 0;

    for (std::pair<std::string, std::function<bool(Rng*)>> &pair : tests) {
        bool ok;
        try {
            ok = pair.second(&rng);
        } catch (...) {
            ok = false;
            std::cout << "unexpected exception caught" << std::endl;
        }

        if (ok) {
            std::cout << "[ok]";
        } else {
            failed += 1;
            std::cout << "[fail]";
        }
        std::cout << " (" << counter << "/" << total << ") ";
        std::cout << pair.first << std::endl;
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
    
    return ret;
}

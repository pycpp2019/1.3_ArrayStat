#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <utility>

#include <cstdlib>
#include <cmath>

#include "rng.hh"

#include <ArrayStat.h>

using namespace std;


#define EPS 1e-8

static const int N_TRIES = 16; 

void replace_other(string *str, const char *srcs, char dst) {
    for (int i = 0; i < str->size(); ++i) {
        bool found = false;
        for (int j = 0; srcs[j] != '\0'; ++j) {
            if ((*str)[i] == srcs[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            (*str)[i] = dst;
        }
    }
}

vector<int> parse(string str) {
    vector<int> nums;
    int b = -1;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            if (b < 0) {
                b = i;
            }
        } else {
            if (b >= 0) {
                nums.push_back(atoi(str.substr(b, i - b).c_str()));
                b = -1;
            }
        }
    }
    if (b >= 0) {
        nums.push_back(atoi(str.substr(b, str.size() - b).c_str()));
    }
    return nums;
}

int main() {
    vector<pair<string, function<bool(Rng*)>>> tests = {

        make_pair(string("constructor"), [](Rng *rng) -> bool {
            ArrayStat as("test.txt");
            return true;
        }),

        make_pair(string("print"), [](Rng *rng) -> bool {
            ArrayStat as("test.txt");
            return true;
        }),

    };

    Rng rng(0xDEADBEEF);

    int total = tests.size();
    int failed = 0;
    int counter = 0;

    for (pair<string, function<bool(Rng*)>> &pair : tests) {
        if (pair.second(&rng)) {
            cout << "[ok]";
        } else {
            failed += 1;
            cout << "[fail]";
        }
        cout << " (" << counter << "/" << total << ") ";
        cout << pair.first << endl;
        counter += 1;
    }

    int ret = 0;
    cout << "result: ";
    if (failed > 0) {
        cout << "fail";
        ret = 1;
    } else {
        cout << "ok";
    }
    cout << ". " << total - failed << " passed, " << failed << " failed." << endl;
    
    return ret;
}

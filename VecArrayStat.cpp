#include "VecArrayStat.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <numeric>

ArrayStat::ArrayStat(const char *file_name) {
    ifstream file(file_name);
    if (!file) throw invalid_argument("File does not open.");
    file >> n;
    dat.resize(n);
    bdat.resize(n);
    for (int i = 0; i < n; ++i) {
        dat[i].resize(3);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            if (!file.eof()) {
                file >> dat[i][j];
            } else {
                throw std::invalid_argument("Unexpected EOF.");
            }
        }
    }
    for (int i = 0; i < n; i++) {
        bdat[i] = sqrt(dat[i][0]*dat[i][0] + dat[i][1]*dat[i][1] + dat[i][2]*dat[i][2]);
    }
    sort(bdat.begin(), bdat.end());
}
double ArrayStat::max() const {
    if (n == 0) throw invalid_argument("Count of array is not enough for work");
    return bdat[n - 1];
}
double ArrayStat::min() const {
    if (n == 0) throw invalid_argument("Count of array is not enough for work");
    return bdat[0];
}
double ArrayStat::mean() const {
    if (n == 0) throw invalid_argument("Count of array is not enough for work");
    return accumulate(bdat.begin(), bdat.end(), 0.)/n;
}
double ArrayStat::rms() const {
    if ((n == 0) || (n == 1)) throw invalid_argument("Count of array is not enough for work");
    double m = mean();
    return sqrt(accumulate(bdat.begin(), bdat.end(), 0., [m](double a, double x) {
        return a + pow(x - m, 2);
    })/(n - 1));
}
size_t ArrayStat::countLarger(double a) const {
    return bdat.end() - upper_bound(bdat.begin(), bdat.end(), a);
}
void ArrayStat::print() const {
    for (int i = 0; i < n; i++) {
        cout << bdat[i] << " ";
    }
    cout << endl;
}

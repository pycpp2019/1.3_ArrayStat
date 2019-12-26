#include "ArrayStat.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <cmath>

ArrayStat::ArrayStat(const char *file_name) {
    std::ifstream file(file_name);
    if (!file) throw std::invalid_argument("File does not open.");
    file >> count;
    data.resize(count);
    for (int i = 0; i < count; i++) {
        if (!file.eof()) {
            file >> data[i];
        } else {
            throw std::invalid_argument("Unexpected EOF.");
        }
    }
    std::sort(data.begin(), data.end());
}

int ArrayStat::max() const {
    if (count == 0) throw std::invalid_argument("Count of array is not enough for work");
    return data[count - 1];
}
int ArrayStat::min() const {
    if (count == 0) throw std::invalid_argument("Count of array is not enough for work");
    return data[0];
}
double ArrayStat::mean() const {
    if (count == 0) throw std::invalid_argument("Count of array is not enough for work");
    return accumulate(data.begin(), data.end(), 0.)/count;
}
double ArrayStat::rms() const {
    if ((count == 0) || (count == 1)) throw std::invalid_argument("Count of array is not enough for work");
    double m = mean();
    return sqrt(accumulate(data.begin(), data.end(), 0., [m](double a, int x) {
        return a + pow(x - m, 2);
    })/(count - 1));
}
size_t ArrayStat::countLarger(int a) const {
    return data.end() - std::upper_bound(data.begin(), data.end(), a);
}
void ArrayStat::print() const {
    for (int i = 0; i < count; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

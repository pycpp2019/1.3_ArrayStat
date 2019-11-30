#pragma once

#include <cstdlib>
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <fstream>

class ArrayStat {
    int n;
    std::vector<double> m;
public:
    ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double a) const;
    void print() const;
};

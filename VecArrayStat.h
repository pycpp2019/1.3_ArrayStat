#pragma once

#include <cstdlib>
#include <vector>

class ArrayStat {
    int N;
    std::vector<double> array;
public:
    ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double a) const;
    void print() const;
};

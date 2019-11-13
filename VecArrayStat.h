#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>


class ArrayStat {
    std::vector<double> Array;

public:
    ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double a) const;
    void print() const;
};

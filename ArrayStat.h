#pragma once
#include <cstdlib>
#include "fstream"
#include <stdexcept>
#include <vector>

class ArrayStat {
    int count;
    std::vector<int> data;
public:
    ArrayStat(const char *file_name);
    int max() const;
    int min() const;
    double mean() const;
    double rms() const;
    size_t countLarger(int a) const;
    void print() const;
};

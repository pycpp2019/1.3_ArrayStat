#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>

class ArrayStat {
std::vector<int> Array;
public:
    ArrayStat(const char *file_name);

    int max() const;
    int min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(int a) const;
    void print() const;
};

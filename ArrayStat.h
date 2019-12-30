#pragma once

#include <cstdlib>
#include <vector>


class ArrayStat {
    int N;
    std::vector<int> array;
public:
    ArrayStat(const char *file_name);

    int max() const;
    int min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(int a) const;
    void print() const;
};

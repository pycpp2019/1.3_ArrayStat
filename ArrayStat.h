#pragma once

#include <cstdlib>
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <fstream>
struct square
{
    int operator()(const int& Left, const int& Right) const;
};

struct one
{
    int operator()(const int& Left, const int& Right) const;
};


class ArrayStat {
    int n;
    std::multiset<int> m;
public:
    ArrayStat(const char *file_name);

    int max() const;
    int min() const;

    float mean() const;
    float rms() const;

    size_t countLarger(int a) const;
    void print() const;
};

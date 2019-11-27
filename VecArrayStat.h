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
    double operator()(const double& Left, const double& Right) const;
};




class ArrayStat {
    int n;
    std::multiset<float> m;
public:
    ArrayStat(const char *file_name);

    float max() const;
    float min() const;

    float mean() const;
    float rms() const;

    size_t countLarger(int a) const;
    void print() const;
};

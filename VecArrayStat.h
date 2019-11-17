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

struct one
{
    double operator()(const double& Left, const double& Right) const;
};


class ArrayStat {
    int n;
    std::multiset<double> m;
public:
    ArrayStat(const char *file_name);

    int max() const;
    int min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(int a) const;
    void print() const;
};

#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>



class ArrayStat 
{
private:
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

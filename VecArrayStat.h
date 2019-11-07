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
	std::vector<std::vector<double>> data;
	std::vector<double> len;	
public:
    ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double a) const;
    void print() const;
};

#pragma once
#include <set>
#include <cstdlib>
#include <vector>


class ArrayStat {
private:
	std::vector<double> myset;
public:
    ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double key) const;

    void print() const;
};

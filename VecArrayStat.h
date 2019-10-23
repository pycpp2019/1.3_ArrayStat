#pragma once

#include <cstdlib>
#include <vector>


class ArrayStat {
private:
	std::vector<double> sorted;
public:
    explicit ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double el) const;
    void print() const;
};

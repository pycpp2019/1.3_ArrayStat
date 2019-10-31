#pragma once
#include <set>
#include <cstdlib>


class ArrayStat {
private:
	std::multiset<int> myset;
public:
    ArrayStat(const char *file_name);

    int max() const;
    int min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(int key) const;
    void print() const;
};

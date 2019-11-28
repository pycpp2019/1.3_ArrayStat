#pragma once

#include <cstdlib>
#include <vector>

using namespace std;

class ArrayStat {
private:
    vector<int> arr;
public:
    ArrayStat(const char *file_name);

    int max() const;
    int min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(int a) const;
    void print() const;
};

#include <cstdlib>
#include <iostream>
#include <vector>
#include <exception>
#include <string>
using namespace std;
class ArrayStat {
public:
    ArrayStat(const char *file_name);
    double max() const;
    double min() const;
    double mean() const;
    double rms() const;
    size_t countLarger(double a) const;
    void print() const;
 private:
    vector<double> arr;
};
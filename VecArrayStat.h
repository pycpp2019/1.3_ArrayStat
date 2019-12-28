#include <cstdlib>
#include "fstream"
#include <stdexcept>
#include <vector>

using namespace std;

class ArrayStat {
    int n;
    vector<vector<double> > dat;
    vector<double> bdat;
public:
    ArrayStat(const char *file_name);
    double max() const;
    double min() const;
    double mean() const;
    double rms() const;
    size_t countLarger(double a) const;
    void print() const;
};

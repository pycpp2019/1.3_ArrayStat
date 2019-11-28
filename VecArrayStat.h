#include <cstdlib>
#include <vector>

using namespace std;

class ArrayStat {
private:
    vector<double> vector;
public:
    ArrayStat(const char *file_name);

    double max() const;
    double min() const;

    double mean() const;
    double rms() const;

    size_t countLarger(double a) const;
    void print() const;
};

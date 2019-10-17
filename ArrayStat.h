#include <iostream>
#include <vector>
using namespace std;
class ArrayStat
{
    public:
        int max();
        int min();
        double mean();
        double rms();
        size_t countLarger(int a);
        ArrayStat(const char * name);
        void print();
    private:
    vector<int> arr;
};
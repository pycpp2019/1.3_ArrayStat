#include <iostream>
#include <vector>
#include <exception>
#include<string>
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
/*
class Exception:exception{
    public:
    string msg;
    Exception (const char *msg);
};
*/

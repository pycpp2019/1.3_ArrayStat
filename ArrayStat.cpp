#include "ArrayStat.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;


ArrayStat::ArrayStat(const char *file_name){
    fstream file;
    file.open(file_name, fstream::in);
    if (!file.is_open()){
        throw exception();
    };
    file >> N;
    
    array.resize(N, 1);
    for (int i = 0; i < N; i++){
        file >> array[i];
    };
    file.close();
    sort(array.begin(), array.end());
};

int ArrayStat::max() const{
    if (N <= 0){
        throw exception();
    };
    return array[N - 1];
};

int ArrayStat::min() const{
    if (N <= 0){
        throw exception();
    };
    return array[0];
};

double ArrayStat::mean() const{
    if (N <= 0){
        throw exception();
    }
    else{
        double mean = accumulate(array.begin(), array.end(), 0.0) / N;
        return mean;
    };
};

double ArrayStat::rms() const{
    if (this->array.empty())
        throw exception();
    if (this->array.size() == 1)
        throw exception();
    double avg = mean();
    double rms;
    double res = accumulate(array.begin(), array.end(), 0.0, [avg](double a, int element){
        return (a + (element - avg) * (element - avg));});
    rms = sqrt(res / (N - 1));
};

size_t ArrayStat::countLarger(int a) const{
    return array.end() - upper_bound(array.begin(), array.end(), a);
};

void ArrayStat::print() const{
	for (int i = 0; i < array.size(); i++)
   	{
       	cout << array[i] << " ";
    };
};
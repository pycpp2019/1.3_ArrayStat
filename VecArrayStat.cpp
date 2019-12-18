#include "VecArrayStat.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cstdlib>

using namespace std;

ArrayStat::ArrayStat(const char *file_name){
    fstream file;
    if (!file){
        throw exception();
    };
    file.open(file_name, fstream::in);
    file >> N;
    
    array.resize(N, 1);
    double a, b, c;
    for (int i = 0; i < N; i++){
        file >> a >> b >> c;
        array[i] = sqrt(a * a + b * b + c * c);
    };
    file.close();
    sort(array.begin(), array.end());
};

double ArrayStat::max() const{
    if (N <= 0){
        throw exception();
    };
    return array[N - 1];
};

double ArrayStat::min() const{
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
    if (this->array.empty()) throw "The array is empty";
    if (this->array.size() == 1) throw "Only one element in the array";
    double avg = mean();
    double rms;
    double res = accumulate(array.begin(), array.end(), 0.0, [avg](double a, double element){
        return (a + (element - avg) * (element - avg));});
    rms = sqrt(res / (N - 1));
};

size_t ArrayStat::countLarger(double a) const{
    return array.end() - upper_bound(array.begin(), array.end(), a);
};

void ArrayStat::print() const{
	for (int i = 0; i < array.size(); i++)
    {
       	cout << array[i] << " ";
    };
};

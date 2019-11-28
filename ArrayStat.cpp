#include "ArrayStat.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cmath>
#include <exception>

ArrayStat::ArrayStat(const char *file_name) {
    fstream st (file_name, fstream::in);

    if (!st.is_open()) throw "Problems opening the file";
    if (st.eof()) throw "File is empty";

    int N;
    st >> N;
    arr.resize(N);

    for (int i = 0; i < N; i++) {
        if (st.eof()) throw "Unexpected end of file";
        st >> this->arr[i];
    }

    st.close();
    sort(this->arr.begin(), this->arr.end());
}

int ArrayStat::max() const {
    if (this->arr.empty()) throw "The array is empty";
    return *(--this->arr.end());
}

int ArrayStat::min() const {
    if (this->arr.empty()) throw "The array is empty";
    return *(this->arr.begin());
}

double ArrayStat::mean() const {
    if (this->arr.empty()) throw "The array is empty";
    return accumulate(this->arr.begin(), this->arr.end(), 0.0) / this->arr.size();
}

double ArrayStat::rms() const {
    if (this->arr.empty()) throw "The array is empty";
    if (this->arr.size() == 1) throw "Only one element in the array";
    double mean = this->mean();
    double sq = accumulate(this->arr.begin(), this->arr.end(), 0.0, 
    [mean](double acc, int elem) {
        return acc + (elem - mean) * (elem - mean);
    }
    );
    return sqrt(sq / (this->arr.size() - 1));
}

size_t ArrayStat::countLarger(int a) const {
    return this->arr.end() - upper_bound(this->arr.begin(), this->arr.end(), a);
}

void ArrayStat::print() const {
    for (int i = 0; i < this->arr.size(); i++) {
        cout << this->arr[i] << " ";
    }
    return;
}
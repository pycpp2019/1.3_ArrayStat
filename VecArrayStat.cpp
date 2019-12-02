#include "VecArrayStat.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cmath>

ArrayStat::ArrayStat(const char *file_name) {
    fstream st (file_name, fstream::in);

    if (!st.is_open()) throw "Problems opening the file";
    if (st.eof()) throw "File is empty";

    int N;
    st >> N;
    vec.resize(N);

    double a, b, c;
    for (int i = 0; i < N; i++) {
        if (st.eof()) throw "Unexpected end of file";
        st >> a >> b >> c;
        this->vec[i] = sqrt(a * a + b * b + c * c);
    }

    st.close();
    sort(this->vec.begin(), this->vec.end());
}

double ArrayStat::max() const {
    if (this->vec.empty()) throw "The array is empty";
    return *(this->vec.end() - 1);
}

double ArrayStat::min() const {
    if (this->vec.empty()) throw "The array is empty";
    return *(this->vec.begin());
}

double ArrayStat::mean() const {
    if (this->vec.empty()) throw "The array is empty";
    return accumulate(this->vec.begin(), this->vec.end(), 0.0) / this->vec.size();
}

double ArrayStat::rms() const {
    if (this->vec.empty()) throw "The array is empty";
    if (this->vec.size() == 1) throw "Only one element in the array";
    double mean = this->mean();
    double sq = accumulate(this->vec.begin(), this->vec.end(), 0.0, 
    [mean](double acc, double elem) {
        return acc + (elem - mean) * (elem - mean);
    }
    );
    return sqrt(sq / (this->vec.size() - 1));
}

size_t ArrayStat::countLarger(double a) const {
    return this->vec.end() - upper_bound(this->vec.begin(), this->vec.end(), a);
}

void ArrayStat::print() const {
    for (int i = 0; i < this->vec.size(); i++) {
        cout << this->vec[i] << " ";
    }
    return;
}
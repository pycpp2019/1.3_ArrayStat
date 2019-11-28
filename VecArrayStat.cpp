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
    vector.resize(N);

    double a, b, c;
    for (int i = 0; i < N; i++) {
        if (st.eof()) throw "Unexpected end of file";
        st >> a >> b >> c;
        this->vector[i] = sqrt(a * a + b * b + c * c);
    }

    st.close();
    sort(this->vector.begin(), this->vector.end());
}

double ArrayStat::max() const {
    if (this->vector.empty()) throw "The array is empty";
    return *(this->vector.end() - 1);
}

double ArrayStat::min() const {
    if (this->vector.empty()) throw "The array is empty";
    return *(this->vector.begin());
}

double ArrayStat::mean() const {
    if (this->vector.empty()) throw "The array is empty";
    return accumulate(this->vector.begin(), this->vector.end(), 0.0) / this->vector.size();
}

double ArrayStat::rms() const {
    if (this->vector.empty()) throw "The array is empty";
    if (this->vector.size() == 1) throw "Only one element in the array";
    double mean = this->mean();
    double sq = accumulate(this->vector.begin(), this->vector.end(), 0.0, 
    [mean](double acc, double elem) {
        return acc + (elem - mean) * (elem - mean);
    }
    );
    return sqrt(sq / (this->vector.size() - 1));
}

size_t ArrayStat::countLarger(double a) const {
    return this->vector.end() - upper_bound(this->vector.begin(), this->vector.end(), a);
}

void ArrayStat::print() const {
    for (int i = 0; i < this->vector.size(); i++) {
        cout << this->vector[i] << " ";
    }
    return;
}
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include "VecArrayStat.h"
using namespace std;

ArrayStat::ArrayStat(const char* filename){
    ifstream  file(filename);
    if (!file){
        throw exception();
    }

    file >> n;
    m.resize(n,1);
    double a1,a2,a3;
    for (long int i=0; i < n; i++) {
        file >> a1 >> a2 >> a3;

        m[i]=sqrt((double)(a1*a1+a2*a2+a3*a3));
    }

    sort(m.begin(),m.end());
}


void ArrayStat::print() const{
    for (int i=0; i < n; i++) {
        cout << m[i] << endl;
    }
}

double ArrayStat::max() const{
    if (n<1)
        throw exception();
    else
        return m[n-1];
}

size_t ArrayStat::countLarger(double a) const{
    return n-(upper_bound(m.begin(),m.end(),a)-m.begin()) ;
}


double ArrayStat::min() const{
    if (n<1)
        throw exception();
    else
        return m[0];
}

double ArrayStat::mean() const {
    if (n<1)
        throw exception();
    else {
        long double summ=std::accumulate(m.begin(), m.end(), (long double)0);
        return summ/(double)n;
    }
}

double ArrayStat::rms()const{
    if (n<2)
        throw exception();
    else {
        double Mean=mean();
        double r=(double)0;
        std::for_each (m.begin(), m.end(), [&](double a)->double {r += (n - Mean) * (n - Mean);});
        return sqrt(r/(double)(m.size()-1));
    }
}

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include "ArrayStat.h"
using namespace std;

double ArrayStat::rms()const{

if (Array.size()<2) throw(1);
    else {
        double rms = 0.0;
        std::for_each (Array.begin(), Array.end(), [&](int n)->double {rms += (n - mean()) * (n - mean());});
        return sqrt((rms)/Array.size());
    }
}


double ArrayStat::mean() const {

if (Array.size()<1) throw(1);
    else {
        double sum = std::accumulate(Array.begin(), Array.end(), 0);
        return (sum/(Array.size()));
    }}

int ArrayStat::max() const{

if (Array.size()<1) throw(1);
    else
        return Array[Array.size()-1];
}

size_t ArrayStat::countLarger(int a) const{
        int k = 0;
        std::for_each (Array.begin(), Array.end(), [&](int n)->double {if (n>a)  k += 1;});

}


int ArrayStat::min() const{

if (Array.size()<1) throw(1);
    else
        return Array[0];
    }


ArrayStat::ArrayStat(const char* filename){

ifstream  ifile(filename, ifstream::in);
if (!ifile.good()){
    throw 1;
}

int N;
ifile >> N;
int k = N;

for (int i=0; i < k; i++) {
    ifile >> N;
    Array.push_back(N);

std::sort(Array.begin(),Array.end());

}}


void ArrayStat::print() const{

for (int i=0; i < (Array.size()); i++) {
    cout << Array[i] <<" "<< endl;

}
}

/*int main(){

    ArrayStat wow("D:/ArrayStat.txt.txt");
    wow.print();
   /* cout << "max is" << wow.max() << endl;
    cout <<wow.mean()<<"rms is"<< wow.rms()<< endl;

    return 0;
}*/

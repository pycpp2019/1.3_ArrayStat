#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include "VecArrayStat.h"
using namespace std;

double ArrayStat::rms()const{

if (Array.size()<2) throw(1);
    else {
        double m = mean();
        double rms =(double)0;
        std::for_each (Array.begin(), Array.end(), [&](int n)->double {rms += (n - m) * (n - m);});
        return sqrt((rms)/((double)Array.size()-1));
    }
}



double ArrayStat::mean() const {

if (Array.size()<1) throw(1);
    else {
        long double sum = std::accumulate(Array.begin(), Array.end(), (long double)0);
        return (sum/(double)(Array.size()));
    }
}

double ArrayStat::max() const{

if (Array.size()<1) throw(1);
    else
        return Array[Array.size()-1];
}

size_t ArrayStat::countLarger(double a) const{
        int k = 0;
       k =Array.size() - (upper_bound(Array.begin(),Array.end(), (a)) - Array.begin()) ;      /*std::for_each (Array.begin(), Array.end(), [&](int n)-> int{if (n>a)  k += 1;});*/
return k;
}


double ArrayStat::min() const{

if (Array.size()<1) throw(1);
    else
        return Array[0];
}



ArrayStat::ArrayStat(const char* filename){

ifstream  ifile(filename, ifstream::in);
if (!ifile.good()){
    throw 1;
}

double N;
ifile >> N;
int k = (int)N;
double o;
for (long int i=0; i < k; i++) {
    o=(double)0;
    for(int j=0; j<3; j++){
        ifile >> N;
        o+=N*N;
    }

    Array.push_back(sqrt(o));
    }
std::sort(Array.begin(),Array.end());

}


void ArrayStat::print() const{
for (int i=0; i < (Array.size()); i++) {
    cout << Array[i] <<" "<< endl;

}
}

/*int main(){

    ArrayStat wow("D:/VecArrayStat.txt.txt");
    wow.print();
    cout << "max is" << wow.max() << endl;
    cout <<"mean" << wow.mean()<<"rms is"<< wow.rms()<< endl;
    cout <<">3.999 :"<< wow.countLarger(4.5825) << endl;
    return 0;
}*/


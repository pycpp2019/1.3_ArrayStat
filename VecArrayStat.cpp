#pragma once

#include <cstdlib>
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <fstream>
#include "VecArrayStat.h"
using namespace std;

   double square::  operator()(const double& Left, const double& Right) const
    {
        return (Left + Right*Right);
    }
    double one::  operator()(const double& Left, const double& Right) const
    {
        return Left+1;
    }

ArrayStat:: ArrayStat(const char *file_name){
    try{
        ifstream file(file_name);
        if(!file)
            throw 0;
        try{
            file >> this->n;
            if(this->n<0)
                throw 1;
            int a1,a2,a3;
            for(int i=1;i<=this->n;i++){

                    file >> a1 >> a2 >> a3;

                    this->m.insert(sqrt(a1*a1+a2*a2+a3*a3));

            }
        }
        catch(int i){
        if (i==1) cout << "not a number";}
    }
    catch (int i){
        if(i==0) cout << "no file";}


}

double ArrayStat:: max() const{
    try{
        if(this->n==0)
            throw 10;
        return *(this->m.end());
    }
    catch(int i){
       if(i==10) cout << "n=0";}
}
double ArrayStat:: min() const{
    try{
        if(this->n==0)
            throw 10;
        return *(this->m.begin());
    }
    catch(int i){
       if(i==10) cout <<"n=0";}
}

double ArrayStat:: mean() const{
    try{
        if(this->n==0)
            throw 10;
        return double(accumulate(this->m.begin(),this->m.end(),0))/this->n;
    }
    catch (int i){
        cout << "n=0";}
}
double ArrayStat:: rms() const{
    try{
        if(this->n==0||this->n==1)
            throw 100;
        return sqrt(double(accumulate(this->m.begin(),this->m.end(),0,square()))/this->n-(this->mean()*this->mean()));
    }
    catch (int i){
        cout << "n=0or1";}
}
size_t ArrayStat:: countLarger(int a) const{
    size_t s=0;
        s=accumulate(this->m.upper_bound(a),this->m.end(),0,one());
        return s;
}
void ArrayStat:: print() const{
    copy( m.begin(), m.end(), ostream_iterator<double>(cout, " "));

}
int main(){
    ArrayStat m=ArrayStat("a.txt");
    double a=m.min();

   cout << a << ' ';
    return 0;

}


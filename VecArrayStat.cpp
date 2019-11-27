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
        if(!file){
            throw 0;
        }
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
        if (i==1) cout << "not a number: error -" << i;}
    }
    catch (int i){
        if(i==0) cout << "no file";}


}

float ArrayStat:: max() const{
    try{
        if(this->n==0)
            throw 10;
        return *(this->m.end());
    }
    catch(int i){
       if(i==10) cout << "n=0";}
}
float ArrayStat:: min() const{
    try{
        if(this->n==0)
            throw 10;
        return *(this->m.begin());
    }
    catch(int i){
       if(i==10) cout <<"n=0";}
}

float ArrayStat:: mean() const{
    try{
        if(this->n==0)
            throw 10;
        return double(accumulate(this->m.begin(),this->m.end(),0))/this->n;
    }
    catch (int i){
        cout << "n=0";}
}
float ArrayStat:: rms() const{
    try{
        if(this->n==0||this->n==1)
            throw 100;
        return sqrt(float(accumulate(this->m.begin(),this->m.end(),0,square()))/this->n-(this->mean()*this->mean()));
    }
    catch (int i){
        cout << "n=0or1";}
}
size_t ArrayStat:: countLarger(int a) const{
    return distance(this->m.upper_bound(a),this->m.end());
}
void ArrayStat:: print() const{
    if(this->n==0)
        cout << "empty";
    else{
    multiset <float> :: iterator it = this->m.begin();
   for (int i = 1; it != this->m.end(); i++, it++) {
        cout << *it << " ";
    }
    }
}
/*int main(){
    ArrayStat m=ArrayStat("a.txt");
    size_t a=m.countLarger(18);
    cout << a << endl;
    float p=m.min();
    m.print();
    return 0;

}*/


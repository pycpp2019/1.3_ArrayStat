#pragma once

#include <cstdlib>
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <fstream>
#include "ArrayStat.h"
using namespace std;

   int square::  operator()(const int& Left, const int& Right) const
    {
        return (Left + Right*Right);
    }
    int one::  operator()(const int& Left, const int& Right) const
    {
        return 1;
    }

ArrayStat:: ArrayStat(const char *file_name){
    try{
        ifstream file(file_name);
        if(!file){
            throw 0;
        }
        try{
            file >> this->n;
            if(!this->n)
                throw 1;
            int a;
            for(int i=1;i<=this->n;i++){

                    file >> a;

                    this->m.insert(a);


            }
        }
        catch(int i){
        cout << "not a number error: " << i;}
    }
    catch (int i){
        cout << "no file error: " << i;}


}

int ArrayStat:: max() const{
    try{
        if(this->n==0)
            throw 10;

        return *(this->m.end());

    }
    catch(int i){
       if(i==10) cout << "n=0";}
}
int ArrayStat:: min() const{
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
        return float(accumulate(this->m.begin(),this->m.end(),0)/this->n);
    }
    catch (int i){
        cout << "n=0";}
}
float ArrayStat:: rms() const{
    try{
        if(this->n==0||this->n==1)
            throw 100;
        return sqrt(fabs(this->mean()*this->mean()+(accumulate(this->m.begin(),this->m.end(),0,square())/this->n)));
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
    multiset <int> :: iterator it = this->m.begin();
   for (int i = 1; it != this->m.end(); i++, it++) {
        cout << *it << " ";
    }
    }
}


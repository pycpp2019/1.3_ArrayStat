#pragma once
# include <exception>
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
            throw exception();
        }
        try{
            file >> this->n;
            if(!this->n)
                throw exception();
            int a;
            for(int i=1;i<=this->n;i++){
                    file >> a;
                    this->m.insert(a);
            }
        }

        catch(exception err){
            cout << "not a number error: " ;

    }
    }
    catch (exception err){
        cout << "no file error: " ;
    }


}

int ArrayStat:: max() const{
    try{
        if(this->n==0)
            throw exception();

        return *(this->m.end());

    }
    catch(exception err){
       cout << "n=0";
    }
}
int ArrayStat:: min() const{
    try{
        if(this->n==0)
            throw exception();
        return *(this->m.begin());
    }
    catch(exception arr){
       cout <<"n=0";
    }
}

float ArrayStat:: mean() const{
    try{
        if(this->n==0)
            throw exception();
        return float(accumulate(this->m.begin(),this->m.end(),0)/this->n);
    }
    catch (exception err){
        cout << "n=0";
    }
}
float ArrayStat:: rms() const{
    try{
        if(this->n==0||this->n==1)
            throw exception();
        return sqrt(fabs(this->mean()*this->mean()+(accumulate(this->m.begin(),this->m.end(),0,square())/this->n)));
    }
    catch (exception arr){
        cout << "n=0or1";
    }
}
size_t ArrayStat:: countLarger(int a) const{
    return distance(this->m.upper_bound(a),this->m.end());
}
void ArrayStat:: print() const{
    try{
        if(this->n==0)
            throw exception();
        else{
            multiset <int> :: iterator it = this->m.begin();
            for (int i = 1; it != this->m.end(); i++, it++) {
                cout << *it << " ";
            }
        }
    }
    catch(exception err){
        cout << "empty";
    }
}


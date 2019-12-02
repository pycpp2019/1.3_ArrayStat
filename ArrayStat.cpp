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

ArrayStat:: ArrayStat(const char *file_name){
    this->n=-5;

        ifstream file(file_name);
        if(!file){
            throw exception();
        }
        try{
            file >> this->n;
            if(!this->n)
                throw exception();
            m.resize(this->n,1);
            int a;
            int i;
            for(i=0;i<this->n;i++)
                    file >> m[i];
            sort(m.begin(),m.end());
        }

        catch(exception err){
            cout << "exception" ;
            this->n=0;
    }



}

int ArrayStat:: max() const{
    if(this->n==0)
        throw exception();
    else{
        return *prev((this->m.end()));
    }

}
int ArrayStat:: min() const{
        if(this->n==0)
            throw exception();
        else{
            return *(this->m.begin());
        }
}

double ArrayStat:: mean() const{
        if(this->n==0)
            throw exception();
        else{
            return double(accumulate(this->m.begin(),this->m.end(),0.0)/double(this->n));
        }
}
double ArrayStat:: rms() const{
        if(this->n==0||this->n==1)
            throw exception();
        else{
            double s=accumulate(this->m.begin(),this->m.end(),0.0);
            double ssq=double(accumulate(this->m.begin(),this->m.end(),0.0,[](double x,double y){return double(x+y*y);}));
            return sqrt((ssq-s*s/double(this->n))/double(n-1));
        }
}
size_t ArrayStat:: countLarger(int a) const{
    return m.end()-upper_bound(m.begin(),m.end(),a);
}
void ArrayStat:: print() const{
    try{
        if(this->n==0)
            throw exception();
        else{
            for (int i = 0; i<this->n; i++) {
                cout << m[i] << " ";
            }
        }
    }
    catch(exception err){
        cout << "empty";
    }
}



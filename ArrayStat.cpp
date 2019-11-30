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
            int a;
            o.resize(this->n,1);
            for(int i=1;i<=this->n;i++){
                    file >> a;
                    this->m.insert(a);
                    o[i]=a;
            }
        }

        catch(exception err){
            cout << "not a number" ;
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
            double s=accumulate(this->m.begin(),this->m.end(),0.0)/double(this->n);
            double ssq=inner_product(this->m.begin(),this->m.end(),this->m.begin(),0.0);
            return(sqrt(ssq-s*s/double(this->n))/double(this->n-1));
        }
}
size_t ArrayStat:: countLarger(int a) const{
    return o.end()-upper_bound(o.begin(),o.end(),a);
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

/*int main(){
    ArrayStat m=ArrayStat("a.txt");
    float a=m.rms();
    cout << a;
    return 0;
}*/


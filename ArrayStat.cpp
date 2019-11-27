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
            cout << "not a number" ;
            this->n=0;
    }
    }
    catch (exception err){
        cout << "no such file " ;

    }


}

int ArrayStat:: max() const{
    try{
        if(this->n==0)
            throw exception();

        return *prev((this->m.end()));

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
        return float(accumulate(this->m.begin(),this->m.end(),0.0)/float(this->n));
    }
    catch (exception err){
        cout << "n=0";
    }
}
float ArrayStat:: rms() const{
    try{
        if(this->n==0||this->n==1)
            throw exception();
        return sqrt(inner_product(this->m.begin(),this->m.end(), this->m.begin(),0.0)/this->n-float(this->mean()*this->mean()));
    }
    catch (exception arr){
        cout << "n=0or1";
    }
}
size_t ArrayStat:: countLarger(int a) const{
    if(this->n==0)
        return 0;
    if(a>this->mean())
        return distance(this->m.upper_bound(a),this->m.end());
    else return this->n-distance(this->m.begin(),this->m.upper_bound(a));
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


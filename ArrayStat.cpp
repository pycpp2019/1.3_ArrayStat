#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <functional>
#include "ArrayStat.h"

ArrayStat::ArrayStat(const char * name)
{
    ifstream filein;
    try
    {
        {
            filein.open(name);
            if (filein.is_open() == false) throw  "Input error: file not found or type is incorrect!";
            int c, n;
            filein >> n;
            for (int i=0; i<n; i++)
            {
                filein >> c;
                arr.push_back(c);
            }

        }
    }
    catch(const string error)
    {
        cout << error;
    }
    sort(arr.begin(), arr.end());
    
}

int ArrayStat::max()
{
    if (arr.size()==0) throw "Error";
    else
    return arr[arr.size()-1];
}
int ArrayStat::min()
{
    if (arr.size()==0) throw "Error";
    else
    return arr[0];
}
double ArrayStat::mean()
{
    if (arr.size()==0) throw "Error";
    else
    {
    double n=arr.size();
    double sum=accumulate(arr.begin(), arr.end(), (double)0);
    return sum/n;
    }
}
double ArrayStat::rms()
{
    if (arr.size()==0 || arr.size()==1) throw "Error";
    else
    {
    double m=mean();
    double n=arr.size();
    double S=accumulate(arr.begin(), arr.end(), (double)0, [](double sum, double el) {
			return sum + el * el;})/n;
    
        S=sqrt((S - m * m) * n / (n-1));
    return S;
    }
}
size_t ArrayStat::countLarger(int a)
{
    if (arr.size()==0) throw "Error";
   if (arr.size() <= 2)
    {
        if (arr.size()==2)
        {
        if (arr[0]>a) return 2;
        else if (arr[1]>a) return 1;
        else return 0;
        }
        else
        {
            if (arr.size()==1)
            {
            if (arr[0]>a)return 1;
            else return 0;
            }
            else return 0;
        }
        
    }
    else
    {
        return distance(upper_bound(arr.begin(), arr.end(), a), arr.end());
    } 
}
void ArrayStat::print()
{
    if (arr.size()!=0) 
    for (long int i=0; i<arr.size(); i++)
    {
        cout<< arr[i]<<" ";
    }
}
/*
int main() {
    ArrayStat stat("test.txt");
    stat.print();
    cout <<"  a="<< stat.countLarger(2) << endl;
      //cout << "max=" << stat.max() << endl;
    
    return 0;
}
*/
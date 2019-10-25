#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <functional>
#include "VecArrayStat.h"

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
                double x, y, z;
                filein >> x >> y >> z;
                double n=sqrt(x*x+y*y+z*z);
                arr.push_back(n);

                
            }

        }
    }
    catch(const string error)
    {
        cout << error;
    }
    sort(arr.begin(), arr.end());
}
double ArrayStat::max() const
{
    if (arr.size()==0) throw "Error";
    else
    return arr[arr.size()-1];
}
double ArrayStat::min() const
{
    if (arr.size()==0) throw "Error";
    else
    return arr[0];
}
double ArrayStat::mean() const
{
    if (arr.size()==0) throw "Error";
    else
    {
    double n=arr.size();
    double sum=accumulate(arr.begin(), arr.end(), (double)0);
    return sum/n;
    }
}
double ArrayStat::rms() const
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
size_t ArrayStat::countLarger(double a) const
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
void ArrayStat::print() const
{
    if (arr.size()!=0) 
    for (long int i=0; i<arr.size(); i++)
    {
        cout<< arr[i]<<" ";
    }
}
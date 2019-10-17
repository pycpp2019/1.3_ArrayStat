#include <fstream>
#include <algorithm>
#include <cmath>
#include "ArrayStat.h"

ArrayStat::ArrayStat(const char * name)
{
    ifstream filein;
    try
    {
        {
            filein.open(name);
            int c, n;
            filein >> n;
            for (int i=0; i<n; i++)
            {
                filein >> c;
                arr.push_back(c);
            }

        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    sort(arr.begin(), arr.end());
    
}

int ArrayStat::max()
{
    if (arr.size()!=0)
    return arr[arr.size()-1];
}
int ArrayStat::min()
{
    if (arr.size()!=0)
    return arr[0];
}
double ArrayStat::mean()
{
    if (arr.size()!=0)
    {
    int n=arr.size()-1;
    double sum;
    for (int i=0; i<=n; i++)
    {
        sum=sum+arr[i];
    }
    return sum/n;
    }
}
double ArrayStat::rms()
{
    if (arr.size()!=0)
    {
    double m=mean();
    double S;
    int n=arr.size()-1;
    for (int i=0; i<=n; i++)
    {
        S=S+(arr[i]-m)*(arr[i]-m);
    }
    S=sqrt(S/n);
    return S;
    }
}
size_t ArrayStat::countLarger(int a)
{
   if (arr.size() <= 2)
    {
        if (arr.size() == 2)
        {
            if (arr[1]>=a) return 2;
            else 
            {
                if (arr[0]>=a) return 1;
                else return 0;
            }
        }
        if(arr.size() == 1)
        {
            if (arr[0]>=a) return 1;
            else return 0;
        }
        if (arr.size() == 0) return 0;
    }
    else
    {
        return distance(arr.begin(), upper_bound(arr.begin(), arr.end(), a));
    } 
}
void ArrayStat::print()
{
    if (arr.size()!=0)
    for (int i=0; i<=arr.size(); i++)
    {
        cout<< arr[i]<<" ";
    }
}
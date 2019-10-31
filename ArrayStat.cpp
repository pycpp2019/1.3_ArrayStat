	#include <fstream>
	#include <iostream>
	#include <cmath>
	#include "ArrayStat.h"
	#include <iterator>
	#include <numeric>
	 
 	ArrayStat::ArrayStat(const char *file_name){
 		try{
		 	std::ifstream fin(file_name);
 			if(fin.is_open() == false) throw "can't open the file";
 			
		
 		int N,buf=0;
 		fin>>N;
		for(int i=0; i!=N; i++){
				fin>>buf;
				myset.insert(buf);
		}
	
 			fin.close();
 		}	
		catch(char *error){
		std::cout<<error;
		}
 	}

    int ArrayStat::max() const{
    	try{
    		if(myset.size()==0) throw "max 0 error";
			return *(--myset.end());
		}
		catch(char *error){
		std::cout<<error;	
		return 0;
	}}

    int ArrayStat::min() const{
    	try{
    		if(myset.size()==0) throw "min 0 error";
			return *myset.begin();
		}
		catch(char *error){
		std::cout<<error;
		return 0;
	}}

    double ArrayStat::mean() const{
    	try{
    		if(myset.size()==0) throw "mean 0 error";
			double sum=std::accumulate(myset.begin(), myset.end(), 0.0);
			return sum/myset.size();
		}
		catch(char *error){
		std::cout<<error;
		return 0;
	}}

	
    double ArrayStat::rms() const{
    	try{
    		if(myset.size()==0 || myset.size()==1) throw "rms error";
			double m = mean();
			double s=std::accumulate(myset.begin(),myset.end(),0.0,[&m](const double &x,const double &y)->double{return x+(m-y)*(m-y);});
			return sqrt(s/(myset.size()-1));
		}
		catch(char *error){
		std::cout<<error;
		return 0;
	}}

    size_t ArrayStat::countLarger(int key) const{
		return std::distance(myset.upper_bound(key),myset.end());
	}
	
    void ArrayStat::print() const{
		copy( myset.begin(), myset.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout<<std::endl;
	}

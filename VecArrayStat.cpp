	#include <fstream>
	#include <iostream>
	#include <cmath>
	#include "VecArrayStat.h"
	#include <iterator>
	#include <numeric>
	#include <algorithm> 
	 
 	ArrayStat::ArrayStat(const char *file_name){
 		int N;
 		double buf,norm=0.0;
 		try{
		 	std::ifstream fin(file_name);
 			if(fin.is_open() == false) throw "can't open the file";
 			fin>>N;
			for(int i=0; i!=N; i++){
				for(int j=0; j!=3; j++){
					fin>>buf;
					norm+=buf*buf;	
				}
				myset.push_back(sqrt(norm));
				norm=0.0;
			}
	
 			fin.close();
 		}	
		catch(char *error){
		std::cout<<error;
		}
		std::sort(myset.begin(),myset.end());
 	}

    double ArrayStat::max() const{
    	try{
    		if(myset.size()==0) throw "max 0 error";
			return myset.back();
		}
		catch(char *error){
		std::cout<<error;	
		return 0;
		}
	}

    double ArrayStat::min() const{
    	try{
    		if(myset.size()==0) throw "min 0 error";
			return myset.front();
		}
		catch(char *error){
		std::cout<<error;
		return 0;
		}
	}

    double ArrayStat::mean() const{
    	try{
    		if(myset.size()==0) throw "mean 0 error";
			double sum=std::accumulate(myset.begin(), myset.end(), 0.0);
			return sum/myset.size();
		}
		catch(char *error){
		std::cout<<error;
		return 0;
		}
	}
	

	
    double ArrayStat::rms() const{
    	double m = mean();
    	try{
    		if(myset.size()==0 || myset.size()==1) throw "rms error";
			double s=std::accumulate(myset.begin(),myset.end(),0.0,
			[&m](const double &x,const double &y)->double{return x+(m-y)*(m-y);}
			);
			return sqrt(s/(myset.size()-1.0));
		}
		catch(char *error){
		std::cout<<error;
		return 0;
		}
	}

    size_t ArrayStat::countLarger(double key) const{
		return myset.end()-std::upper_bound(myset.begin(),myset.end(),key);
	}
	
    void ArrayStat::print() const{
		copy( myset.begin(), myset.end(), std::ostream_iterator<double>(std::cout, "\n"));
		std::cout<<std::endl;
	}

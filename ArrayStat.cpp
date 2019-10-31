	#include <fstream>
	#include <iostream>
	#include <cmath>
	#include "ArrayStat.h"
	#include <iterator>
	 
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
	return *(--myset.end());
	}

    int ArrayStat::min() const{
	return *myset.begin();
	}

    double ArrayStat::mean() const{
    	int sum=0;
    	std::multiset<int>::iterator it;
		for (it=myset.begin(); it!=myset.end(); ++it){
			sum+=*it;
		}
		return sum/myset.size();
	}
	
    double ArrayStat::rms() const{
		double m = mean();
		int sum;
		std::multiset<int>::iterator it;
		for (it=myset.begin(); it!=myset.end(); ++it){
			sum+=(m-*it)*(m-*it);
		}
		return sqrt(sum/myset.size());
	}

    size_t ArrayStat::countLarger(int key) const{
	return std::distance(myset.upper_bound(key),myset.end());
	}
	
    void ArrayStat::print() const{
		copy( myset.begin(), myset.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout<<std::endl;
	}

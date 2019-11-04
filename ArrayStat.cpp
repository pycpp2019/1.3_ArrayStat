#include "ArrayStat.h"


ArrayStat::ArrayStat(const char *file_name)
{
	std::ifstream file(file_name);
	if (!file) 
	{ 
		throw 1;
	} 
	else
	{
		int N;
		file >> N;
		if (!(N >= 0)) { throw 0; }
		else
		{
			data.resize(N,1);
        	for (int i = 0; i < data.size(); ++i)
        	{
            	file >> data[i];
        	}
        	std::sort(data.begin(),data.end());
    	}
	} 

}

int ArrayStat::max() const
{
	if (data.size() == 0)
	{ 
		throw 2;
	}
	else
	{
		return *std::max_element(data.begin(), data.end());
	} 
}
int ArrayStat::min() const
{
	if (data.size() == 0)
	{ 
		throw 2;
	}
	else
	{
		return *std::min_element(data.begin(), data.end());
	}
}
double ArrayStat::mean() const
{
	if (data.size() == 0)
	{ 
		throw 2;
	}
	else
	{
		return double(std::accumulate(data.begin(), data.end(), 0)) / double(data.size());
	}
}

int sumsq(int x, int y)
{
	return x + y*y;
}

double ArrayStat::rms() const
{ 
	if (data.size() > 1)
	{
		return double(data.size()) / double(data.size() - 1) * (double(std::accumulate(data.begin(), data.end(), 0, sumsq)) / double(data.size()) - std::pow(double(std::accumulate(data.begin(), data.end(), 0)) / double(data.size()),2));
	}
	else { throw 2; }
} 


size_t ArrayStat::countLarger(int a) const { return data.end() - std::upper_bound(data.begin(), data.end(), a); }

void ArrayStat::print() const
{
	if (data.size() != 0)
	{
		for (int i = 0; i < data.size() - 1; ++i)
    	{
        	std::cout << data[i] << " ";
    	}
    	std::cout << *(data.end() - 1) << std::endl;;
	}
}


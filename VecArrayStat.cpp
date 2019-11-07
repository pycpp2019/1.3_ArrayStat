#include "VecArrayStat.h"


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
			std::vector<double> a;
			a.resize(4,0);
			data.resize(N, a);
			len.resize(N,0);
        	for (int i = 0; i < data.size(); ++i)
        	{
            	file >> data[i][0] >> data[i][1] >> data[i][2];
            	data[i][3] = std::sqrt(double(data[i][0]*data[i][0] + data[i][1]*data[i][1] + data[i][2]*data[i][2]));
            	len[i] = data[i][3];
        	}
        	std::sort(data.begin(),data.end(),[] (std::vector<double> x, std::vector<double> y){ return x[3] < y[3];});
    	}
	} 

}
double ArrayStat::max() const
{
	if (data.size() == 0)
	{ 
		throw 2;
	}
	else
	{
		return (*std::max_element(data.begin(), data.end(),[] (std::vector<double> x, std::vector<double> y){ return x[3] < y[3];}))[3];
	}
}
double ArrayStat::min() const
{
	if (data.size() == 0)
	{ 
		throw 2;
	}
	else
	{
		return (*std::max_element(data.begin(), data.end(),[] (std::vector<double> x, std::vector<double> y){ return x[3] > y[3];}))[3];
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
		return double(std::accumulate(data.begin(), data.end(), double(0), [] (double x, std::vector<double> y){ return double(x) + double(y[3]);})) / double(data.size());
	}
}
double ArrayStat::rms() const
{ 
	if (data.size() > 1)
	{
		double sum = double(std::accumulate(data.begin(), data.end(), double(0), [] (double x, std::vector<double> y){ return double(x) + double(y[3]);}));
		double sq_sum = double(std::accumulate(data.begin(), data.end(), double(0), [] (double x, std::vector<double> y){ return double(x) + double(y[3])*double(y[3]);}));
		return sqrt((sq_sum - sum*sum/data.size()) / (data.size() - 1));
	}
	else { throw 2; }
}
size_t ArrayStat::countLarger(double a) const { return len.end() - std::upper_bound(len.begin(), len.end(), a); } 
void ArrayStat::print() const
{
	if (data.size() != 0)
	{
		for (int i = 0; i < data.size(); ++i)
    	{
        	std::cout << data[i][3] << " ";
    	}
	}
}
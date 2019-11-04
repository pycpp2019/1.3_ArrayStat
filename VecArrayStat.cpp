#include "VecArrayStat.h"


VecArrayStat::VecArrayStat(const char *file_name)
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
double VecArrayStat::max() const
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
double VecArrayStat::min() const
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
double VecArrayStat::mean() const
{
	if (data.size() == 0)
	{ 
		throw 2;
	}
	else
	{
		return double(std::accumulate(data.begin(), data.end(), double(0), [] (double x, std::vector<double> y){ return double(x + y[3]);})) / double(data.size());
	}
}
double VecArrayStat::rms() const
{ 
	if (data.size() > 1)
	{
		return double(data.size()) / double(data.size() - 1) * (double(std::accumulate(data.begin(), data.end(), double(0), [] (double x, std::vector<double> y){ return double(x + y[3]*y[3]);})) / double(data.size()) - std::pow(double(std::accumulate(data.begin(), data.end(), double(0), [] (double x, std::vector<double> y){ return double(x + y[3]);})) / double(data.size()),2));
	}
	else { throw 2; }
}
size_t VecArrayStat::countLarger(double a) const { return len.end() - std::upper_bound(len.begin(), len.end(), a) - 1; } 
void VecArrayStat::print() const
{
	if (data.size() != 0)
	{
		for (int i = 0; i < data.size(); ++i)
    	{
        	std::cout << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3] << std::endl;;
    	}
	}
}
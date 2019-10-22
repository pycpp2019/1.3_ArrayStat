#include "VecArrayStat.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>




ArrayStat::ArrayStat(const char *file_name) : sorted(std::vector<double>()) {
	std::fstream file (file_name, std::fstream::in);

	if(!file.is_open())
		throw std::invalid_argument("File does not exist");
	if(file.bad())
		throw std::invalid_argument("Unknown problem with file");
	if(file.eof())
		throw std::invalid_argument("File is empty");

	size_t num_of_el = 0;

	file >> num_of_el;
	this->sorted.resize(num_of_el);

	std::for_each(this->sorted.begin(), this->sorted.end(),
		[& file](double & el) {
			if(file.eof())
				throw std::length_error("File format does not match required one");

			double tmp0 = 0;
			double tmp1 = 0;
			double tmp2 = 0;

			file >> tmp0;
			file >> tmp1;
			file >> tmp2;
			el = std::sqrt(tmp0 * tmp0 + tmp1 * tmp1 + tmp2 * tmp2);
		}
	);

	file.close();

	std::sort(this->sorted.begin(), this->sorted.end());
}


double ArrayStat::max() const {
	if(this->sorted.empty())
		throw std::length_error("Vector is empty");

	return *(--this->sorted.end());
}




double ArrayStat::min() const {
	if(this->sorted.empty())
		throw std::length_error("Vector is empty");

	return *(this->sorted.begin());
}




double ArrayStat::mean() const {
	if(this->sorted.empty())
		throw std::length_error("Vector is empty");

	return (double)std::accumulate(this->sorted.begin(), this->sorted.end(), (double) 0) /
		this->sorted.size();
}




double ArrayStat::rms() const {
	if(this->sorted.empty() || this->sorted.size() == 1)
		throw std::length_error("Vector is empty or includes only 1 element");

	double rms = (double)std::accumulate(this->sorted.begin(),
		this->sorted.end(), (double) 0,
		[](double sum, double el) {
			return sum + el * el;
		}) / this->sorted.size();

	double mean = this->mean();

	return std::sqrt((double)(rms - mean * mean) * this->sorted.size() /
		(this->sorted.size() - 1));
}




size_t ArrayStat::countLarger (double el) const {
	return this->sorted.end() -
		std::upper_bound(this->sorted.begin(), this->sorted.end(), el);
}




void ArrayStat::print() const {
	std::for_each(this->sorted.begin(), this->sorted.end(),
		[](const double& elem) {
			std::cout << elem << " ";
		});

	std::cout << std::endl;
	return;
}
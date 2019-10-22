#include "ArrayStat.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>




ArrayStat::ArrayStat(const char *file_name) : sorted(std::vector<int>()) {
	std::fstream file (file_name, std::fstream::in);

	if(!file.is_open())
		throw std::invalid_argument("File does not exist");
	if(file.bad())
		throw std::invalid_argument("An unknown problem with file");
	if(file.eof())
		throw std::invalid_argument("File is empty");

	size_t num_of_el = 0;

	file >> num_of_el;
	this->sorted.resize(num_of_el);

	std::for_each(this->sorted.begin(), this->sorted.end(),
		[& file](int & el) {
			if(file.eof())
				throw std::length_error("File format does not match required one");

			file >> el;
		});

	file.close();
	std::sort(this->sorted.begin(), this->sorted.end());
}




int ArrayStat::max() const {
	if(this->sorted.empty())
		throw std::length_error("Vector is empty");

	return *(--this->sorted.end());
}




int ArrayStat::min() const {
	if(this->sorted.empty())
		throw std::length_error("Vector is empty");

	return *(this->sorted.begin());
}




double ArrayStat::mean() const {
	if(this->sorted.empty())
		throw std::length_error("Vector is empty");

	return (double)std::accumulate(this->sorted.begin(), this->sorted.end(), 0) /
		this->sorted.size();
}




double ArrayStat::rms() const {
	if(this->sorted.empty() || this->sorted.size() == 1)
		throw std::length_error("Vector is empty or includes only 1 element");

	double rms = (double)std::accumulate(this->sorted.begin(),
		this->sorted.end(), 0,
		[](int sum, int el) {
			return sum + el * el;
		}) / this->sorted.size();

	double mean = this->mean();

	return std::sqrt((double)(rms - mean * mean) * this->sorted.size() /
		(this->sorted.size() - 1));
}




size_t ArrayStat::countLarger (int el) const {
	return this->sorted.end() -
		std::upper_bound(this->sorted.begin(), this->sorted.end(), el);
}




void ArrayStat::print() const {
	std::for_each(this->sorted.begin(), this->sorted.end(),
		[](const int& elem) {
			std::cout << elem << " ";
		});

	std::cout << std::endl;
	return;
}
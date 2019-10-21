#include "ArrayStat.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <algorithm>

ArrayStat::ArrayStat(const char *file_name) : sorted(std::vector<int>()) {
	std::fstream file (file_name, std::fstream::in);

	if(file.bad())
		throw std::invalid_argument("File does not exist");
	if(file.eof())
		throw std::invalid_argument("File is empty");

	size_t num_of_el = 0;

	file >> num_of_el;

	for(size_t i = 0; i < num_of_el; ++i) {
		if(file.eof())
			throw std::length_error("File format does not match required one");

		int tmp = 0;

		file >> tmp;
		this->sorted.insert(this->sorted.end(), tmp);
	}

	file.close();

	std::sort(this->sorted.begin(), this->sorted.end());
}

int ArrayStat::max() const {
	return *(--this->sorted.end());
}

int ArrayStat::min() const {
	return *(this->sorted.begin());
}

double ArrayStat::mean() const {
	return (double)std::accumulate(this->sorted.begin(), this->sorted.end(), 0) / this->sorted.size();
}

double ArrayStat::rms() const {
	return (double)std::accumulate(this->sorted.begin(), this->sorted.end(), 0,
		[](int sum, int el) {
			return sum + el * el;
		}) / this->sorted.size();
}

size_t ArrayStat::countLarger (int el) const {
	return std::upper_bound(this->sorted.begin(), this->sorted.end(), el) - this->sorted.end();
}

void ArrayStat::print() const {
	std::for_each(this->sorted.begin(), this->sorted.end(),
		[](const int& elem) {
			std::cout << elem << " ";
		});
	std::cout << std::endl;
	return;
}
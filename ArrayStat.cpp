#include "ArrayStat.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <io.h>
#include <numeric>
#include <cmath>

ArrayStat::ArrayStat(const char *file_name) {
    std::ifstream file(file_name);
    if (!file) throw std::invalid_argument("File does not open.");
    file >> count;
    data.resize(count);
    while (!file.eof()) {
        for (int i = 0; i < count; i++) {
            file >> data[i];
        }
    }
    std::sort(data.begin(), data.end());
}

int ArrayStat::max() const {
    if ((count == 0) || (count == 1)) throw std::invalid_argument("Count of array is not enough for work");
    return data[count - 1];
}
int ArrayStat::min() const {
    if ((count == 0) || (count == 1)) throw std::invalid_argument("Count of array is not enough for work");
    return data[0];
}
double ArrayStat::mean() const {
    if ((count == 0) || (count == 1)) throw std::invalid_argument("Count of array is not enough for work");
    return accumulate(data.begin(), data.end(), data[0])/count;
}
double ArrayStat::rms() const {
    if ((count == 0) || (count == 1)) throw std::invalid_argument("Count of array is not enough for work");
    std::vector<int> data_1;
    data_1.resize(count);
    for (int i = 0; i < count; i++) {
        data_1[i] = pow(data[i], 2);
    }
    return accumulate(data_1.begin(), data_1.end(), data_1[0])/count - pow((accumulate(data.begin(), data.end(), data[0])/count), 2);
}
size_t ArrayStat::countLarger(int a) const {
    int counter = 0;
    for (int i = 0; i < count; i++) {
        if (data[i] > a) {
            counter++;
        }
    }
    return counter;
}
void ArrayStat::print() const {
    for (int i = 0; i < count; ++i) {
        std::cout << data[i] << std::endl;
    }
}
int main() {
    ArrayStat A("test.txt");
    A.print();
    std::cout << A.mean() << std::endl;
    return 0;
}

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cstdlib>


class ArrayStat {
public:
    class Exception : std::exception {
    public:
        std::string msg;
        Exception(const char *msg) {
            this->msg = std::string(msg);
        }
    };

private:
    std::vector<int> data;

public:
    ArrayStat(const char *file_name) {
        std::ifstream file(file_name);
        if (!file.is_open() || !file.good()) {
            throw Exception("cannot open file");
        }

        std::size_t n;
        file >> n;

        this->data.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            if (!file.good()) {
                throw Exception("unexpected eof or failure");
            }
            int x;
            file >> x;
            this->data[i] = x;

        }

        std::sort(this->data.begin(), this->data.end());

        file.close();
    }

    int max() const {
        if (this->data.size() > 0) {
            return this->data[this->data.size() - 1];
        } else {
            throw Exception("array is empty");
        }
    }
    int min() const {
        if (this->data.size() > 0) {
            return this->data[0];
        } else {
            throw Exception("array is empty");
        }
    }

    double mean() const {
        if (this->data.size() > 0) {
            return std::accumulate(
                this->data.begin(), this->data.end(),
                0.0
            )/this->data.size();
        } else {
            throw Exception("array is empty");
        }
    }
    double rms() const {
        if (this->data.size() > 1) {
            double m = this->mean();
            return sqrt(std::accumulate(
                this->data.begin(), this->data.end(),
                0.0, [m](const double &a, const double &x) -> double {
                    return a + (x - m)*(x - m);
                }
            )/(this->data.size() - 1));
        } else {
            throw Exception("array is empty");
        }
    }

    size_t countLarger(int a) const {
        if (this->data.size() <= 0) {
            return 0;
        }

        std::vector<int>::const_iterator i = std::upper_bound(
            this->data.begin(), this->data.end(), a
        );
        return this->data.end() - i;
    }

    void print() const {
        for (int v : this->data) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
};

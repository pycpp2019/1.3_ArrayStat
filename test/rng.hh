#pragma once

#include <utility>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Rng {
private:
    uint32_t state;

public:
    Rng(uint32_t seed) : state(seed) {}

    uint32_t rand_int() {
        return (this->state = 1103515245*this->state + 12345);
    }

    double uniform() {
        return double(this->rand_int())/0x100000000;
    }

    std::pair<double, double> normal() {
        double phi = 2.0*M_PI*this->uniform();
        double r = -log(0.5*(1.0 - this->uniform()));
        return std::make_pair(r*cos(phi), r*sin(phi));
    }
};



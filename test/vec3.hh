#pragma once

#include <cmath>

double norm(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}

class Vec3 {
public:
    int x, y, z;
    Vec3() {}
    Vec3(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
    double norm() const {
        return ::norm(x, y, z);
    }
};

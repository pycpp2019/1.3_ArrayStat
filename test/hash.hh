#pragma once

#include <vector>
#include <functional>

#include "vec3.hh"


class Hasher {
private:
    size_t state;

public:
    Hasher(size_t seed = 0) {
        this->state = seed;
    }

    template <typename T>
    void write(const T &x) {
        std::hash<T> std_hasher;
        this->state ^= std_hasher(x) + 0x9e3779b9 + (this->state << 6) + (this->state >> 2);
    }

    size_t finish() const {
        return this->state;
    }
};

namespace std {
    template<typename T> struct hash<vector<T>> {
        size_t operator()(const vector<T> &v) const {
            Hasher hasher;
            for (const T &x : v) {
                hasher.write(x);
            }
            return hasher.finish();
        }
    };

    template<> struct hash<Vec3> {
        size_t operator()(const Vec3 &v) const {
            Hasher hasher;
            hasher.write(v.x);
            hasher.write(v.y);
            hasher.write(v.z);
            return hasher.finish();
        }
    };
}

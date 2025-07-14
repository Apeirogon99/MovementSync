#include "Vector2.h"
#include <cmath>

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::distance(const Vector2& other) const {
    return (*this - other).length();
}

Vector2 Vector2::normalize() const {
    float len = length();
    if (len > 0) {
        return Vector2(x / len, y / len);
    }
    return Vector2(0, 0);
}
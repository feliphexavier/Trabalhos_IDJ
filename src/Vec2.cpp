#include "Vec2.h"
#include <cmath>

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2::~Vec2() {}

Vec2 Vec2::Sum(Vec2 v) {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::Sub(Vec2 v) {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::Multiply(float scalar) {
    return Vec2(x * scalar, y * scalar);
}

float Vec2::Magnitude() {
    return sqrt(x * x + y * y);
}

Vec2 Vec2::Versor() {
    float mag = Magnitude();
    if (mag == 0) {
        return Vec2(0, 0);
    }
    return Vec2(x / mag, y / mag);
}

float Vec2::Distance(Vec2 v) {
    Vec2 diff = Sub(v);
    return diff.Magnitude();
}

float Vec2::Angle() {
    return atan2(y, x);
}

float Vec2::LineAngle(Vec2 a, Vec2 b) {
    Vec2 diff = b.Sub(a); 
    return diff.Angle();
}

Vec2 Vec2::Rotate(float angle) {
    float newX = x * cos(angle) - y * sin(angle);
    float newY = y * cos(angle) + x * sin(angle);
    return Vec2(newX, newY);
}
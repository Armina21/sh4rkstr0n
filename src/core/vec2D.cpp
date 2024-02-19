#include "vec2D.h"

vec2D::vec2D()  :
    x(0),
    y(0) {
}
vec2D::vec2D(float a, float b)  :
    x(a),
    y(b) {
}


bool vec2D::operator==(const vec2D &v) const  {
    return (x == v.x && y == v.y);
}

bool vec2D::operator!=(const vec2D &v) const  {
    return (x != v.x || y != v.y);
}

void vec2D::operator=(const vec2D &v)  {
    x = v.x;
    y = v.y;
}

vec2D vec2D::operator+(const vec2D &v) const  {
    return { x + v.x, y + v.y };
}

vec2D vec2D::operator*(const vec2D &v) const {
    return { x * v.x, y * v.y };
}

vec2D vec2D::operator-(const vec2D &v) const  {
    return { x - v.x, y - v.y };
}

vec2D vec2D::operator/(const int &v) const  {
    return { x / v, y / v };
}

vec2D vec2D::operator-() {
    return {- x, - y };
}


#include "myvector.hpp"

void Vector2::set(scalar _x, scalar _y) {
    this->x = _x;
    this->y = _y;
}

scalar Vector2::length() const {
#ifdef USING_FLOAT64
    return sqrt(x * x + y * y);
#else
    return sqrtf(x * x + y * y);
#endif
}

scalar Vector2::norm() const {
    return length();
}

scalar Vector2::distance(const Vector2& vec) const {
#ifdef USING_FLOAT64
    return sqrt(x * x + y * y);
#else
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
#endif
}

Vector2 Vector2::normalized() const {
    scalar len = length();
    if (len < MYEPSILON) {
        std::cerr << "Vector2d length is too small" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    } else {
        return Vector2(x / len, y / len);
    }
}

void Vector2::normalize() {
    scalar len = length();
    this->x = x / len;
    this->y = y / len;
}

scalar Vector2::dot(const Vector2& vec) const {
    return (vec.x * x + vec.y * y);
}

bool Vector2::equal(const Vector2& vec, scalar e) const {
    return !((std::abs(vec.x - x) > e) || (std::abs(vec.y - y) > e));
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

//Vector2& Vector2::operator=(Vector2& rhs) const {
//    return rhs;
//}

Vector2 Vector2::operator+(const Vector2& rhs) const {
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
    x = x + rhs.x;
    y = y + rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs) {
    x = x - rhs.x;
    y = y - rhs.y;
    return *this;
}

Vector2 Vector2::operator*(const Vector2& rhs) const {
    return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator*(const scalar scale) const {
    return Vector2(x * scale, y * scale);
}

Vector2& Vector2::operator*=(const Vector2& rhs) {
    x = x * rhs.x;
    y = y * rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(const scalar scale) {
    x = x * scale;
    y = y * scale;
    return *this;
}

Vector2 Vector2::operator/(const scalar scale) const {
    if (std::abs(scale) < MYEPSILON) {
        std::cerr << "scale too smaple" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    }
    return Vector2(x / scale, y / scale);
}

Vector2& Vector2::operator/=(const scalar scale) {
    if (std::abs(scale) < MYEPSILON) {
        std::cerr << "scale too smaple" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    }
    x /= scale;
    y /= scale;
    return *this;
}

bool Vector2::operator==(const Vector2& rhs) const {
    return !((x != rhs.x) || (y != rhs.y));
}

bool Vector2::operator!=(const Vector2& rhs) const {
    return ((x != rhs.x) || (y != rhs.y));
}

bool Vector2::operator<(const Vector2& rhs) const {
    //! possible issue: < > comparison rather than EPISILON
    if (x < rhs.x) return true;
    if (x > rhs.x) return false;
    if (y < rhs.y) return true;
    if (y > rhs.y) return false;
    return false;
}

scalar Vector2::operator[](int index) const {
//  not very clear which case used
//    std::cout << "not reference" << std::endl;
    if (index > 1) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should more than 0";
    }
    return (&x)[index];
}

scalar& Vector2::operator[](int index) {
//  w[0]
//    std::cout << "reference" << std::endl;
    if (index > 1) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should more than 0";
    }
    return (&x)[index];
}

Vector2 operator*(const scalar a, const Vector2 vec) {
    return Vector2(a*vec.x, a*vec.y);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

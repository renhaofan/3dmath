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

scalar Vector2::l2norm() const {
    return length();
}

scalar Vector2::distance(const Vector2& vec) const {
#ifdef USING_FLOAT64
    return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
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
    if (len < MYEPSILON) {
        std::cerr << "Vector2d length is too small" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    } else {
        this->x = x / len;
        this->y = y / len;
    }
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
    return ((x == rhs.x) && (y == rhs.y));
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

bool Vector2::operator>(const Vector2& rhs) const {
    return !(operator<(rhs));
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
    return Vector2(a * vec.x, a * vec.y);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

void Vector3::set(scalar _x, scalar _y, scalar _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

scalar Vector3::length() const {
#ifdef USING_FLOAT64
    return sqrt(x * x + y * y + z * z);
#else
    return sqrtf(x * x + y * y + z * z);
#endif
}

scalar Vector3::l2norm() const {
    return length();
}

scalar Vector3::distance(const Vector3& vec) const {
#ifdef USING_FLOAT64
    return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
#else
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
#endif
}

scalar Vector3::angle(const Vector3& vec) const {
    scalar len = this->length() * vec.length();
    if (len < MYEPSILON) {
        std::cerr << "length is too small" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    } else {
#ifdef USING_FLOAT64
        return acos(this->dot(vec) / len) * (RAD2DEG);
#else
        // acosf return  [0 ; π],
        return acosf(this->dot(vec) / len) * (RAD2DEG);
#endif
    }
}

Vector3 Vector3::normalized() const {
    scalar len = length();
    if (len < MYEPSILON) {
        std::cerr << "Vector2d length is too small" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    } else {
        return Vector3(x / len, y / len, z / len);
    }
}

void Vector3::normalize() {
    scalar len = length();
    if (len < MYEPSILON) {
        std::cerr << "Vector2d length is too small" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    } else {
        this->x = x / len;
        this->y = y / len;
        this->z = z / len;
    }
}

scalar Vector3::dot(const Vector3& vec) const {
    return (x * vec.x + y * vec.y + z * vec.z);
}

Vector3 Vector3::cross(const Vector3& rhs) const {
    return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

bool Vector3::equal(const Vector3& vec, scalar e) const {
    return !((std::abs(vec.x - x) > e) || (std::abs(vec.y - y) > e) || (std::abs(vec.z - z) > e));
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& rhs) const {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3& Vector3::operator+=(const Vector3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3& Vector3::operator-=(const Vector3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3 Vector3::operator*(const Vector3& rhs) const {
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vector3& Vector3::operator*=(const Vector3& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vector3 Vector3::operator*(const scalar scale) const {
    return Vector3(x * scale, y * scale, z * scale);
}

Vector3& Vector3::operator*=(const scalar scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Vector3 Vector3::operator/(const scalar scale) const {
    if (std::abs(scale) < MYEPSILON) {
        std::cerr << "scale too smaple" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    }
    return Vector3(x / scale, y / scale, z / scale);
}

Vector3& Vector3::operator/=(const scalar scale) {
    if (std::abs(scale) < MYEPSILON) {
        std::cerr << "scale too smaple" << std::endl;
        throw "Division by zero condition! norm less than EPSILON";
    }
    x /= scale;
    y /= scale;
    z /= scale;
    return *this;
}

bool Vector3::operator==(const Vector3& rhs) const {
    return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
}

bool Vector3::operator!=(const Vector3& rhs) const {
    return ((x != rhs.x) || (y != rhs.y) || (z != rhs.z));
}

bool Vector3::operator<(const Vector3& rhs) const {
    //! possible issue: < > comparison rather than EPISILON
    if (x < rhs.x) return true;
    if (x > rhs.x) return false;
    if (y < rhs.y) return true;
    if (y > rhs.y) return false;
    if (z < rhs.z) return true;
    if (z > rhs.z) return false;
    return false;
}

bool Vector3::operator>(const Vector3& rhs) const {
    return !(operator<(rhs));
}

scalar Vector3::operator[](int index) const {
    //  not very clear which case used
    //    std::cout << "not reference" << std::endl;
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should more than 0";
    }
    return (&x)[index];
}

scalar& Vector3::operator[](int index) {
    //  w[0]
    //    std::cout << "reference" << std::endl;
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should less than 3";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, index should more than 0";
    }
    return (&x)[index];
}

Vector3 operator*(const scalar a, const Vector3 vec) {
    return Vector3(a * vec.x, a * vec.y, a * vec.z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

#include "mymatrix.hpp"

Matrix2::Matrix2() {
    identity();
}

Matrix2::Matrix2(const scalar* src) {
    set(src);
}

Matrix2::Matrix2(scalar m0, scalar m1, scalar m2, scalar m3) {
    set(m0, m1, m2, m3);
}

void Matrix2::set(const scalar* src) {
    m[0] = src[0];
    m[1] = src[1];
    m[2] = src[2];
    m[3] = src[3];
}

void Matrix2::set(scalar m0, scalar m1, scalar m2, scalar m3) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = m3;
}

void Matrix2::setRow(int index, const scalar* row) {
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, seteRow index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, seteRow index should more than 0";
    }
    m[index] = row[0];
    m[index + 2] = row[1];
}

void Matrix2::setRow(int index, const Vector2& v) {
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, setRow index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, setRow index should more than 0";
    }
    m[index] = v.x;
    m[index + 2] = v.y;
}

void Matrix2::setColumn(int index, const scalar* col) {
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, setColumn index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, setColumn index should more than 0";
    }
    m[index * 2] = col[0];
    m[index * 2 + 1] = col[1];
}

void Matrix2::setColumn(int index, const Vector2 &v) {
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, setColumn index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, setColumn index should more than 0";
    }
    m[index * 2] = v[0];
    m[index * 2 + 1] = v[1];
}

const scalar* Matrix2::data() const {
    return m;
}

const scalar* Matrix2::dataTranspose() {
    mt[0] = m[0];
    mt[1] = m[2];
    mt[2] = m[1];
    mt[3] = m[3];
    return mt;
}

const scalar* Matrix2::get() const {
    return this->data();
}

const scalar* Matrix2::getTranspose() {
    return this->dataTranspose();
}

Vector2 Matrix2::getRow(int index) const {
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, getRow index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, getRow index should more than 0";
    }
    return Vector2(m[index], m[index+2]);
}

Vector2 Matrix2::getColumn(int index) const {
    if (index > 2) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, getColumn index should less than 2";
    }
    if (index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds, getColumn index should more than 0";
    }
    return Vector2(m[index*2], m[index*2+1]);
}

scalar Matrix2::getDeterminant() const {
    return (m[0] * m[3] - m[1] * m[2]);
}

scalar Matrix2::getAngle(ANGLEUNIT unit) const {
    // atan2 return in the interval [-pi,+pi] radians.
    // R = | cos  -sin|
    //   = | sin   cos|
    // angle = atan2 (sin/cos)
    scalar u = (unit == RAD) ? 1 : (RAD2DEG);
#ifdef USING_FLOAT64
    return atan2(m[1], m[0]) * u;
#else
    return atan2f(m[1],  m[0]) * u;
#endif
}

Matrix2& Matrix2::identity() {
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 1;
    return *this;
}

Matrix2& Matrix2::transpose() {
    std::swap(m[1], m[2]);
    return *this;
}

Matrix2& Matrix2::inverse() {
    // try to compute inverse matirx, if not return identity
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        std::cout << "Inverse matrix not exists, return Identity." << std::endl;
        return identity();
    }
    std::swap(m[0], m[3]);
    m[1] = -m[1];
    m[2] = -m[2];
    det = 1 / det;
    m[0] *= det;
    m[1] *= det;
    m[2] *= det;
    m[3] *= det;
    return *this;
}

Matrix2 Matrix2::operator-() const {
    return Matrix2(-m[0], -m[1], -m[2], -m[3]);
}




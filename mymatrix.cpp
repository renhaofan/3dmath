#include "mymatrix.hpp"

Matrix2::Matrix2() {
    identity();
}

Matrix2::Matrix2(const scalar src[4]) {
    set(src);
}

Matrix2::Matrix2(scalar m0, scalar m1, scalar m2, scalar m3) {
    set(m0, m1, m2, m3);
}

Matrix2::Matrix2(const Matrix2& mat2) {
    // std::cout << "invoke ctor aka copy constructor" << std::endl;
    m[0] = mat2[0];
    m[1] = mat2[1];
    m[2] = mat2[2];
    m[3] = mat2[3];
}

Matrix2& Matrix2::operator=(const Matrix2& mat2) {
    // std::cout << "invoke copy assignment operator" << std::endl;
    if (this == &mat2) {
        return *this;
    }
    m[0] = mat2[0];
    m[1] = mat2[1];
    m[2] = mat2[2];
    m[3] = mat2[3];
    return *this;
}

void Matrix2::set(const scalar src[4]) {
    if ((src == nullptr) || ((src + 1) == nullptr) ||
        ((src + 2) == nullptr) || ((src + 3) == nullptr)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Data pointer error.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Data pointer error.";
    }
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

void Matrix2::setRow(int index, const scalar row[2]) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }

    if ((row == nullptr) || ((row + 1) == nullptr)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Data pointer error.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Data pointer error.";
    }

    m[index] = row[0];
    m[index + 2] = row[1];
}

void Matrix2::setRow(int index, const Vector2& v) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index] = v.x;
    m[index + 2] = v.y;
}

void Matrix2::setColumn(int index, const scalar col[2]) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }

    if ((col == nullptr) || ((col + 1) == nullptr)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Data pointer error.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Data pointer error.";
    }

    m[index * 2] = col[0];
    m[index * 2 + 1] = col[1];
}

void Matrix2::setColumn(int index, const Vector2& v) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index * 2] = v.x;
    m[index * 2 + 1] = v.y;
}

scalar* Matrix2::data() {
    return m;
}

scalar* Matrix2::dataTranspose() {
    mt[0] = m[0];
    mt[1] = m[2];
    mt[2] = m[1];
    mt[3] = m[3];
    return mt;
}

const scalar* Matrix2::get() const {
    return m;
}

const scalar* Matrix2::getTranspose() {
    mt[0] = m[0];
    mt[1] = m[2];
    mt[2] = m[1];
    mt[3] = m[3];
    return mt;
}

Vector2 Matrix2::getRow(int index) const {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector2(m[index], m[index + 2]);
}

Vector2 Matrix2::getColumn(int index) const {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector2(m[index * 2], m[index * 2 + 1]);
}

scalar Matrix2::getDeterminant() const {
    return (m[0] * m[3] - m[1] * m[2]);
}

scalar Matrix2::getAngle(ANGLEUNIT unit) const {
    // atan2 return in the interval [-pi,+pi] radians.
    // R = | cos  -sin|
    //   = | sin   cos|
    // angle = atan2 (sin/cos)
    if (std::abs(getDeterminant() - 1) > MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Not a rotation matrix.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Not a rotation matrix!";
    }
    scalar u = (unit == RAD) ? 1 : (RAD2DEG);
#ifdef USING_FLOAT64
    return atan2(m[1], m[0]) * u;
#else
    return atan2f(m[1], m[0]) * u;
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
    // try to compute inverse matirx
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Inverse matrix not exists, return Identity.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Inverse matrix not exists!";
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

Matrix2 Matrix2::operator+(const Matrix2& rhs) const {
    return Matrix2(m[0] + rhs[0], m[1] + rhs[1],
                   m[2] + rhs[2], m[3] + rhs[3]);
}

Matrix2& Matrix2::operator+=(const Matrix2& rhs) {
    m[0] += rhs[0];
    m[1] += rhs[1];
    m[2] += rhs[2];
    m[3] += rhs[3];
    return *this;
}

Matrix2 Matrix2::operator-(const Matrix2& rhs) const {
    return Matrix2(m[0] - rhs[0], m[1] - rhs[1],
                   m[2] - rhs[2], m[3] - rhs[3]);
}

Matrix2& Matrix2::operator-=(const Matrix2& rhs) {
    m[0] -= rhs[0];
    m[1] -= rhs[1];
    m[2] -= rhs[2];
    m[3] -= rhs[3];
    return *this;
}

Vector2 Matrix2::operator*(const Vector2& rhs) const {
    return Vector2(m[0] * rhs.x + m[2] * rhs.y,
                   m[1] * rhs.x + m[3] * rhs.y);
}

Matrix2 Matrix2::operator*(const Matrix2& rhs) const {
    return Matrix2(m[0] * rhs[0] + m[2] * rhs[1], m[1] * rhs[0] + m[3] * rhs[1],
                   m[0] * rhs[2] + m[2] * rhs[3], m[1] * rhs[2] + m[3] * rhs[3]);
}

Matrix2 Matrix2::operator*(const scalar& rhs) {
    return Matrix2(m[0] * rhs, m[1] * rhs, m[2] * rhs, m[3] * rhs);
}

Matrix2& Matrix2::operator*=(const Matrix2& rhs) {
    *this = (*this) * rhs;
    return *this;
}

bool Matrix2::equal(const Matrix2& rhs, scalar e) const {
    return (std::abs(m[0] - rhs[0]) < e) && (std::abs(m[2] - rhs[2]) < e) && (std::abs(m[1] - rhs[1]) < e) && (std::abs(m[3] - rhs[3]) < e);
}

bool Matrix2::operator==(const Matrix2& rhs) const {
    return (m[0] == rhs[0]) && (m[2] == rhs[2]) && (m[1] == rhs[1]) && (m[3] == rhs[3]);
}

bool Matrix2::operator!=(const Matrix2& rhs) const {
    return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) || (m[3] != rhs[3]);
}

scalar Matrix2::operator[](int index) const {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[index];
}

scalar& Matrix2::operator[](int index) {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[index];
}

scalar Matrix2::operator()(int i, int j) const {
    if ((i < 0) || (i > 1) || (j < 0) || (j > 1)) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds!";
    }
    return m[j * 2 + i];
}

scalar& Matrix2::operator()(int i, int j) {
    if ((i < 0) || (i > 1) || (j < 0) || (j > 1)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[j * 2 + i];
}

Matrix2 operator-(const Matrix2& mat2) {
    // std::cout << "friend operator-" << std::endl;
    return Matrix2(-mat2[0], -mat2[1], -mat2[2], -mat2[3]);
}

Matrix2 operator*(const scalar& s, const Matrix2& mat2) {
    return Matrix2(s * mat2[0], s * mat2[1], s * mat2[2], s * mat2[3]);
}

Vector2 operator*(const Vector2& vec, const Matrix2& mat2) {
    return Vector2(vec.x * mat2[0] + vec.y * mat2[1],
                   vec.x * mat2[2] + vec.y * mat2[3]);
}

std::ostream& operator<<(std::ostream& os, const Matrix2& mat2) {
    os << std::fixed << std::setprecision(6);
    os << "[" << std::setw(10) << mat2[0] << " " << std::setw(10) << mat2[2] << "]\n"
       << "[" << std::setw(10) << mat2[1] << " " << std::setw(10) << mat2[3] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

#include "mymatrix.hpp"

Matrix2::Matrix2() {
    setIdentity();
}

Matrix2::Matrix2(const scalar src[4]) {
    set(src);
}

Matrix2::Matrix2(scalar m0, scalar m1, scalar m2, scalar m3) {
    set(m0, m1, m2, m3);
}

Matrix2::Matrix2(const Matrix2& mat2) {
    //    std::cout << "invoke ctor aka copy constructor" << std::endl;
    m[0] = mat2[0];
    m[1] = mat2[1];
    m[2] = mat2[2];
    m[3] = mat2[3];
}

Matrix2& Matrix2::operator=(const Matrix2& mat2) {
    //    std::cout << "invoke copy assignment operator" << std::endl;
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
    m[0] = src[0];
    m[1] = src[1];
    m[2] = src[2];
    m[3] = src[3];
}

void Matrix2::set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = m3;
}

void Matrix2::setRow(int index, const scalar row[2]) {
    if ((index > 1) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index] = row[0];
    m[index + 2] = row[1];
}

void Matrix2::setRow(int index, const Vector2& v) {
    if ((index > 1) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index] = v.x;
    m[index + 2] = v.y;
}

void Matrix2::setColumn(int index, const scalar col[2]) {
    if ((index > 1) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index * 2] = col[0];
    m[index * 2 + 1] = col[1];
}

void Matrix2::setColumn(int index, const Vector2& v) {
    if ((index > 1) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index * 2] = v.x;
    m[index * 2 + 1] = v.y;
}

void Matrix2::setIdentity() {
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 1;
}

void Matrix2::setRotatonMatrix(const scalar& angle, ANGLEUNIT unit) {
    scalar u = (unit == DEG) ? DEG2RAD : (1);
    m[0] = std::cos(angle * u);
    m[1] = std::sin(angle * u);
    m[2] = -m[1];
    m[3] = m[0];
}

scalar* Matrix2::data() {
    return m;
}

const scalar* Matrix2::constData() const {
    return m;
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
    if (!this->isRotationMatrix()) {
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

bool Matrix2::isRotationMatrix() const {
    // determinant == 1
    if (std::abs(getDeterminant() - 1) > MYEPSILON) return false;
    // unit column vector groups
    if (std::abs(this->getColumn(0).dot(this->getColumn(1))) > MYEPSILON) return false;
    if (std::abs(this->getColumn(0).norm() - 1) > MYEPSILON) return false;
    if (std::abs(this->getColumn(1).norm() - 1) > MYEPSILON) return false;
    return true;
}

void Matrix2::inverse() {
    // try to compute inverse matirx
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Inverse matrix not exists.\n",
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
}

Matrix2 Matrix2::computeInverse() const {
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Inverse matrix not exists.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Inverse matrix not exists!";
    }
    Matrix2 tmp(m[3], -m[1], -m[2], m[0]);
    det = 1 / det;
    tmp *= det;
    return tmp;
}

bool Matrix2::isInversed() const {
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        return false;
    }
    return true;
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

Matrix2 Matrix2::matmul(const Matrix2& rhs) const {
    return Matrix2(m[0] * rhs[0] + m[2] * rhs[1], m[1] * rhs[0] + m[3] * rhs[1],
                   m[0] * rhs[2] + m[2] * rhs[3], m[1] * rhs[2] + m[3] * rhs[3]);
}

Vector2 Matrix2::operator*(const Vector2& rhs) const {
    return Vector2(m[0] * rhs.x + m[2] * rhs.y,
                   m[1] * rhs.x + m[3] * rhs.y);
}

Matrix2 Matrix2::operator*(const Matrix2& rhs) const {
    return Matrix2(m[0] * rhs[0], m[1] * rhs[1],
                   m[2] * rhs[2], m[3] * rhs[3]);
}

Matrix2 Matrix2::operator*(const scalar& rhs) {
    return Matrix2(m[0] * rhs, m[1] * rhs, m[2] * rhs, m[3] * rhs);
}

Matrix2& Matrix2::operator*=(const Matrix2& rhs) {
    *this = (*this) * rhs;
    return *this;
}

Matrix2 Matrix2::operator/(const scalar& rhs) const {
    if (std::abs(rhs) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Division by zero condition.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Division by zero condition!";
    }
    Matrix2 ret(m[0], m[1], m[2], m[3]);
    return ret * (1 / rhs);
}

Matrix2& Matrix2::operator/=(const scalar& rhs) {
    if (std::abs(rhs) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Division by zero condition.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Division by zero condition!";
    }
    *this = (*this) / rhs;
    return *this;
}

Matrix2& Matrix2::operator*=(const scalar& rhs) {
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
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
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

Matrix3::Matrix3() {
    setIdentity();
}

Matrix3::Matrix3(const scalar src[9]) {
    set(src);
}

Matrix3::Matrix3(scalar m0, scalar m1, scalar m2,
                 scalar m3, scalar m4, scalar m5,
                 scalar m6, scalar m7, scalar m8) {
    set(m0, m1, m2,
        m3, m4, m5,
        m6, m7, m8);
}

Matrix3::Matrix3(const Matrix3& mat3) {
    for (int i = 0; i < 9; i++)
        m[i] = mat3[i];
}

Matrix3& Matrix3::operator=(const Matrix3& mat3) {
    if (this == &mat3) {
        return *this;
    }
    for (int i = 0; i < 9; i++)
        m[i] = mat3[i];
    return *this;
}

void Matrix3::set(const scalar src[9]) {
    for (int i = 0; i < 9; i++)
        m[i] = src[i];
}

void Matrix3::set(const scalar& m0, const scalar& m1, const scalar& m2,
                  const scalar& m3, const scalar& m4, const scalar& m5,
                  const scalar& m6, const scalar& m7, const scalar& m8) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = m3;
    m[4] = m4;
    m[5] = m5;
    m[6] = m6;
    m[7] = m7;
    m[8] = m8;
}

void Matrix3::setRow(int index, const scalar data[3]) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index] = data[0];
    m[index + 3] = data[1];
    m[index + 6] = data[2];
}

void Matrix3::setRow(int index, const Vector3& v) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index] = v[0];
    m[index + 3] = v[1];
    m[index + 6] = v[2];
}

void Matrix3::setColumn(int index, const scalar data[3]) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index * 3] = data[0];
    m[index * 3 + 1] = data[1];
    m[index * 3 + 2] = data[2];
}

void Matrix3::setColumn(int index, const Vector3& v) {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    m[index * 3] = v[0];
    m[index * 3 + 1] = v[1];
    m[index * 3 + 2] = v[2];
}

void Matrix3::setIdentity() {
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    m[4] = 1;
    m[5] = 0;
    m[6] = 0;
    m[7] = 0;
    m[8] = 1;
}

void Matrix3::setRotationMatrix(const Vector3& axis, const scalar& angle,
                                ANGLEUNIT unit) {
    this->au = unit;
    scalar u = (this->au == RAD) ? 1 : (DEG2RAD);

    Vector3 nv = axis.normalized();
    scalar cos = std::cos(angle * u);
    scalar sin = std::sin(angle * u);
    // shorthand
    scalar n_cos = 1 - cos;
    scalar xy = nv.x * nv.y;
    scalar yz = nv.y * nv.z;
    scalar xz = nv.x * nv.z;
    scalar xy_c = xy * n_cos;
    scalar yz_c = yz * n_cos;
    scalar xz_c = xz * n_cos;
    scalar xsin = nv.x * sin;
    scalar ysin = nv.y * sin;
    scalar zsin = nv.z * sin;
    // the first column
    m[0] = nv.x * nv.x * n_cos + cos;
    m[1] = xy_c + zsin;
    m[2] = xz_c - ysin;
    // the second column
    m[3] = xy_c - zsin;
    m[4] = nv.y * nv.y * n_cos + cos;
    m[5] = yz_c + xsin;
    // the third column
    m[6] = xz_c + ysin;
    m[7] = yz_c - xsin;
    m[8] = nv.z * nv.z * n_cos + cos;
}

scalar* Matrix3::data() {
    return m;
}

const scalar* Matrix3::constData() const {
    return m;
}

Vector3 Matrix3::getRow(int index) const {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector3(m[index], m[index + 3], m[index + 6]);
}

Vector3 Matrix3::getColumn(int index) const {
    if ((index > 2) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector3(m[index * 3], m[index * 3 + 1], m[index * 3 + 2]);
}

scalar Matrix3::getDeterminant() const {
    return (m[0] * (m[4] * m[8] - m[5] * m[7])
            - m[1] * (m[3] * m[8] - m[5] * m[6])
            + m[2] * (m[3] * m[7] + m[4] * m[6]));
}

bool Matrix3::isRotationMatrix() const {
    // determinant == 1
    if (std::abs(this->getDeterminant() - 1) > MYEPSILON) return false;
    Vector3 v0 = this->getColumn(0);
    Vector3 v1 = this->getColumn(1);
    Vector3 v2 = this->getColumn(2);
    // unit column vector groups
    if (std::abs(v0.dot(v1)) > MYEPSILON) return false;
    if (std::abs(v0.dot(v2)) > MYEPSILON) return false;
    if (std::abs(v1.dot(v2)) > MYEPSILON) return false;
    if (std::abs(v0.norm() - 1) > MYEPSILON) return false;
    if (std::abs(v1.norm() - 1) > MYEPSILON) return false;
    if (std::abs(v2.norm() - 1) > MYEPSILON) return false;
    return true;
}

void Matrix3::transpose() {
    std::swap(m[1], m[3]);
    std::swap(m[2], m[6]);
    std::swap(m[5], m[7]);
}

Matrix3 Matrix3::transposed() const {
    return Matrix3(m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8]);
}

void Matrix3::inverse() {
    // M^-1 = adj(M) / det(M)
    //        | m4m8-m5m7  m5m6-m3m8  m3m7-m4m6 |
    //      = | m7m2-m8m1  m0m8-m2m6  m6m1-m7m0 | / det(M)
    //        | m1m5-m2m4  m2m3-m0m5  m0m4-m1m3 |
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Determinant is zero.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Determinant is zero!";
    }
    scalar inv_det = 1.f / det;
    scalar tmp[9];
    tmp[0] = m[4] * m[8] - m[5] * m[7];
    tmp[1] = m[7] * m[2] - m[8] * m[1];
    tmp[2] = m[1] * m[5] - m[2] * m[4];
    tmp[3] = m[5] * m[6] - m[3] * m[8];
    tmp[4] = m[0] * m[8] - m[2] * m[6];
    tmp[5] = m[2] * m[3] - m[0] * m[5];
    tmp[6] = m[3] * m[7] - m[4] * m[6];
    tmp[7] = m[6] * m[1] - m[7] * m[0];
    tmp[8] = m[0] * m[4] - m[1] * m[3];
    m[0] = inv_det * tmp[0];
    m[1] = inv_det * tmp[1];
    m[2] = inv_det * tmp[2];
    m[3] = inv_det * tmp[3];
    m[4] = inv_det * tmp[4];
    m[5] = inv_det * tmp[5];
    m[6] = inv_det * tmp[6];
    m[7] = inv_det * tmp[7];
    m[8] = inv_det * tmp[8];
}

Matrix3 Matrix3::computeInverse() const {
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Determinant is zero.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Determinant is zero!";
    }
    scalar inv_det = 1.f / det;
    scalar tmp[9];
    tmp[0] = m[4] * m[8] - m[5] * m[7];
    tmp[1] = m[7] * m[2] - m[8] * m[1];
    tmp[2] = m[1] * m[5] - m[2] * m[4];
    tmp[3] = m[5] * m[6] - m[3] * m[8];
    tmp[4] = m[0] * m[8] - m[2] * m[6];
    tmp[5] = m[2] * m[3] - m[0] * m[5];
    tmp[6] = m[3] * m[7] - m[4] * m[6];
    tmp[7] = m[6] * m[1] - m[7] * m[0];
    tmp[8] = m[0] * m[4] - m[1] * m[3];
    tmp[0] = inv_det * tmp[0];
    tmp[1] = inv_det * tmp[1];
    tmp[2] = inv_det * tmp[2];
    tmp[3] = inv_det * tmp[3];
    tmp[4] = inv_det * tmp[4];
    tmp[5] = inv_det * tmp[5];
    tmp[6] = inv_det * tmp[6];
    tmp[7] = inv_det * tmp[7];
    tmp[8] = inv_det * tmp[8];
    return Matrix3(tmp[0], tmp[1], tmp[2],
                   tmp[3], tmp[4], tmp[5],
                   tmp[6], tmp[7], tmp[8]);
}

bool Matrix3::isInversed() const {
    scalar det = this->getDeterminant();
    if (std::abs(det) < MYEPSILON) {
        return false;
    } else {
        return true;
    }
}

Matrix3 Matrix3::operator+(const Matrix3& rhs) const {
    return Matrix3(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
                   m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
                   m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
}

Matrix3& Matrix3::operator+=(const Matrix3& rhs) {
    m[0] = m[0] + rhs[0];
    m[1] = m[1] + rhs[1];
    m[2] = m[2] + rhs[2];
    m[3] = m[3] + rhs[3];
    m[4] = m[4] + rhs[4];
    m[5] = m[5] + rhs[5];
    m[6] = m[6] + rhs[6];
    m[7] = m[7] + rhs[7];
    m[8] = m[8] + rhs[8];
    return *this;
}

Matrix3 Matrix3::operator-(const Matrix3& rhs) const {
    return Matrix3(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
                   m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
                   m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
}

Matrix3& Matrix3::operator-=(const Matrix3& rhs) {
    m[0] = m[0] - rhs[0];
    m[1] = m[1] - rhs[1];
    m[2] = m[2] - rhs[2];
    m[3] = m[3] - rhs[3];
    m[4] = m[4] - rhs[4];
    m[5] = m[5] - rhs[5];
    m[6] = m[6] - rhs[6];
    m[7] = m[7] - rhs[7];
    m[8] = m[8] - rhs[8];
    return *this;
}

Matrix3 Matrix3::matmul(const Matrix3& rhs) const {
    // | 0 3 6 |   | 0 3 6 |
    // | 1 4 7 | * | 1 4 7 |
    // | 2 5 8 |   | 2 5 8 |
    return Matrix3(m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2], m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2], m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
                   m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5], m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5], m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
                   m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8], m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8], m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]);
}

Vector3 Matrix3::operator*(const Vector3& rhs) const {
    return Vector3(m[0] * rhs.x + m[3] * rhs.y + m[6] * rhs.z,
                   m[1] * rhs.x + m[4] * rhs.y + m[7] * rhs.z,
                   m[2] * rhs.x + m[5] * rhs.y + m[8] * rhs.z);
}

Matrix3 Matrix3::operator*(const Matrix3& rhs) const {
    return Matrix3(m[0] * rhs[0], m[1] * rhs[1], m[2] * rhs[2],
                   m[3] * rhs[3], m[4] * rhs[4], m[5] * rhs[5],
                   m[6] * rhs[6], m[7] * rhs[7], m[8] * rhs[8]);
}

Matrix3 Matrix3::operator*(const scalar& rhs) {
    return Matrix3(m[0] * rhs, m[1] * rhs, m[2] * rhs,
                   m[3] * rhs, m[4] * rhs, m[5] * rhs,
                   m[6] * rhs, m[7] * rhs, m[8] * rhs);
}

Matrix3& Matrix3::operator*=(const Matrix3& rhs) {
    m[0] *= rhs[0];
    m[1] *= rhs[1];
    m[2] *= rhs[2];
    m[3] *= rhs[3];
    m[4] *= rhs[4];
    m[5] *= rhs[5];
    m[6] *= rhs[6];
    m[7] *= rhs[7];
    m[8] *= rhs[8];
    return *this;
}

Matrix3& Matrix3::operator*=(const scalar& rhs) {
    m[0] *= rhs;
    m[1] *= rhs;
    m[2] *= rhs;
    m[3] *= rhs;
    m[4] *= rhs;
    m[5] *= rhs;
    m[6] *= rhs;
    m[7] *= rhs;
    m[8] *= rhs;
    return *this;
}

Matrix3 Matrix3::operator/(const scalar& rhs) const {
    if (std::abs(rhs) > MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Division by zero condition.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Division by zero condition!";
    }
    return Matrix3(m[0] / rhs, m[1] / rhs, m[2] / rhs,
                   m[3] / rhs, m[4] / rhs, m[5] / rhs,
                   m[6] / rhs, m[7] / rhs, m[8] / rhs);
}

Matrix3& Matrix3::operator/=(const scalar& rhs) {
    if (std::abs(rhs) > MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Division by zero condition.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Division by zero condition!";
    }
    m[0] /= rhs;
    m[1] /= rhs;
    m[2] /= rhs;
    m[3] /= rhs;
    m[4] /= rhs;
    m[5] /= rhs;
    m[6] /= rhs;
    m[7] /= rhs;
    m[8] /= rhs;
    return *this;
}

bool Matrix3::equal(const Matrix3& rhs, scalar e) const {
    if (std::abs(m[0] - rhs[0]) > e) return false;
    if (std::abs(m[1] - rhs[1]) > e) return false;
    if (std::abs(m[2] - rhs[2]) > e) return false;
    if (std::abs(m[3] - rhs[3]) > e) return false;
    if (std::abs(m[4] - rhs[4]) > e) return false;
    if (std::abs(m[5] - rhs[5]) > e) return false;
    if (std::abs(m[6] - rhs[6]) > e) return false;
    if (std::abs(m[7] - rhs[7]) > e) return false;
    if (std::abs(m[8] - rhs[8]) > e) return false;
    return true;
}

bool Matrix3::operator==(const Matrix3& rhs) const {
    if (m[0] != rhs[0]) return false;
    if (m[1] != rhs[1]) return false;
    if (m[2] != rhs[2]) return false;
    if (m[3] != rhs[3]) return false;
    if (m[4] != rhs[4]) return false;
    if (m[5] != rhs[5]) return false;
    if (m[6] != rhs[6]) return false;
    if (m[7] != rhs[7]) return false;
    if (m[8] != rhs[8]) return false;
    return true;
}

bool Matrix3::operator!=(const Matrix3& rhs) const {
    if (m[0] == rhs[0]) return false;
    if (m[1] == rhs[1]) return false;
    if (m[2] == rhs[2]) return false;
    if (m[3] == rhs[3]) return false;
    if (m[4] == rhs[4]) return false;
    if (m[5] == rhs[5]) return false;
    if (m[6] == rhs[6]) return false;
    if (m[7] == rhs[7]) return false;
    if (m[8] == rhs[8]) return false;
    return true;
}

scalar Matrix3::operator[](int index) const {
    if ((index > 8) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[index];
}

scalar& Matrix3::operator[](int index) {
    if ((index > 8) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[index];
}

scalar Matrix3::operator()(int i, int j) const {
    if ((i < 0) || (i > 2) || (j < 0) || (j > 2)) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds!";
    }
    return m[j * 3 + i];
}

scalar& Matrix3::operator()(int i, int j) {
    if ((i < 0) || (i > 2) || (j < 0) || (j > 2)) {
        std::cerr << "Index out of bounds" << std::endl;
        throw "Index out of bounds!";
    }
    return m[j * 3 + i];
}

Matrix3 operator-(const Matrix3& mat3) {
    return Matrix3(-mat3[0], -mat3[1], -mat3[2],
                   -mat3[3], -mat3[4], -mat3[5],
                   -mat3[6], -mat3[7], -mat3[8]);
}

Matrix3 operator*(const scalar& s, const Matrix3& mat3) {
    return Matrix3(s * mat3[0], s * mat3[1], s * mat3[2],
                   s * mat3[3], s * mat3[4], s * mat3[5],
                   s * mat3[6], s * mat3[7], s * mat3[8]);
}

Vector3 operator*(const Vector3& vec, const Matrix3& mat3) {
    return Vector3(vec.x*mat3[0] + vec.y*mat3[1] + vec.z*mat3[2],  vec.x*mat3[3] + vec.y*mat3[4] + vec.z*mat3[5],  vec.x*mat3[6] + vec.y*mat3[7] + vec.z*mat3[8]);
}

std::ostream& operator<<(std::ostream& os, const Matrix3& mat3) {
    os << std::fixed << std::setprecision(6);
    os << "[" << std::setw(10) << mat3[0] << " " << std::setw(10) << mat3[3] << " " << std::setw(10) << mat3[6] << "]\n"
       << "[" << std::setw(10) << mat3[1] << " " << std::setw(10) << mat3[4] << " " << std::setw(10) << mat3[7] << "]\n"
       << "[" << std::setw(10) << mat3[2] << " " << std::setw(10) << mat3[5] << " " << std::setw(10) << mat3[8] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

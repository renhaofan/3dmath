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
    if ((index > 1) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector2(m[index], m[index + 2]);
}

Vector2 Matrix2::getColumn(int index) const {
    if ((index > 1) || (index < 0)) {
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

Matrix4 Matrix3::toHomogenous() const {
    return Matrix4(m[0], m[1], m[2], 0.f,
                   m[3], m[4], m[5], 0.f,
                   m[6], m[7], m[8], 0.f,
                   0.f, 0.f, 0.f, 1.f);
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
    return Vector3(vec.x * mat3[0] + vec.y * mat3[1] + vec.z * mat3[2], vec.x * mat3[3] + vec.y * mat3[4] + vec.z * mat3[5], vec.x * mat3[6] + vec.y * mat3[7] + vec.z * mat3[8]);
}

std::ostream& operator<<(std::ostream& os, const Matrix3& mat3) {
    os << std::fixed << std::setprecision(6);
    os << "[" << std::setw(10) << mat3[0] << " " << std::setw(10) << mat3[3] << " " << std::setw(10) << mat3[6] << "]\n"
       << "[" << std::setw(10) << mat3[1] << " " << std::setw(10) << mat3[4] << " " << std::setw(10) << mat3[7] << "]\n"
       << "[" << std::setw(10) << mat3[2] << " " << std::setw(10) << mat3[5] << " " << std::setw(10) << mat3[8] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

scalar Matrix4::getCofactor(scalar m0, scalar m1, scalar m2,
                            scalar m3, scalar m4, scalar m5,
                            scalar m6, scalar m7, scalar m8) const {
    return m0 * (m4 * m8 - m5 * m7) -
           m1 * (m3 * m8 - m5 * m6) +
           m2 * (m3 * m7 - m4 * m6);
}

Matrix4::Matrix4() {
    setIdentity();
}

Matrix4::Matrix4(const scalar src[16]) {
    set(src);
}

Matrix4::Matrix4(scalar m0, scalar m1, scalar m2, scalar m3,
                 scalar m4, scalar m5, scalar m6, scalar m7,
                 scalar m8, scalar m9, scalar m10, scalar m11,
                 scalar m12, scalar m13, scalar m14, scalar m15) {
    set(m0, m1, m2, m3,
        m4, m5, m6, m7,
        m8, m9, m10, m11,
        m12, m13, m14, m15);
}

Matrix4::Matrix4(const Matrix4& mat4) {
    for (int i = 0; i < 16; i++)
        m[i] = mat4[i];
}

Matrix4& Matrix4::operator=(const Matrix4& mat4) {
    if (this == &mat4) {
        return *this;
    }
    for (int i = 0; i < 16; i++)
        m[i] = mat4[i];
    return *this;
}

void Matrix4::set(const scalar src[16]) {
    for (int i = 0; i < 16; i++)
        m[i] = src[i];
}

void Matrix4::set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
                  const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
                  const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
                  const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15) {
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m03;
    m[4] = m04;
    m[5] = m05;
    m[6] = m06;
    m[7] = m07;
    m[8] = m08;
    m[9] = m09;
    m[10] = m10;
    m[11] = m11;
    m[12] = m12;
    m[13] = m13;
    m[14] = m14;
    m[15] = m15;
}

void Matrix4::setRow(int index, const scalar data[4]) {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    for (int i = 0; i < 4; ++i) {
        m[index + 4 * i] = data[i];
    }
}

void Matrix4::setRow(int index, const Vector4& v) {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    for (int i = 0; i < 4; ++i) {
        m[index + 4 * i] = v[i];
    }
}

void Matrix4::setColumn(int index, const scalar data[4]) {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    for (int i = 0; i < 4; ++i) {
        m[index * 4 + i] = data[i];
    }
}

void Matrix4::setColumn(int index, const Vector4& v) {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    for (int i = 0; i < 4; ++i) {
        m[index * 4 + i] = v[i];
    }
}

void Matrix4::setIdentity() {
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
}

scalar* Matrix4::data() {
    return m;
}

const scalar* Matrix4::constData() const {
    return m;
}

Vector4 Matrix4::getRow(int index) const {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector4(m[index], m[index + 4], m[index + 8], m[index + 12]);
}

Vector4 Matrix4::getColumn(int index) const {
    if ((index > 3) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return Vector4(m[index * 4], m[index * 4 + 1], m[index * 4 + 2], m[index * 4 + 3]);
}

scalar Matrix4::getDeterminant() const {
    return (m[0] * getCofactor(m[5],m[6],m[7], m[9],m[10],m[11], m[13],m[14],m[15])
            - m[1] * getCofactor(m[4],m[6],m[7], m[8],m[10],m[11], m[12],m[14],m[15])
            + m[2] * getCofactor(m[4],m[5],m[7], m[8],m[9], m[11], m[12],m[13],m[15])
            - m[3] * getCofactor(m[4],m[5],m[6], m[8],m[9], m[10], m[12],m[13],m[14]));
}

bool Matrix4::isRotationMatrix() const {
    if (std::abs(m[3]) > MYEPSILON) return false;
    if (std::abs(m[7]) > MYEPSILON) return false;
    if (std::abs(m[11]) > MYEPSILON) return false;
    if (std::abs(m[12]) > MYEPSILON) return false;
    if (std::abs(m[13]) > MYEPSILON) return false;
    if (std::abs(m[14]) > MYEPSILON) return false;
    if (std::abs(m[15] - 1) > MYEPSILON) return false;
    Matrix3 tmp(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
    return tmp.isRotationMatrix();
}

bool Matrix4::isEuclideanMatrix() const {
    if (std::abs(m[3]) > MYEPSILON) return false;
    if (std::abs(m[7]) > MYEPSILON) return false;
    if (std::abs(m[11]) > MYEPSILON) return false;
    if (std::abs(m[15] - 1) > MYEPSILON) return false;

    Matrix3 tmp(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
    if ((std::abs(tmp.getDeterminant()) - 1.f) > MYEPSILON) return false;
    return true;
}

bool Matrix4::isAffineMatrix() const {
    if (std::abs(m[3]) > MYEPSILON) return false;
    if (std::abs(m[7]) > MYEPSILON) return false;
    if (std::abs(m[11]) > MYEPSILON) return false;
    if (std::abs(m[15] - 1) > MYEPSILON) return false;
    Matrix3 tmp(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
    if (std::abs(tmp.getDeterminant())  > MYEPSILON) return false;
    return true;
}

bool Matrix4::isPeojectiveMatrix() const {
    if(std::abs(m[0] * m[5] - m[1] * m[4]) > MYEPSILON) return false;
    return true;
}

void Matrix4::transpose() {
    std::swap(m[1],  m[4]);
    std::swap(m[2],  m[8]);
    std::swap(m[3],  m[12]);
    std::swap(m[6],  m[9]);
    std::swap(m[7],  m[13]);
    std::swap(m[11], m[14]);
}

Matrix4 Matrix4::transposed() const {
    return Matrix4(m[0], m[4], m[8], m[12],
                   m[1], m[5], m[9], m[13],
                   m[2], m[6], m[10], m[14],
                   m[3], m[7], m[11], m[15]);
}

void Matrix4::inverse() {
    if (!this->isInversed()) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Inverse matrix not exists.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Inverse matrix not exists!";
    }
    scalar cofactor0 = getCofactor(m[5],m[6],m[7], m[9],m[10],m[11], m[13],m[14],m[15]);
    scalar cofactor1 = getCofactor(m[4],m[6],m[7], m[8],m[10],m[11], m[12],m[14],m[15]);
    scalar cofactor2 = getCofactor(m[4],m[5],m[7], m[8],m[9], m[11], m[12],m[13],m[15]);
    scalar cofactor3 = getCofactor(m[4],m[5],m[6], m[8],m[9], m[10], m[12],m[13],m[14]);

    // get determinant
    scalar determinant = m[0] * cofactor0 - m[1] * cofactor1 + m[2] * cofactor2 - m[3] * cofactor3;

    // get rest of cofactors for adj(M)
    scalar cofactor4 = getCofactor(m[1],m[2],m[3], m[9],m[10],m[11], m[13],m[14],m[15]);
    scalar cofactor5 = getCofactor(m[0],m[2],m[3], m[8],m[10],m[11], m[12],m[14],m[15]);
    scalar cofactor6 = getCofactor(m[0],m[1],m[3], m[8],m[9], m[11], m[12],m[13],m[15]);
    scalar cofactor7 = getCofactor(m[0],m[1],m[2], m[8],m[9], m[10], m[12],m[13],m[14]);

    scalar cofactor8 = getCofactor(m[1],m[2],m[3], m[5],m[6], m[7],  m[13],m[14],m[15]);
    scalar cofactor9 = getCofactor(m[0],m[2],m[3], m[4],m[6], m[7],  m[12],m[14],m[15]);
    scalar cofactor10= getCofactor(m[0],m[1],m[3], m[4],m[5], m[7],  m[12],m[13],m[15]);
    scalar cofactor11= getCofactor(m[0],m[1],m[2], m[4],m[5], m[6],  m[12],m[13],m[14]);

    scalar cofactor12= getCofactor(m[1],m[2],m[3], m[5],m[6], m[7],  m[9], m[10],m[11]);
    scalar cofactor13= getCofactor(m[0],m[2],m[3], m[4],m[6], m[7],  m[8], m[10],m[11]);
    scalar cofactor14= getCofactor(m[0],m[1],m[3], m[4],m[5], m[7],  m[8], m[9], m[11]);
    scalar cofactor15= getCofactor(m[0],m[1],m[2], m[4],m[5], m[6],  m[8], m[9], m[10]);

    // build inverse matrix = adj(M) / det(M)
    // adjugate of M is the transpose of the cofactor matrix of M
    scalar invDeterminant = 1.0f / determinant;
    m[0] =  invDeterminant * cofactor0;
    m[1] = -invDeterminant * cofactor4;
    m[2] =  invDeterminant * cofactor8;
    m[3] = -invDeterminant * cofactor12;

    m[4] = -invDeterminant * cofactor1;
    m[5] =  invDeterminant * cofactor5;
    m[6] = -invDeterminant * cofactor9;
    m[7] =  invDeterminant * cofactor13;

    m[8] =  invDeterminant * cofactor2;
    m[9] = -invDeterminant * cofactor6;
    m[10]=  invDeterminant * cofactor10;
    m[11]= -invDeterminant * cofactor14;

    m[12]= -invDeterminant * cofactor3;
    m[13]=  invDeterminant * cofactor7;
    m[14]= -invDeterminant * cofactor11;
    m[15]=  invDeterminant * cofactor15;
}

Matrix4 Matrix4::computeInverse() const {
    if (!this->isInversed()) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Inverse matrix not exists.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Inverse matrix not exists!";
    }
    scalar cofactor0 = getCofactor(m[5],m[6],m[7], m[9],m[10],m[11], m[13],m[14],m[15]);
    scalar cofactor1 = getCofactor(m[4],m[6],m[7], m[8],m[10],m[11], m[12],m[14],m[15]);
    scalar cofactor2 = getCofactor(m[4],m[5],m[7], m[8],m[9], m[11], m[12],m[13],m[15]);
    scalar cofactor3 = getCofactor(m[4],m[5],m[6], m[8],m[9], m[10], m[12],m[13],m[14]);

    // get determinant
    scalar determinant = m[0] * cofactor0 - m[1] * cofactor1 + m[2] * cofactor2 - m[3] * cofactor3;

    // get rest of cofactors for adj(M)
    scalar cofactor4 = getCofactor(m[1],m[2],m[3], m[9],m[10],m[11], m[13],m[14],m[15]);
    scalar cofactor5 = getCofactor(m[0],m[2],m[3], m[8],m[10],m[11], m[12],m[14],m[15]);
    scalar cofactor6 = getCofactor(m[0],m[1],m[3], m[8],m[9], m[11], m[12],m[13],m[15]);
    scalar cofactor7 = getCofactor(m[0],m[1],m[2], m[8],m[9], m[10], m[12],m[13],m[14]);

    scalar cofactor8 = getCofactor(m[1],m[2],m[3], m[5],m[6], m[7],  m[13],m[14],m[15]);
    scalar cofactor9 = getCofactor(m[0],m[2],m[3], m[4],m[6], m[7],  m[12],m[14],m[15]);
    scalar cofactor10= getCofactor(m[0],m[1],m[3], m[4],m[5], m[7],  m[12],m[13],m[15]);
    scalar cofactor11= getCofactor(m[0],m[1],m[2], m[4],m[5], m[6],  m[12],m[13],m[14]);

    scalar cofactor12= getCofactor(m[1],m[2],m[3], m[5],m[6], m[7],  m[9], m[10],m[11]);
    scalar cofactor13= getCofactor(m[0],m[2],m[3], m[4],m[6], m[7],  m[8], m[10],m[11]);
    scalar cofactor14= getCofactor(m[0],m[1],m[3], m[4],m[5], m[7],  m[8], m[9], m[11]);
    scalar cofactor15= getCofactor(m[0],m[1],m[2], m[4],m[5], m[6],  m[8], m[9], m[10]);

    // build inverse matrix = adj(M) / det(M)
    // adjugate of M is the transpose of the cofactor matrix of M
    scalar invDeterminant = 1.0f / determinant;
    scalar tmp[16];
    tmp[0] =  invDeterminant * cofactor0;
    tmp[1] = -invDeterminant * cofactor4;
    tmp[2] =  invDeterminant * cofactor8;
    tmp[3] = -invDeterminant * cofactor12;

    tmp[4] = -invDeterminant * cofactor1;
    tmp[5] =  invDeterminant * cofactor5;
    tmp[6] = -invDeterminant * cofactor9;
    tmp[7] =  invDeterminant * cofactor13;

    tmp[8] =  invDeterminant * cofactor2;
    tmp[9] = -invDeterminant * cofactor6;
    tmp[10]=  invDeterminant * cofactor10;
    tmp[11]= -invDeterminant * cofactor14;

    tmp[12]= -invDeterminant * cofactor3;
    tmp[13]=  invDeterminant * cofactor7;
    tmp[14]= -invDeterminant * cofactor11;
    tmp[15]=  invDeterminant * cofactor15;
    return Matrix4(tmp[0], tmp[1], tmp[2], tmp[3],
                   tmp[4], tmp[5], tmp[6], tmp[7],
                   tmp[8], tmp[9], tmp[10], tmp[11],
                   tmp[12], tmp[13], tmp[14], tmp[15]);
}



bool Matrix4::isInversed() const {
    if (this->isRotationMatrix()) return true;
    if (this->isEuclideanMatrix()) return true;
    if (this->isAffineMatrix()) return true;
    if (this->isPeojectiveMatrix()) return true;
    if (std::abs(this->getDeterminant()) < MYEPSILON) return false;
    return true;
}

Matrix4 Matrix4::computeRotationInverse() const {
    if (!this->isRotationMatrix()) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Not a rotation matrix.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Not a rotation matrix.";
    }
    Matrix4 ret;
    ret.setIdentity();
    Matrix3 R(m[0], m[1], m[2],
              m[4], m[5], m[5],
              m[8], m[9], m[10]);
    R.transpose();
    // the first column
    ret[0] = R[0];
    ret[1] = R[1];
    ret[2] = R[2];
    // the second column
    ret[4] = R[3];
    ret[5] = R[4];
    ret[6] = R[5];
    // the third column
    ret[8] = R[6];
    ret[9] = R[7];
    ret[10] = R[8];
    return ret;
}

Matrix4 Matrix4::computeEuclideanInverse() const {
    if (!this->isEuclideanMatrix()) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Not a eudlidean matrix.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Not a eudlidean matrix.";
    }
    Matrix4 ret;
    ret.setIdentity();
    Matrix3 R(m[0], m[1], m[2],
              m[4], m[5], m[5],
              m[8], m[9], m[10]);
    R.transpose();
    Vector3 t(m[12], m[13], m[14]);
    t = -R * t;
    // the first column
    ret[0] = R[0];
    ret[1] = R[1];
    ret[2] = R[2];
    // the second column
    ret[4] = R[3];
    ret[5] = R[4];
    ret[6] = R[5];
    // the third column
    ret[8] = R[6];
    ret[9] = R[7];
    ret[10] = R[8];
    // the fourth column
    ret[12] = t[0];
    ret[13] = t[1];
    ret[14] = t[2];
    return ret;
}

Matrix4 Matrix4::computeAffineInverse() const {
    if (!this->isAffineMatrix()) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Not a affine matrix.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Not a affine matrix.";
    }
    Matrix4 ret;
    ret.setIdentity();
    Matrix3 R(m[0], m[1], m[2],
              m[4], m[5], m[5],
              m[8], m[9], m[10]);
    R.inverse();
    Vector3 t(m[12], m[13], m[14]);
    t = -R * t;
    // the first column
    ret[0] = R[0];
    ret[1] = R[1];
    ret[2] = R[2];
    // the second column
    ret[4] = R[3];
    ret[5] = R[4];
    ret[6] = R[5];
    // the third column
    ret[8] = R[6];
    ret[9] = R[7];
    ret[10] = R[8];
    // the fourth column
    ret[12] = t[0];
    ret[13] = t[1];
    ret[14] = t[2];
    return ret;
}

Matrix4 Matrix4::computeProjectiveInverse() const {
    if (!this->isPeojectiveMatrix()) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Not a projective matrix.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Not a projective matrix.";
    }
    // partition
    Matrix2 a(m[0], m[1], m[4], m[5]);
    Matrix2 b(m[8], m[9], m[12], m[13]);
    Matrix2 c(m[2], m[3], m[6], m[7]);
    Matrix2 d(m[10], m[11], m[14], m[15]);

    // pre-compute repeated parts
    a.inverse();             // A^-1
    Matrix2 ab = a * b;     // A^-1 * B
    Matrix2 ca = c * a;     // C * A^-1
    Matrix2 cab = ca * b;   // C * A^-1 * B
    Matrix2 dcab = d - cab; // D - C * A^-1 * B

    // check determinant if |D - C * A^-1 * B| = 0
    //NOTE: this function assumes det(A) is already checked. if |A|=0 then,
    //      cannot use this function.
    scalar determinant = dcab[0] * dcab[3] - dcab[1] * dcab[2];
    if (std::abs(determinant) > MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Projective matrix is not reversible.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Projective matrix is not reversible.";
    }
    // compute D' and -D'
    Matrix2 d1 = dcab;      //  (D - C * A^-1 * B)
    d1.inverse();            //  (D - C * A^-1 * B)^-1
    Matrix2 d2 = -d1;       // -(D - C * A^-1 * B)^-1

    // compute C'
    Matrix2 c1 = d2 * ca;   // -D' * (C * A^-1)

    // compute B'
    Matrix2 b1 = ab * d2;   // (A^-1 * B) * -D'

    // compute A'
    Matrix2 a1 = a - (ab * c1); // A^-1 - (A^-1 * B) * C'

    Matrix4 ret;
    // assemble inverse matrix
    ret[0] = a1[0];  ret[4] = a1[2]; /*|*/ ret[8] = b1[0];  ret[12]= b1[2];
    ret[1] = a1[1];  ret[5] = a1[3]; /*|*/ ret[9] = b1[1];  ret[13]= b1[3];
    /*-----------------------------+-----------------------------*/
    ret[2] = c1[0];  ret[6] = c1[2]; /*|*/ ret[10]= d1[0];  ret[14]= d1[2];
    ret[3] = c1[1];  ret[7] = c1[3]; /*|*/ ret[11]= d1[1];  ret[15]= d1[3];
    return ret;
}

Matrix4 Matrix4::operator+(const Matrix4 &rhs) const {
    Matrix4 ret;
    for (int i = 0; i < 16; ++i) {
        ret[i] = this->m[i] + rhs[i];
    }
    return ret;
}

Matrix4& Matrix4::operator+=(const Matrix4 &rhs) {
    for (int i = 0; i < 16; ++i) {
        this->m[i] += rhs[i];
    }
    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4 &rhs) const {
    Matrix4 ret;
    for (int i = 0; i < 16; ++i) {
        ret[i] = this->m[i] - rhs[i];
    }
    return ret;
}

Matrix4& Matrix4::operator-=(const Matrix4 &rhs) {
    for (int i = 0; i < 16; ++i) {
        this->m[i] -= rhs[i];
    }
    return *this;
}

Matrix4 Matrix4::matmul(const Matrix4 &rhs) const {
    // |  0  4  8 12 | |  0  4  8 12 |
    // |  1  5  9 13 | |  1  5  9 13 |
    // |  2  6 10 14 | |  2  6 10 14 |
    // |  3  7 11 15 | |  3  7 11 15 |
    Matrix4 ret;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ret(i, j) = this->getRow(i).dot(rhs.getColumn(j));
        }
    }
    return ret;
}

Vector4 Matrix4::operator*(const Vector4 &rhs) const {
    Vector4 ret;
    for (int i = 0; i < 4; ++i) {
        ret[i] = this->getRow(i).dot(rhs);
    }
    return ret;
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) const {
    Matrix4 ret;
    for (int i = 0; i < 16; ++i) {
        ret[i] = this->m[i] * rhs[i];
    }
    return ret;
}

Matrix4 Matrix4::operator*(const scalar& rhs) {
    Matrix4 ret;
    for (int i = 0; i < 16; ++i) {
        ret[i] = this->m[i] * rhs;
    }
    return ret;
}

Matrix4& Matrix4::operator*=(const Matrix4 &rhs) {
    for (int i = 0; i < 16; ++i) {
        this->m[i] *= rhs[i];
    }
    return *this;
}

Matrix4& Matrix4::operator*=(const scalar& rhs) {
    *this = *this * rhs;
    return *this;
}

Matrix4 Matrix4::operator/(const scalar &rhs) const {
    if (std::abs(rhs) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Division by zero condition.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Division by zero condition!";
    }
    Matrix4 ret;
    for (int i = 0; i < 16; ++i) {
        ret[i] = this->m[i] / rhs;
    }
    return ret;
}

Matrix4& Matrix4::operator/=(const scalar& rhs) {
    if (std::abs(rhs) < MYEPSILON) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Division by zero condition.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Division by zero condition!";
    }
    for (int i = 0; i < 16; ++i) {
        this->m[i] = this->m[i] / rhs;
    }
    return *this;
}

bool Matrix4::equal(const Matrix4 &rhs, scalar e) const {
    for (int i = 0; i < 16; ++i) {
        if (std::abs(m[i] - rhs[i]) > MYEPSILON) {
            return false;
        }
    }
    return true;
}

bool Matrix4::operator==(const Matrix4 &rhs) const {
    for (int i = 0; i < 16; ++i) {
        if (m[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4 &rhs) const {
    for (int i = 0; i < 16; ++i) {
        if (m[i] == rhs[i]) {
            return false;
        }
    }
    return true;
}

scalar Matrix4::operator[](int index) const {
    if ((index > 15) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[index];
}

scalar& Matrix4::operator[](int index) {
    if ((index > 15) || (index < 0)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[index];
}

scalar Matrix4::operator()(int i, int j) const {
    if ((i < 0) || (i > 3) || (j < 0) || (j > 3)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[j * 4 + i];
}

scalar& Matrix4::operator()(int i, int j) {
    if ((i < 0) || (i > 3) || (j < 0) || (j > 3)) {
        fprintf(stderr, "File %s, Line %d, Function %s(): Index out of bounds.\n",
                __FILE__, __LINE__, __FUNCTION__);
        throw "Index out of bounds!";
    }
    return m[j * 4 + i];
}

Matrix4 operator-(const Matrix4& mat4) {
    return Matrix4(-mat4[0], -mat4[1], -mat4[2], -mat4[3],
                   -mat4[4], -mat4[5], -mat4[6], -mat4[7],
                   -mat4[8], -mat4[9], -mat4[10], -mat4[11],
                   -mat4[12], -mat4[13], -mat4[14], -mat4[15]);
}

Matrix4 operator*(const scalar& s, const Matrix4& mat4) {
    return Matrix4(s*mat4[0], s*mat4[1], s*mat4[2], s*mat4[3],
                   s*mat4[4], s*mat4[5], s*mat4[6], s*mat4[7],
                   s*mat4[8], s*mat4[9], s*mat4[10], s*mat4[11],
                   s*mat4[12], s*mat4[13], s*mat4[14], s*mat4[15]);
}

Vector4 operator*(const Vector4& vec, const Matrix4& mat4) {
    Vector4 ret;
    for (int i = 0; i < 4; ++i) {
        ret[i] = vec.dot(mat4.getColumn(i));
    }
    return ret;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& mat4) {
    os << std::fixed << std::setprecision(6);
    os << "[" << std::setw(10) << mat4[0] << " " << std::setw(10) << mat4[4] << " " << std::setw(10) << mat4[8]  <<  " " << std::setw(10) << mat4[12] << "]\n"
       << "[" << std::setw(10) << mat4[1] << " " << std::setw(10) << mat4[5] << " " << std::setw(10) << mat4[9]  <<  " " << std::setw(10) << mat4[13] << "]\n"
       << "[" << std::setw(10) << mat4[2] << " " << std::setw(10) << mat4[6] << " " << std::setw(10) << mat4[10] <<  " " << std::setw(10) << mat4[14] << "]\n"
       << "[" << std::setw(10) << mat4[3] << " " << std::setw(10) << mat4[7] << " " << std::setw(10) << mat4[11] <<  " " << std::setw(10) << mat4[15] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

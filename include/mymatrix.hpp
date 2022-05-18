/**
 *  Copyright (C) All rights reserved.
 *  @file mymatrix.hpp
 *  @brief 2,3,4 square matrix simple implementation, column major order
 *  @author haofan ren, yqykrhf@163.com
 *  @version beta 0.0
 *  @date 22-2-26
 *  @todo function data() issue, when multiple pointer point that, memory management.
 *  @todo block operation.
 *  @todo matrix3 get axis-angle.
 *  @todo opeartor [][]
 *  @note The elements of the matrix are stored as column major order.
 *  @note| 0 2 |....| 0 3 6 |......| 0  4  8 12 |
 *  @note| 1 3 |....| 1 4 7 |......| 1  5  9 13 |
 *  @note...........| 2 5 8 |......| 2  6 10 14 |
 *  @note..........................| 3  7 11 15 |
 */

#pragma once

#include "myvector.hpp"

class Matrix2;
class Matrix3;
class Matrix4;

/**
 *  @brief Matrix2 class used for 2x2 matrix.
 */
class Matrix2 {
  private:
    /** @brief elements stored in column major. */
    scalar m[4];

  protected:
  public:
    /**
    * Create a new 2x2 matrix object, identity by default.
    * @brief Default constructor.
    * @see Matrix2(const scalar src[4])
    * @see Matrix2(scalar m0, scalar m1, scalar m2, scalar m3)
    */
    Matrix2();
    /**
    * Create a new 2x2 matrix object by pointer.
    * @brief constructor by a scalar pointer.
    * @warning make sure the pointer is a 4-elements array.
    * @see Matrix2()
    * @see Matrix2(scalar m0, scalar m1, scalar m2, scalar m3)
    */
    Matrix2(const scalar src[4]);
    /**
    * Create a new 2x2 matrix object by 4 elements.
    * @brief constructor by 4 scalar elements.
    * @see Matrix2()
    * @see Matrix2(const scalar src[4])
    */
    Matrix2(scalar m0, scalar m1, scalar m2, scalar m3);
    /**
     * @brief Matrix2 copy constructor, deep copy.
     * @param mat2: Matrix2 object
     */
    Matrix2(const Matrix2& mat2);

    /**
     * @brief Matrix2 operator= overloading, deep copy.
     * @param mat2 Matirx2 object
     * @return Matrix2 reference
     */
    Matrix2& operator=(const Matrix2& mat2);

    /**
     * @brief set elements in Matrix2 obejct with a scalar pointer.
     * @param src scalar pointer with 4 elements stored in column major.
     * @warning make sure the pointer is a 4-elements array.
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void set(const scalar src[4]);
    /**
     * @brief set elements in Matrix2 object with 4 scalars.
     * @param m0 the element located in (0, 0).
     * @param m1 the element located in (1, 0).
     * @param m2 the element located in (0, 1).
     * @param m3 the element located in (1, 1).
     * @see void set(const scalar src[4])
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3);
    /**
     * @brief set elements in specified row by a pointer.
     * @param index determine specified row.
     * @param data stores the elements to be set.
     * @warning make sure the pointer is 2 elements array.
     * @exception (index > 1) or (index < 0)
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void setRow(int index, const scalar data[2]);
    /**
     * @brief set elements in specified row by a 2D vector.
     * @param index determine specified row.
     * @param v stores the elements to be set.
     * @exception (index > 1) or (index < 0)
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void setRow(int index, const Vector2& v);
    /**
     * @brief set elements in specified column by a pointer.
     * @param index determine specified column.
     * @param data stores the elements to be set.
     * @exception (index > 1) or (index < 0)
     * @warning make sure the pointer is a 2-elements array.
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const Vector2& v)
     */
    void setColumn(int index, const scalar data[2]);
    /**
     * @brief set elements in specified column by a 2D vector.
     * @param index determine specified column.
     * @param v stores the elements to be set.
     * @exception (index > 1) or (index < 0)
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2]);
     */
    void setColumn(int index, const Vector2& v);
    /**
     * @brief in-place operation, set as identity 2x2 matrix.
     */
    void setIdentity();
    /**
     * @brief construct rotation matrix by angle.
     * @param angle right-hand direction is positive.
     * @param unit degree or radian, degree by default.
     */
    void setRotatonMatrix(const scalar& angle, ANGLEUNIT unit = DEG);

    /**
     * @brief get the contiguous address raw data(column-major) m[4].
     * @return scalar pointer of m.
     */
    scalar* data();
    /**
     * @brief get the const contiguous address raw data(column-major) m[4].
     * @return const scalar pointer of m.
     */
    const scalar* constData() const;

    /**
     * @brief get elements in specified row.
     * @param index row index.
     * @exception (index > 1) or (index < 0)
     * @return 2D Vector with index-th row elements of the Matrix.
     */
    Vector2 getRow(int index) const;
    /**
     * @brief get elements in specified column.
     * @param index column index.
     * @exception (index > 1) or (index < 0)
     * @return 2D Vector with index-th column elements of the Matrix.
     */
    Vector2 getColumn(int index) const;
    /**
     * @brief compute determinant.
     * @return determinant value.
     */
    scalar getDeterminant() const;
    /**
     * @brief extract rotation angle from 2x2 rotation matrix.
     * @param unit determine the returned angle unit(degree or radians).
     * @exception not a rotation matrix.
     * @return rotation angle in the interval [-/pi,+/pi] radian or [-180, +180] degree.
     */
    scalar getAngle(ANGLEUNIT unit = DEG) const;
    /**
     * @brief judge whether this matrix is a rotation matrix.
     * @return bool
     */
    bool isRotationMatrix() const;

    /**
     * @brief in-place operation, transpose 2x2 matrix.
     * @see Matrix2 transposed() const
     */
    void transpose() {
        std::swap(m[1], m[2]);
    }
    /**
     * @brief transpose operation.
     * @return transposed Matrix2.
     * @see void transpose()
     */
    Matrix2 transposed() const {
        return Matrix2(m[0], m[2], m[1], m[3]);
    }

    /**
     * @brief in-place operation, compute inversed 2x2 matrix.
     * @exception Inverse matrix not exists!
     * @see bool isInversed()
     */
    void inverse();
    /**
     * @brief compute inverse matrix.
     * @exception Inverse matrix not exists!
     * @return inverse matrix.
     * @see void inverse()
     */
    Matrix2 computeInverse() const;
    /**
     * @brief judge whether the matrix is reversible by determinant equal to 0 with EPISION.
     * @return bool
     * @see void inverse()
     */
    bool isInversed() const;

    /**
     * @brief Binary operator, addition of two 2x2 matrix.
     * @see Matrix2& operator+=(const Matrix2& rhs)
     */
    Matrix2 operator+(const Matrix2& rhs) const;
    /**
     * @brief Binary operator, addition of two 2x2 matrix.
     * @see Matrix2 operator+(const Matrix2& rhs) const
     */
    Matrix2& operator+=(const Matrix2& rhs);

    /**
     * @brief Binary operator, subtraction of two 2x2 matrices.
     * @see Matrix2& operator-=(const Matrix2& rhs)
     */
    Matrix2 operator-(const Matrix2& rhs) const;
    /**
     * @brief Abbr Binary operator, subtraction of two 2x2 matrices.
     * @see Matrix2& operator-(const Matrix2& rhs) const
     */
    Matrix2& operator-=(const Matrix2& rhs);

    /**
     * @brief matrix multiplication.
     * @param rhs right hand side mutiplication object.
     * @return result
     * @see Matrix2 operator*(const Matrix2& rhs) const
     */
    Matrix2 matmul(const Matrix2& rhs) const;
    /**
     * @brief multiply 2x2 matrix with 2D vector.
     * @see friend Vector2 operator*(const Vector2& vec, const Matrix2& mat2)
     */
    Vector2 operator*(const Vector2& rhs) const;
    /**
     * @brief multiply this 2x2 matrix with another 2x2 matrix.
     * @see Matrix2& operator*=(const Matrix2& rhs)
     * @see Matrix2 matmul(const Matrix2& rhs) const
     */
    Matrix2 operator*(const Matrix2& rhs) const;
    /**
     * @brief multiply 2x2 matrix with a scalar.
     * @see friend Matrix2 operator*(const scalar& s, const Matrix2& mat2)
     */
    Matrix2 operator*(const scalar& rhs);
    /**
     * @brief Abbr Binary operator, element-wise multiplication of two 2x2 matrices.
     * @see Matrix2 operator*(const Matrix2& rhs) const
     */
    Matrix2& operator*=(const Matrix2& rhs);
    /**
     * @brief Abbr Binray operator, multiply 2x2 matrix a with scalar.
     * @see Matrix2 operator*(const scalar& rhs)
     */
    Matrix2& operator*=(const scalar& rhs);

    /**
     * @brief Binary operator, 2x2 matrix divided by a scalar.
     * @exception Division by zero condition with EPISION
     * @see Matrix2& operator/=(const scalar& rhs)
     */
    Matrix2 operator/(const scalar& rhs) const;
    /**
     * @brief Abbr Binary operator, 2x2 matrix divided by a scalar.
     * @exception Division by zero condition with EPISION
     * @see Matrix2 operator/(const scalar& rhs) const
     */
    Matrix2& operator/=(const scalar& rhs);

    /**
     * @brief comparsion whether two matrices are equal with EPSILON.
     * @param rhs comparison object.
     * @param e EPSILON.
     * @return bool
     * @see bool operator==(const Matrix2& rhs) const
     */
    bool equal(const Matrix2& rhs, scalar e = MYEPSILON) const;
    /**
     * @brief Equivalence overloading, exact comparsion, no epsilon.
     * @param rhs comparison object.
     * @return bool
     * @see bool equal(const Matrix2& rhs, scalar e = MYEPSILON) const
     * @see bool operator!=(const Matrix2& rhs) const
     */
    bool operator==(const Matrix2& rhs) const;
    /**
     *  @brief Inequivalence overloading, exact comparsion, no epsilon.
     *  @param rhs comparison object.
     *  @return bool
     *  @see bool operator==(const Matrix2& rhs) const
     */
    bool operator!=(const Matrix2& rhs) const;

    /**
     * @brief index[] overloading for const object.
     * @param index range from 0 to 3.
     * @exception (index > 3) or (index < 0)
     * @return raw data[index] value.
     * @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     * @brief index[] overloading.
     * @param index range from 0 to 3.
     * @exception (index > 3) or (index < 0)
     * @return raw data[index] value.
     * @see scalar operator[](int index) const
     */
    scalar& operator[](int index);

    /**
     * @brief index(i,j) overloading for const object.
     * @param i row index, range from 0 to 1.
     * @param j column index, range from 0 to 1.
     * @exception (i < 0) or (i > 1) or (j < 0) or (j > 1)
     * @return value located in index(i, j)
     * @see scalar& operator()(int i, int j)
     */
    scalar operator()(int i, int j) const;
    /**
     * @brief index(i,j) overloading.
     * @param i row index, range from 0 to 1.
     * @param j column index, range from 0 to 1.
     * @exception (i < 0) or (i > 1) or (j < 0) or (j > 1)
     * @return value located in index(i, j).
     * @see scalar operator()(int i, int j) const
     */
    scalar& operator()(int i, int j);

    /**
     * @brief unary operator, for negative Matrix2.
     * @param mat2 original matrix
     * @return negative matrix2
     */
    friend Matrix2 operator-(const Matrix2& mat2);
    /**
     * @brief multiply a scalar with a 2x2 matrix.
     * @param s scalar.
     * @param mat2 2x2 matrix.
     * @return result
     * @see Matrix2 operator*(const scalar& rhs)
     */
    friend Matrix2 operator*(const scalar& s, const Matrix2& mat2);
    /**
     * @brief multiply a 2D vector with 2x2 matrix.
     * @param vec 2D vector.
     * @param mat2 2x2 matrix.
     * @return result
     * @see Vector2 operator*(const Vector2& rhs) const
     */
    friend Vector2 operator*(const Vector2& vec, const Matrix2& mat2);
    /**
     *  @brief << overloading.
     *  @return std::ostream object
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix2& mat2);
};


/**
 *  @brief Matrix3 class used for 3x3 matrix.
 */
class Matrix3 {
  private:
    /** @brief elements stored in column major. */
    scalar m[9];
    /** @brief record angle unit when axis-angle set function for getAxisAngle() */
    ANGLEUNIT au = DEG;

  protected:
  public:
    /**
    * Create a new 3x3 matrix object, identity by default.
    * @brief Default constructor.
    * @see Matrix3(const scalar src[9])
    * @see Matrix3(scalar m0, scalar m1, scalar m2,
    *              scalar m3, scalar m4, scalar m5,
    *              scalar m6, scalar m7, scalar m8)
    */
    Matrix3();
    /**
    * Create a new 3x3 matrix object by pointer.
    * @brief constructor by a scalar pointer.
    * @warning make sure the pointer is a 9-elements array.
    * @see Matrix3()
    * @see Matrix3(scalar m0, scalar m1, scalar m2,
    *              scalar m3, scalar m4, scalar m5,
    *              scalar m6, scalar m7, scalar m8)
    */
    Matrix3(const scalar src[9]);
    /**
    * Create a new 3x3 matrix object by 9 elements.
    * @brief constructor by 9 scalar elements.
    * @see Matrix3()
    * @see Matrix3(const scalar src[9])
    */
    Matrix3(scalar m0, scalar m1, scalar m2,  // first column
            scalar m3, scalar m4, scalar m5,  // second column
            scalar m6, scalar m7, scalar m8); // third column
    /**
     * @brief Matrix3 copy constructor, deep copy.
     * @param mat3 Matrix3 object
     */
    Matrix3(const Matrix3& mat3);

    /**
     * @brief Matrix3 operator= overloading, deep copy.
     * @param mat3 Matirx3 object
     * @return Matrix3 reference
     */
    Matrix3& operator=(const Matrix3& mat3);

    /**
     * @brief set elements in Matrix3 obejct with a scalar pointer.
     * @param src scalar pointer with 9 elements stored in column major.
     * @warning make sure the pointer is a 9-elements array.
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2,
                     const scalar& m3, const scalar& m4, const scalar& m5,
                     const scalar& m6, const scalar& m7, const scalar& m8)
     * @see void setRow(int index, const scalar data[3])
     * @see void setRow(int index, const Vector3& v)
     * @see void setColumn(int index, const scalar data[3])
     * @see void setColumn(int index, const Vector3& v)
     */
    void set(const scalar src[9]);
    /**
     * @brief set elements in Matrix3 object with 9 scalars.
     * @param m0 the element located in (0, 0).
     * @param m1 the element located in (1, 0).
     * @param m2 the element located in (2, 0).
     * @param m3 the element located in (0, 1).
     * @param m4 the element located in (1, 1).
     * @param m5 the element located in (2, 1).
     * @param m6 the element located in (0, 2).
     * @param m7 the element located in (1, 2).
     * @param m8 the element located in (2, 2).
     * @see void set(const scalar src[9])
     * @see void setRow(int index, const scalar data[3])
     * @see void setRow(int index, const Vector3& v)
     * @see void setColumn(int index, const scalar data[3])
     * @see void setColumn(int index, const Vector3& v)
     */
    void set(const scalar& m0, const scalar& m1, const scalar& m2,
             const scalar& m3, const scalar& m4, const scalar& m5,
             const scalar& m6, const scalar& m7, const scalar& m8);
    /**
     * @brief set elements in specified row by a pointer.
     * @param index determine specified row.
     * @param data stores the elements to be set.
     * @warning make sure the pointer is 3 elements array.
     * @exception (index > 2) or (index < 0)
     * @see void set(const scalar src[9])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2,
                     const scalar& m3, const scalar& m4, const scalar& m5,
                     const scalar& m6, const scalar& m7, const scalar& m8);
     * @see void setRow(int index, const Vector3& v)
     * @see void setColumn(int index, const scalar data[3])
     * @see void setColumn(int index, const Vector3& v)
     */
    void setRow(int index, const scalar data[3]);
    /**
     * @brief set elements in specified row by a 3D vector.
     * @param index determine specified row.
     * @param v stores the elements to be set.
     * @exception (index > 2) or (index < 0)
     * @see void set(const scalar src[9])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2,
                     const scalar& m3, const scalar& m4, const scalar& m5,
                     const scalar& m6, const scalar& m7, const scalar& m8);
     * @see void setRow(int index, const scalar data[3])
     * @see void setColumn(int index, const scalar data[3])
     * @see void setColumn(int index, const Vector3& v)
     */
    void setRow(int index, const Vector3& v);
    /**
     * @brief set elements in specified column by a pointer.
     * @param index determine specified column.
     * @param data stores the elements to be set.
     * @exception (index > 2) or (index < 0)
     * @warning make sure the pointer is a 3-elements array.
     * @see void set(const scalar src[9])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2,
                     const scalar& m3, const scalar& m4, const scalar& m5,
                     const scalar& m6, const scalar& m7, const scalar& m8);
     * @see void setRow(int index, const scalar data[3])
     * @see void setRow(int index, const Vector3& v)
     * @see void setColumn(int index, const Vector3& v)
     */
    void setColumn(int index, const scalar data[3]);
    /**
     * @brief set elements in specified column by a 3D vector.
     * @param index determine specified column.
     * @param v stores the elements to be set.
     * @exception (index > 2) or (index < 0)
     * @see void set(const scalar src[9])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2,
                     const scalar& m3, const scalar& m4, const scalar& m5,
                     const scalar& m6, const scalar& m7, const scalar& m8);
     * @see void setRow(int index, const scalar data[3])
     * @see void setRow(int index, const Vector3& v)
     * @see void setColumn(int index, const scalar data[3]);
     */
    void setColumn(int index, const Vector3& v);
    /**
     * @brief in-place operation, set as identity 3x3 matrix.
     */
    void setIdentity();
    /**
     * @brief construct rotation matrix by axis-angle utilizing Rodrigues Rotation Formula.
     * @param axis rotation axis.
     * @param angle rotation rotation.
     * @param unit value representing angle in radians or in degree.
     */
    void setRotationMatrix(const Vector3& axis, const scalar& angle = 0.f,
                           ANGLEUNIT unit = DEG);


    /**
     * @brief convert 3x3 matrix to Homogenous form, i.e 4x4 matrix.
     * @return Matrix4 homogenous form of 3x3 matrix.
     */
    Matrix4 toHomogenous() const;

    /**
     * @brief get the contiguous address raw data(column-major) m[9].
     * @return scalar pointer of m.
     */
    scalar* data();
    /**
     * @brief get the const contiguous address raw data(column-major) m[9].
     * @return const scalar pointer of m.
     */
    const scalar* constData() const;

    /**
     * @brief get elements in specified row.
     * @param index row index.
     * @exception (index > 2) or (index < 0)
     * @return 3D Vector with index-th row elements of the Matrix.
     */
    Vector3 getRow(int index) const;
    /**
     * @brief get elements in specified column.
     * @param index column index.
     * @exception (index > 2) or (index < 0)
     * @return 3D Vector with index-th column elements of the Matrix.
     */
    Vector3 getColumn(int index) const;
    /**
     * @brief compute determinant.
     * @return determinant value.
     */
    scalar getDeterminant() const;
    /**
     * @brief judge whether this matrix is a rotation matrix.
     * @return bool
     */
    bool isRotationMatrix() const;

    /**
     * @brief in-place operation, transpose 3x3 matrix.
     * @see Matrix3 transposed() const
     */
    void transpose();
    /**
     * @brief transpose operation.
     * @return transposed Matrix3.
     * @see void transpose()
     */
    Matrix3 transposed() const;

    /**
     * @brief in-place operation, compute inversed 3x3 matrix.
     * @exception Inverse matrix not exists!
     * @see bool isInversed()
     */
    void inverse();
    /**
     * @brief compute inverse matrix.
     * @exception Inverse matrix not exists!
     * @return inverse matrix.
     * @see void inverse()
     */
    Matrix3 computeInverse() const;
    /**
     * @brief judge whether the matrix is reversible by determinant equal to 0 with EPISION.
     * @return bool
     * @see void inverse()
     */
    bool isInversed() const;

    /**
     * @brief Binary operator, addition of two 3x3 matrix.
     * @see Matrix3& operator+=(const Matrix3& rhs)
     */
    Matrix3 operator+(const Matrix3& rhs) const;
    /**
     * @brief Binary operator, addition of two 3x3 matrix.
     * @see Matrix3 operator+(const Matrix3& rhs) const
     */
    Matrix3& operator+=(const Matrix3& rhs);

    /**
     * @brief Binary operator, subtraction of two 3x3 matrices.
     * @see Matrix3& operator-=(const Matrix3& rhs)
     */
    Matrix3 operator-(const Matrix3& rhs) const;
    /**
     * @brief Abbr Binary operator, subtraction of two 3x3 matrices.
     * @see Matrix3& operator-(const Matrix3& rhs) const
     */
    Matrix3& operator-=(const Matrix3& rhs);

    /**
     * @brief matrix multiplication.
     * @param rhs right hand side mutiplication object.
     * @return result
     * @see Matrix3 operator*(const Matrix3& rhs) const
     */
    Matrix3 matmul(const Matrix3& rhs) const;
    /**
     * @brief multiply 3x3 matrix with 3D vector.
     * @see friend Vector3 operator*(const Vector3& vec, const Matrix3& mat3)
     */
    Vector3 operator*(const Vector3& rhs) const;
    /**
     * @brief element-wise multiplcation.
     * @see Matrix3& operator*=(const Matrix3& rhs)
     * @see Matrix3 matmul(const Matrix3& rhs) const
     */
    Matrix3 operator*(const Matrix3& rhs) const;
    /**
     * @brief multiply 3x3 matrix with scalar.
     * @see friend Matrix3 operator*(const scalar& s, const Matrix3& mat3)
     */
    Matrix3 operator*(const scalar& rhs);
    /**
     * @brief Abbr Binary operator, element-wise multiplication of two 3x3 matrices.
     * @see Matrix3 operator*(const Matrix3& rhs) const
     */
    Matrix3& operator*=(const Matrix3& rhs);
    /**
     * @brief Abbr Binray operator, multiply 3x3 matrix with a scalar.
     * @see Matrix3 operator*(const scalar& rhs)
     */
    Matrix3& operator*=(const scalar& rhs);

    /**
     * @brief Binary operator, 3x3 matrix divided by a scalar.
     * @exception Division by zero condition with EPISION
     * @see Matrix3& operator/=(const scalar& rhs)
     */
    Matrix3 operator/(const scalar& rhs) const;
    /**
     * @brief Abbr Binary operator, 3x3 matrix divided by a scalar.
     * @exception Division by zero condition with EPISION
     * @see Matrix3 operator/(const scalar& rhs) const
     */
    Matrix3& operator/=(const scalar& rhs);

    /**
     * @brief comparsion whether two matrices are equal with EPSILON.
     * @param rhs comparison object.
     * @param e EPSILON.
     * @return bool
     * @see bool operator==(const Matrix3& rhs) const
     */
    bool equal(const Matrix3& rhs, scalar e = MYEPSILON) const;
    /**
     * @brief Equivalence overloading, exact comparsion, no epsilon.
     * @param rhs comparison object.
     * @return bool
     * @see bool equal(const Matrix3& rhs, scalar e = MYEPSILON) const
     * @see bool operator!=(const Matrix3& rhs) const
     */
    bool operator==(const Matrix3& rhs) const;
    /**
     *  @brief Inequivalence overloading, exact comparsion, no epsilon.
     *  @param rhs comparison object.
     *  @return bool
     *  @see bool operator==(const Matrix3& rhs) const
     */
    bool operator!=(const Matrix3& rhs) const;

    /**
     * @brief index[] overloading for const object.
     * @param index range from 0 to 8.
     * @exception (index > 8) or (index < 0)
     * @return raw data[index] value.
     * @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     * @brief index[] overloading.
     * @param index range from 0 to 8.
     * @exception (index > 8) or (index < 0)
     * @return raw data[index] value.
     * @see scalar operator[](int index) const
     */
    scalar& operator[](int index);

    /**
     * @brief index(i,j) overloading for const object.
     * @param i row index, range from 0 to 2.
     * @param j column index, range from 0 to 2.
     * @exception (i < 0) or (i > 2) or (j < 0) or (j > 2)
     * @return value located in index(i, j)
     * @see scalar& operator()(int i, int j)
     */
    scalar operator()(int i, int j) const;
    /**
     * @brief index(i,j) overloading.
     * @param i row index, range from 0 to 2.
     * @param j column index, range from 0 to 2.
     * @exception (i < 0) or (i > 2) or (j < 0) or (j > 2)
     * @return value located in index(i, j).
     * @see scalar operator()(int i, int j) const
     */
    scalar& operator()(int i, int j);

    /**
     * @brief unary operator, for negative Matrix3.
     * @param mat3 original matrix
     * @return negative matrix2
     */
    friend Matrix3 operator-(const Matrix3& mat3);
    /**
     * @brief multiply a scalar with a 3x3 matrix.
     * @param s scalar.
     * @param mat3 3x3 matrix.
     * @return result
     * @see Matrix3 operator*(const scalar& rhs)
     */
    friend Matrix3 operator*(const scalar& s, const Matrix3& mat3);
    /**
     * @brief multiply a 3D vector with 3x3 matrix.
     * @param vec 3D vector.
     * @param mat3 3x3 matrix.
     * @return result
     * @see Vector3 operator*(const Vector3& rhs) const
     */
    friend Vector3 operator*(const Vector3& vec, const Matrix3& mat3);
    /**
     *  @brief << overloading.
     *  @return std::ostream object
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix3& mat3);
};

/**
 *  @brief Matrix4 class used for 4x4 matrix.
 */
class Matrix4 {
private:
    /** @brief elements stored in column major. */
    scalar m[16];
    /** @brief compute the 3x3 matrix determinant compose by 9 elements with column major. */
    scalar getCofactor(scalar m0, scalar m1, scalar m2,
                       scalar m3, scalar m4, scalar m5,
                       scalar m6, scalar m7, scalar m8) const;
protected:
public:
    /**
    * Create a new 4x4 matrix object, identity by default.
    * @brief Default constructor.
    * @see Matrix4(const scalar src[16])
    * @see Matrix4(scalar m00, scalar m01, scalar m02, scalar m03,
                   scalar m04, scalar m05, scalar m06, scalar m07,
                   scalar m08, scalar m09, scalar m10, scalar m11,
                   scalar m12, scalar m13, scalar m14, scalar m15)
    */
    Matrix4();
    /**
    * Create a new 4x4 matrix object by pointer.
    * @brief constructor by a scalar pointer.
    * @warning make sure the pointer is a 16-elements array.
    * @see Matrix4()
    * @see Matrix4(scalar m00, scalar m01, scalar m02, scalar m03,
                   scalar m04, scalar m05, scalar m06, scalar m07,
                   scalar m08, scalar m09, scalar m10, scalar m11,
                   scalar m12, scalar m13, scalar m14, scalar m15)
    */
    Matrix4(const scalar src[16]);
    /**
    * Create a new 4x4 matrix object by 16 elements.
    * @brief constructor by 16 scalar elements.
    * @see Matrix4()
    * @see Matrix4(const scalar src[16])
    */
    Matrix4(scalar m00, scalar m01, scalar m02, scalar m03,
            scalar m04, scalar m05, scalar m06, scalar m07,
            scalar m08, scalar m09, scalar m10, scalar m11,
            scalar m12, scalar m13, scalar m14, scalar m15);
    /**
     * @brief Matrix4 copy constructor, deep copy.
     * @param mat4 Matrix4 object
     */
    Matrix4(const Matrix4& mat4);

    /**
     * @brief Matrix4 operator= overloading, deep copy.
     * @param mat4 Matirx3 object
     * @return Matrix4 reference
     */
    Matrix4& operator=(const Matrix4& mat4);

    /**
     * @brief set elements in Matrix4 obejct with a scalar pointer.
     * @param src scalar pointer with 16 elements stored in column major.
     * @warning make sure the pointer is a 16-elements array.
     * @see void set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
                     const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
                     const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
                     const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15)
     * @see void setRow(int index, const scalar data[4])
     * @see void setRow(int index, const Vector4& v)
     * @see void setColumn(int index, const scalar data[4])
     * @see void setColumn(int index, const Vector4& v)
     */
    void set(const scalar src[16]);
    /**
     * @brief set elements in Matrix4 object with 16 scalars.
     * @param m00 the element located in (0, 0).
     * @param m01 the element located in (1, 0).
     * @param m02 the element located in (2, 0).
     * @param m03 the element located in (3, 0).
     * @param m04 the element located in (0, 1).
     * @param m05 the element located in (1, 1).
     * @param m06 the element located in (2, 1).
     * @param m07 the element located in (3, 1).
     * @param m08 the element located in (0, 2).
     * @param m09 the element located in (1, 2).
     * @param m10 the element located in (2, 2).
     * @param m11 the element located in (3, 2).
     * @param m12 the element located in (0, 3).
     * @param m13 the element located in (1, 3).
     * @param m14 the element located in (2, 3).
     * @param m15 the element located in (3, 3).
     * @see void set(const scalar src[16])
     * @see void setRow(int index, const scalar data[4])
     * @see void setRow(int index, const Vector4& v)
     * @see void setColumn(int index, const scalar data[4])
     * @see void setColumn(int index, const Vector4& v)
     */
    void set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
             const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
             const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
             const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15);
    /**
     * @brief set elements in specified row by a pointer.
     * @param index determine specified row.
     * @param data stores the elements to be set.
     * @warning make sure the pointer is 3 elements array.
     * @exception (index > 3) or (index < 0)
     * @see void set(const scalar src[16])
     * @see void set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
     *               const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
     *               const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
     *               const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15)
     * @see void setRow(int index, const Vector4& v)
     * @see void setColumn(int index, const scalar data[4])
     * @see void setColumn(int index, const Vector4& v)
     */
    void setRow(int index, const scalar data[4]);
    /**
     * @brief set elements in specified row by a 4D vector.
     * @param index determine specified row.
     * @param v stores the elements to be set.
     * @exception (index > 3) or (index < 0)
     * @see void set(const scalar src[16])
     * @see void set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
     *               const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
     *               const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
     *               const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15)
     * @see void setRow(int index, const scalar data[4])
     * @see void setColumn(int index, const scalar data[4])
     * @see void setColumn(int index, const Vector4& v)
     */
    void setRow(int index, const Vector4& v);
    /**
     * @brief set elements in specified column by a pointer.
     * @param index determine specified column.
     * @param data stores the elements to be set.
     * @exception (index > 3) or (index < 0)
     * @warning make sure the pointer is a 3-elements array.
     * @see void set(const scalar src[16])
     * @see void set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
     *               const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
     *               const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
     *               const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15)
     * @see void setRow(int index, const scalar data[4])
     * @see void setRow(int index, const Vector4& v)
     * @see void setColumn(int index, const Vector4& v)
     */
    void setColumn(int index, const scalar data[4]);
    /**
     * @brief set elements in specified column by a 4D vector.
     * @param index determine specified column.
     * @param v stores the elements to be set.
     * @exception (index > 3) or (index < 0)
     * @see void set(const scalar src[16])
     * @see void set(const scalar& m00, const scalar& m01, const scalar& m02, const scalar& m03,
     *               const scalar& m04, const scalar& m05, const scalar& m06, const scalar& m07,
     *               const scalar& m08, const scalar& m09, const scalar& m10, const scalar& m11,
     *               const scalar& m12, const scalar& m13, const scalar& m14, const scalar& m15)
     * @see void setRow(int index, const scalar data[4])
     * @see void setRow(int index, const Vector4& v)
     * @see void setColumn(int index, const scalar data[4]);
     */
    void setColumn(int index, const Vector4& v);
    /**
     * @brief in-place operation, set as identity 4x4 matrix.
     */
    void setIdentity();

    /**
     * @brief get the contiguous address raw data(column-major) m[16].
     * @return scalar pointer of m.
     */
    scalar* data();
    /**
     * @brief get the const contiguous address raw data(column-major) m[16].
     * @return const scalar pointer of m.
     */
    const scalar* constData() const;

    /**
     * @brief get elements in specified row.
     * @param index row index.
     * @exception (index > 3) or (index < 0)
     * @return 4D Vector with index-th row elements of the Matrix.
     */
    Vector4 getRow(int index) const;
    /**
     * @brief get elements in specified column.
     * @param index column index.
     * @exception (index > 3) or (index < 0)
     * @return 4D Vector with index-th column elements of the Matrix.
     */
    Vector4 getColumn(int index) const;
    /**
     * @brief compute determinant.
     * @return determinant value.
     */
    scalar getDeterminant() const;

    /**
     * @brief judge whether this matrix is a rotation matrix.
     * @brief (R denotes 3x3 rotation matrix)
     * @brief [ R | 0 ]
     * @brief [ --+-- ]
     * @brief [ 0 | 1 ]
     * @return bool
     */
    bool isRotationMatrix() const;
    /**
     * @brief judge whether this matrix is a Euclidean matrix.
     * @brief (R denotes 3x3 rotation/reflection matrix)
     * @brief (T denotes 3x1 translation matrix)
     * @brief [ R | T ]
     * @brief [ --+-- ]
     * @brief [ 0 | 1 ]
     * @return bool
     */
    bool isEuclideanMatrix() const;
    /**
     * @brief judge whether this matrix is a Affine matrix.
     * @brief (R denotes 3x3 invertible matrix)
     * @brief (T denotes 3x1 translation matrix)
     * @brief [ R | T ]
     * @brief [ --+-- ]
     * @brief [ 0 | 1 ]
     * @return bool
     */
    bool isAffineMatrix() const;
    /**
     * @brief judge whether this matrix is a Peojective matrix.
     * @brief A, B, C, D are 2x2 matrix blocks and A is invertible matrix.
     * @brief [ A | B ]
     * @brief [ --+-- ]
     * @brief [ C | D ]
     * @return bool
     */
    bool isPeojectiveMatrix() const;


    /**
     * @brief in-place operation, transpose 4x4 matrix.
     * @see Matrix4 transposed() const
     */
    void transpose();
    /**
     * @brief transpose operation.
     * @return transposed Matrix4.
     * @see void transpose()
     */
    Matrix4 transposed() const;


    /**
     * @brief in-place operation, compute inversed 4x4 matrix.
     * @exception Inverse matrix not exists!
     * @see bool isInversed()
     */
    void inverse();
    /**
     * @brief compute inverse matrix.
     * @exception Inverse matrix not exists!
     * @return inverse matrix.
     * @see void inverse()
     */
    Matrix4 computeInverse() const;
    /**
     * @brief judge whether the matrix is reversible by determinant equal to 0 with EPISION.
     * @return bool
     * @see void inverse()
     */
    bool isInversed() const;
    /**
     * @brief computeRotationInverse
     * @brief (R denotes 3x3 rotation matrix)
     * @brief (R^{T} denotes R-transpose)
     * @brief (. denotes place-holder)
     * @brief [ R | 0 ]^{-1}..........[ R^{T} | 0 ]
     * @brief [ ..+.. ].......=.......[ ......+.. ]
     * @brief [ 0 | 1 ]...............[   0   | 1 ]
     * @exception Not a rotation matrix.
     * @return result
     */
    Matrix4 computeRotationInverse() const;
    /**
     * @brief computeEuclideanInverse
     * @brief (R denotes 3x3 rotation/reflection matrix)
     * @brief (R^{T} denotes R-transpose)
     * @brief (T denotes 3x1 translation matrix)
     * @brief (. denotes place-holder)
     * @brief [ R | T ]^{-1}..........[ R^{T} | -R^{T} * T ]
     * @brief [ ..+.. ].......=.......[ ......+........... ]
     * @brief [ 0 | 1 ]...............[    0  |      1     ]
     * @exception Not a eudlidean matrix.
     * @return result
     */
    Matrix4 computeEuclideanInverse() const;
    /**
     * @brief computeEuclideanInverse
     * @brief (R denotes 3x3 rotation/reflection matrix)
     * @brief (R^{-1} denotes R-inverse)
     * @brief (T denotes 3x1 translation matrix)
     * @brief (. denotes place-holder)
     * @brief [ R | T ]^{-1} ..........[ R^{-1} | -R^{-1} * T ]
     * @brief [ ..+.. ].......=........[ .......+............ ]
     * @brief [ 0 | 1 ]................[    0   |      1      ]
     * @exception Not a affine matrix.
     * @return result
     */
    Matrix4 computeAffineInverse() const;
    /**
     * @brief computeProjectiveInverse
     * @brief A, B, C, D are 2x2 matrix blocks and A is invertible matrix.
     * @brief (. denotes place-holder)
     * @brief [ A | B ]
     * @brief [ ..+.. ]
     * @brief [ C | D ]
     * @brief det = |A| * | D - C * A^{-1} * B|, inverse matrix is as follows
     * @brief A' = A^-1 - (A^-1 * B) * C'
     * @brief B' = -(A^-1 * B) * D'
     * @brief C' = -D' * (C * A^-1)
     * @brief D' = (D - ((C * A^-1) * B))^-1
     * @brief [ A' |  B' ]
     * @brief [ ...+.... ]
     * @brief [ C' |  D' ]
     * @warning The matrix is invertable even if det(A)=0, check det(A) before calling.
     * @exception Not a projective matrix.
     * @exception Projective matrix is not reversible.
     * @return result
     */
    Matrix4 computeProjectiveInverse() const;

    /**
     * @brief In-place operation, multiply translation matrix with this matrix.
     * @param x translation in the (1, 0, 0) direction.
     * @param y translation in the (0, 1, 0) direction.
     * @param z translation in the (0, 0, 1) direction.
     * @return self-matrix.
     */
    Matrix4& translate(scalar x, scalar y, scalar z);
    /**
     * @brief In-place operation, multiply translation matrix with this matrix.
     * @param v translation in (1, 0, 0), (0, 1, 0), (0, 0, 1) direction.
     * @return self-matrix.
     */
    Matrix4& translate(const Vector3& v);
    /**
     * @brief In-place operation, left multiplied by rotation matrix.
     * @param angle unit in degree.
     * @param x component of rotation axis.
     * @param y component of rotation axis.
     * @param z component of rotation axis.
     * @warning axis composed of rotation matrix will be normalized.
     * @return self-matrix.
     */
    Matrix4& rotate(scalar angle, scalar x, scalar y, scalar z);
    /**
     * @brief In-place operation, left multiplied by rotation matrix.
     * @param angle unit in degree.
     * @param axis rotation axis.
     * @warning axis composed of rotation matrix will be normalized.
     * @return self-matrix.
     */
    Matrix4& rotate(scalar angle, const Vector3& axis);
    /**
     * @brief In-place operation, left multiplied by rotation matrix around (1, 0, 0) dir.
     * @param angle rotation value around (1, 0, 0), unit in degree.
     * @return self-matrix.
     */
    Matrix4& rotateX(scalar angle);
    /**
     * @brief In-place operation, left multiplied by rotation matrix around (0, 1, 0) dir.
     * @param angle rotation value around (0, 1, 0), unit in degree.
     * @return self-matrix.
     */
    Matrix4& rotateY(scalar angle);
    /**
     * @brief In-place operation, left multiplied by rotation matrix around (0, 0, 1) dir.
     * @param angle rotation value around (0, 0, 1), unit in degree.
     * @return self-matrix.
     */
    Matrix4& rotateZ(scalar angle);
    /**
     * @brief In-place operation, left multiplied by scale matrix.
     * @param sx scale in (1, 0, 0).
     * @param sy scale in (1, 0, 0).
     * @param sz scale in (1, 0, 0).
     * @return self-matrix.
     */
    Matrix4& scale(scalar sx, scalar sy, scalar sz);
    /**
     * @brief In-place operation, left multiplied by scale matrix.
     * @param s diagonal value in scale matrix.
     * @return self-matrix.
     */
    Matrix4& scale(scalar s);

    /**
     * @brief Binary operator, addition of two 4x4 matrix.
     * @see Matrix4& operator+=(const Matrix4& rhs)
     */
    Matrix4 operator+(const Matrix4& rhs) const;
    /**
     * @brief Binary operator, addition of two 4x4 matrix.
     * @see Matrix4 operator+(const Matrix4& rhs) const
     */
    Matrix4& operator+=(const Matrix4& rhs);

    /**
     * @brief Binary operator, subtraction of two 4x4 matrices.
     * @see Matrix4& operator-=(const Matrix4& rhs)
     */
    Matrix4 operator-(const Matrix4& rhs) const;
    /**
     * @brief Abbr Binary operator, subtraction of two 4x4 matrices.
     * @see Matrix4& operator-(const Matrix4& rhs) const
     */
    Matrix4& operator-=(const Matrix4& rhs);

    /**
     * @brief matrix multiplication.
     * @param rhs right hand side mutiplication object.
     * @return result
     * @see Matrix4 operator*(const Matrix4& rhs) const
     */
    Matrix4 matmul(const Matrix4& rhs) const;
    /**
     * @brief multiply 4x4 matrix with 4D vector.
     * @see friend Vector4 operator*(const Vector4& vec, const Matrix4& mat4)
     */
    Vector4 operator*(const Vector4& rhs) const;
    /**
     * @brief element-wise multiplcation.
     * @see Matrix4& operator*=(const Matrix4& rhs)
     * @see Matrix4 matmul(const Matrix4& rhs) const
     */
    Matrix4 operator*(const Matrix4& rhs) const;
    /**
     * @brief multiply 4x4 matrix with scalar.
     * @see friend Matrix4 operator*(const scalar& s, const Matrix4& mat4)
     */
    Matrix4 operator*(const scalar& rhs);
    /**
     * @brief Abbr Binary operator, element-wise multiplication of two 4x4 matrices.
     * @see Matrix4 operator*(const Matrix4& rhs) const
     */
    Matrix4& operator*=(const Matrix4& rhs);
    /**
     * @brief Abbr Binray operator, multiply 4x4 matrix with scalar.
     * @see Matrix4 operator*(const scalar& rhs)
     */
    Matrix4& operator*=(const scalar& rhs);

    /**
     * @brief Binary operator, 4x4 matrix divided by a scalar.
     * @exception Division by zero condition with EPISION
     * @see Matrix4& operator/=(const scalar& rhs)
     */
    Matrix4 operator/(const scalar& rhs) const;
    /**
     * @brief Abbr Binary operator, 4x4 matrix divided by a scalar.
     * @exception Division by zero condition with EPISION
     * @see Matrix4 operator/(const scalar& rhs) const
     */
    Matrix4& operator/=(const scalar& rhs);

    /**
     * @brief comparsion whether two matrices are equal with EPSILON.
     * @param rhs comparison object.
     * @param e EPSILON.
     * @return bool
     * @see bool operator==(const Matrix4& rhs) const
     */
    bool equal(const Matrix4& rhs, scalar e = MYEPSILON) const;
    /**
     * @brief Equivalence overloading, exact comparsion, no epsilon.
     * @param rhs comparison object.
     * @return bool
     * @see bool equal(const Matrix4& rhs, scalar e = MYEPSILON) const
     * @see bool operator!=(const Matrix4& rhs) const
     */
    bool operator==(const Matrix4& rhs) const;
    /**
     *  @brief Inequivalence overloading, exact comparsion, no epsilon.
     *  @param rhs comparison object.
     *  @return bool
     *  @see bool operator==(const Matrix4& rhs) const
     */
    bool operator!=(const Matrix4& rhs) const;

    /**
     * @brief index[] overloading for const object.
     * @param index range from 0 to 15.
     * @exception (index > 15) or (index < 0)
     * @return raw data[index] value.
     * @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     * @brief index[] overloading.
     * @param index range from 0 to 15.
     * @exception (index > 15) or (index < 0)
     * @return raw data[index] value.
     * @see scalar operator[](int index) const
     */
    scalar& operator[](int index);

    /**
     * @brief index(i,j) overloading for const object.
     * @param i row index, range from 0 to 3.
     * @param j column index, range from 0 to 3.
     * @exception (i < 0) or (i > 3) or (j < 0) or (j > 3)
     * @return value located in index(i, j)
     * @see scalar& operator()(int i, int j)
     */
    scalar operator()(int i, int j) const;
    /**
     * @brief index(i,j) overloading.
     * @param i row index, range from 0 to 3.
     * @param j column index, range from 0 to 3.
     * @exception (i < 0) or (i > 3) or (j < 0) or (j > 3)
     * @return value located in index(i, j).
     * @see scalar operator()(int i, int j) const
     */
    scalar& operator()(int i, int j);

    /**
     * @brief unary operator, for negative Matrix4.
     * @param mat4 original matrix
     * @return negative matrix2
     */
    friend Matrix4 operator-(const Matrix4& mat4);
    /**
     * @brief multiply a scalar with a 4x4 matrix.
     * @param s scalar.
     * @param mat4 4x4 matrix.
     * @return result
     * @see Matrix4 operator*(const scalar& rhs)
     */
    friend Matrix4 operator*(const scalar& s, const Matrix4& mat4);
    /**
     * @brief multiply a 4D vector with 4x4 matrix.
     * @param vec 4D vector.
     * @param mat4 4x4 matrix.
     * @return result
     * @see Vector4 operator*(const Vector4& rhs) const
     */
    friend Vector4 operator*(const Vector4& vec, const Matrix4& mat4);
    /**
     *  @brief << overloading.
     *  @return std::ostream object
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix4& mat4);
};

/**
 *  Copyright (C) All rights reserved.
 *  @file mymatrix.hpp
 *  @brief 2,3,4 square matrix simple implementation, column major order
 *  @author haofan ren, yqykrhf@163.com
 *  @version beta 0.0
 *  @date 2222-2-26
 *  @todo function data() issue, when multiple pointer point that, memory management.
 *  @note The elements of the matrix are stored as column major order.
 *   | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
 *   | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
 *              | 2 5 8 |    |  2  6 10 14 |
 *                           |  3  7 11 15 |
 */

#pragma once

#include "myvector.hpp"

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
    * Create a new 2x2 matrix object, Identity.
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
     * @exception (index > 2) or (index < 0)
     * @return 2D Vector with index-th row elements of the Matrix.
     */
    Vector2 getRow(int index) const;
    /**
     * @brief get elements in specified column.
     * @param index column index.
     * @exception (index > 2) or (index < 0)
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
     * @return rotation angle in the interval [-&pi,+&pi] radian or [-180, +180] degree.
     */
    scalar getAngle(ANGLEUNIT unit = DEG) const;
    /**
     * @brief judge whether this matrix is a rotation matrix.
     * @return bool
     */
    bool isRotationMatrix() const;

    /**
     * @brief in-place operation, transpose 2x2 matrix.
     * @see Matrix2 transposed()
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
     * @brief multiply 2x2 matrix with 2x2 matrix.
     * @see Matrix2& operator*=(const Matrix2& rhs)
     * @see Matrix2 matmul(const Matrix2& rhs) const
     */
    Matrix2 operator*(const Matrix2& rhs) const;
    /**
     * @brief multiply 2x2 matrix with scalar.
     * @see friend Matrix2 operator*(const scalar& s, const Matrix2& mat2)
     */
    Matrix2 operator*(const scalar& rhs);
    /**
     * @brief Abbr Binary operator, element-wise multiplication of two 2x2 matrices.
     * @see Matrix2 operator*(const Matrix2& rhs) const
     */
    Matrix2& operator*=(const Matrix2& rhs);
    /**
     * @brief Abbr Binray operator, multiply 2x2 matrix with scalar.
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
    ANGLEUNIT au = DEG;

  protected:
  public:
    /**
    * Create a new 3x3 matrix object, Identity.
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
     *               const scalar& m3, const scalar& m4, const scalar& m5,
     *               const scalar& m6, const scalar& m7, const scalar& m8)
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
     * @see Matrix3 transposed()
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
     * @brief Abbr Binray operator, multiply 3x3 matrix with scalar.
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
     * @param index range from 0 to 2.
     * @exception (index > 8) or (index < 0)
     * @return raw data[index] value.
     * @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     * @brief index[] overloading.
     * @param index range from 0 to 2.
     * @exception (index > 8) or (index < 0)
     * @return raw data[index] value.
     * @see scalar operator[](int index) const
     */
    scalar& operator[](int index);

    /**
     * @brief index(i,j) overloading for const object.
     * @param i row index, range from 0 to 1.
     * @param j column index, range from 0 to 1.
     * @exception (i < 0) or (i > 2) or (j < 0) or (j > 2)
     * @return value located in index(i, j)
     * @see scalar& operator()(int i, int j)
     */
    scalar operator()(int i, int j) const;
    /**
     * @brief index(i,j) overloading.
     * @param i row index, range from 0 to 1.
     * @param j column index, range from 0 to 1.
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

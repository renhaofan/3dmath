/**
 *  Copyright (C) All rights reserved.
 *  @file mymatrix.hpp
 *  @brief 2,3,4 square matrix simple implementation, column major order
 *  @author haofan ren, yqykrhf@163.com
 *  @version beta 0.0
 *  @date 2222-2-26
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
    /** @brief elements stored in raw major for transpose */
    scalar mt[4];

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
    * @brief constructor by scalar pointer
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
     * @param mat2: Matirx2 object
     * @return Matrix2 reference
     */
    Matrix2& operator=(const Matrix2& mat2);

    /**
     * @brief set elements in Matrix2 obejct with scalar pointer.
     * @param src scalar pointer with 4 elements stored in column major.
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void set(const scalar src[4]);


    /**
     * @brief set elements in Matrix2 object with 4 scalars.
     * @param m0 the element located in (0, 0)
     * @param m1 the element located in (1, 0)
     * @param m2 the element located in (0, 1)
     * @param m3 the element located in (1, 1)
     * @see void set(const scalar src[4])
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3);

    /**
     * @brief set elements in specified row by pointer
     * @param index determine specified row
     * @param data stores the elements to be set
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void setRow(int index, const scalar data[2]);

    /**
     * @brief set elements in specified row by 2D vector
     * @param index determine specified row
     * @param v stores the elements to be set
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setColumn(int index, const scalar data[2])
     * @see void setColumn(int index, const Vector2& v)
     */
    void setRow(int index, const Vector2& v);
    /**
     * @brief set elements in specified column by pointer
     * @param index determine specified column
     * @param v stores the elements to be set
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const Vector2& v)
     */
    void setColumn(int index, const scalar data[2]);
    /**
     * @brief set elements in specified column by 2D vector
     * @param index determine specified column
     * @param v stores the elements to be set
     * @see void set(const scalar src[4])
     * @see void set(const scalar& m0, const scalar& m1, const scalar& m2, const scalar& m3)
     * @see void setRow(int index, const scalar data[2])
     * @see void setRow(int index, const Vector2& v)
     * @see void setColumn(int index, const scalar data[2]);
     */
    void setColumn(int index, const Vector2& v);

    /**
     * @brief get the contiguous address raw data(column-major) m[4]
     * @return scalar pointer of m
     */
    scalar* data();
    /**
     * @brief get the contiguous address raw data(row-major) mt[4]
     * @return scalar pointer of mt
     */
    scalar* dataTranspose();

    /**
     * @brief get the contiguous address const raw data(column-major) m[4]
     * @return const scalar pointer of m
     */
    const scalar* get() const;
    /**
     * @brief get the contiguous address const raw data(row-major) mt[4]
     * @return const scalar pointer of mt
     */
    const scalar* getTranspose();

    /**
     * @brief get elements in specified row
     * @param index row index
     * @return 2D Vector with index-th row elements
     */
    Vector2 getRow(int index) const;
    /**
     * @brief get elements in specified column
     * @param index column index
     * @return 2D Vector with index-th column elements
     */
    Vector2 getColumn(int index) const;

    /**
     * @brief compute determinant
     * @return determinant value
     */
    scalar getDeterminant() const;
    /**
     * @brief extract angle from 2x2 rotation matrix
     * @param unit determint the returned angle unit(degree or radians)
     * @return rotation angle
     */
    scalar getAngle(ANGLEUNIT unit = DEG) const;

    /**
     * @brief in-place operation, set as identity 2x2 matrix.
     * @return self-matrix
     */
    Matrix2& identity();
    /**
     * @brief in-place operation, set as transposed 2x2 matrix.
     * @return self-matrix
     */
    Matrix2& transpose();
    /**
     * @brief in-place operation, set as inversed 2x2 matrix.
     * @return self-matrix
     */
    Matrix2& inverse();

    Matrix2 operator+(const Matrix2& rhs) const;
    Matrix2& operator+=(const Matrix2& rhs);

    Matrix2 operator-(const Matrix2& rhs) const;
    Matrix2& operator-=(const Matrix2& rhs);

    Vector2 operator*(const Vector2& rhs) const;
    Matrix2 operator*(const Matrix2& rhs) const;
    Matrix2 operator*(const scalar& rhs);

    Matrix2& operator*=(const Matrix2& rhs);

    bool equal(const Matrix2& rhs, scalar e = MYEPSILON) const;
    bool operator==(const Matrix2& rhs) const;
    bool operator!=(const Matrix2& rhs) const;

    scalar operator[](int index) const;
    scalar& operator[](int index);

    scalar operator()(int i, int j) const;
    scalar& operator()(int i, int j);

    friend Matrix2 operator-(const Matrix2& mat2); // unary
    friend Matrix2 operator*(const scalar& s, const Matrix2& mat2);
    friend Vector2 operator*(const Vector2& vec, const Matrix2& mat2);
    friend std::ostream& operator<<(std::ostream& os, const Matrix2& mat2);
};

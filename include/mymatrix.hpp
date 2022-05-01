/**
 *  Copyright (C) All rights reserved.
 *  @file mymatrix.hpp
 *  @brief 2,3,4 square matrix simple implementation
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
    * @see Matrix2(const scalar* src)
    * @see Matrix2(scalar m0, scalar m1, scalar m2, scalar m3)
    */
    Matrix2();
    /**
    * Create a new 2x2 matrix object by pointer.
    * @brief constructor by pointer
    * @see Matrix2()
    * @see Matrix2(scalar m0, scalar m1, scalar m2, scalar m3)
    */
    Matrix2(const scalar* src);
    /**
    * Create a new 2x2 matrix object by 4 elements.
    * @brief constructor by 4 elements.
    * @see Matrix2()
    * @see Matrix2(const scalar* src)
    */
    Matrix2(scalar m0, scalar m1, scalar m2, scalar m3);

    void set(const scalar* src);
    void set(scalar m0, scalar m1, scalar m2, scalar m3);
    void setRow(int index, const scalar* row);
    void setRow(int index, const Vector2& v);
    void setColumn(int index, const scalar* row);
    void setColumn(int index, const Vector2& v);

    const scalar* data() const;
    const scalar* dataTranspose() const;

    const scalar* get() const;
    const scalar* getTranspose() const;

    Vector2 getRow(int index) const;
    Vector2 getColumn(int index) const;

    scalar getDeterminant() const;
    scalar getAngle() const; // retrieve angle degree from matrix

    Matrix2& identity();
    Matrix2& transpose();
    Matrix2& inverse();

    Matrix2& operator+(const Matrix2& rhs) const;
    Matrix2& operator+=(const Matrix2& rhs) const;

    Matrix2& operator-(const Matrix2& rhs) const;
    Matrix2& operator-=(const Matrix2& rhs) const;








};

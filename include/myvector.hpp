/**
 *  Copyright (C) All rights reserved.
 *  @file myvector.hpp
 *  @brief 2D,3D,4D vector simple implementation
 *  @author haofan ren
 *  @version 0.0
 *  @date 2022-4-26
 *  @note comment ref:https://www.cnblogs.com/huipengly/p/9257012.html
 *  @note comment ref:https://www.doxygen.nl/manual/docblocks.html
 */

#pragma once
#include <iostream>
#include <cmath>

/**
 *  @brief: Use double or float as scalar type, float by deatult.
    add option `-DUSING_FLOAT64` when compile if double type needed.
 */
#ifdef USING_FLOAT64
typedef double scalar;
#else
typedef float scalar;
#endif

/**
 *  @brief Macro about float number equal operation.
 */
#define MYEPSILON 1e-6


/**
 *  @brief Vector2 class used for 2D vector.
 */
struct Vector2 {
   /**
    * data in 2D vector.
    */
    scalar x, y;

   /**
     *  Create a new 2D vector object (0, 0).
     *  @brief Default constructor.
     *  @see Vector2(scalar _x, scalar _y)
     */
    Vector2() :
        x(0), y(0){};
    /**
     *  Create a new 2D vector object (0, 0).
     *  @brief Default constructor.
     *  @see Vector2()
     */
    Vector2(scalar _x, scalar _y) :
        x(_x), y(_y){};

    /** @brief Set member variables x,y. */
    void set(scalar _x, scalar _y);
    /** @brief Return length of the vector. */
    scalar length() const;
    /** @brief Alias of length(). */
    scalar norm() const;
    /** @brief Euclidean distance bewteen two vectros. */
    scalar distance(const Vector2& vec) const;
    /** @brief Return the normalized vector. */
    Vector2 normalized() const;
    /** @brief In-place operation, normalized vector. */
    void normalize();
    /** @brief Dot product between two vectors. */
    scalar dot(const Vector2& vec) const;
    /** @brief Determine if the 2D vector object is similar to the other. */
    bool equal(const Vector2& vec, scalar e = MYEPSILON) const;

    /** @brief Unary operator, negate a 2D vector. */
    Vector2 operator-() const;

    /**
     *  @brief Binary operator, addition of two 2D vector.
     *  @see operator+=(const Vector2& rhs)
     */
    Vector2 operator+(const Vector2& rhs) const;
    /**
     *  @brief Abbr binary operator, addition of two 2D vector.
     *  @see operator+(const Vector2& rhs)
     */
    Vector2& operator+=(const Vector2& rhs);

    /**
     *  @brief Binary operator, subtraction of two 2D vectors.
     *  @see operator-=(const Vector2& rhs)
     */
    Vector2 operator-(const Vector2& rhs) const;

    /**
     *  @brief Abbr binary operator, subtraction of two 2D vectors.
     *  @see operator-(const Vector2& rhs) const
     */
    Vector2& operator-=(const Vector2& rhs);

    /**
     *  @brief Binary operator, multiplication between two 2D vectors.
     *  @see operator*=(const Vector2& rhs)
     */
    Vector2 operator*(const Vector2& rhs) const;
    /**
     *  @brief Abbr binary operator, multiplication between two 2D vectors.
     *  @see operator*(const Vector2& rhs) const
     */
    Vector2& operator*=(const Vector2& rhs);


    /**
     *  @brief Binary operator, 2D vector times scalar.
     *  @see operator*=(const scalar scale)
     */
    Vector2 operator*(const scalar scale) const;
    /**
     *  @brief Abbr binary operator, 2D vector times scalar.
     *  @see operator*(const scalar scale) const
     */
    Vector2& operator*=(const scalar scale);


    /**
     *  @brief Binary operator, 2D vector divided by scalar.
     *  @see operator/=(const scalar scale)
     */
    Vector2 operator/(const scalar scale) const;
    /**
     *  @brief Abbr binary operator, 2D vector divided by scalar.
     *  @see operator/(const scalar scale) const
     */
    Vector2& operator/=(const scalar scale);

    /**
     *  @brief Equivalence overloading, exact comparsion, no epsilon.
     *  @param rhs another 2D vector object.
     *  @return Whether the two 2D vector objects are the same.
     *  @see operator!=(const Vector2& rhs) const;
     */
    bool operator==(const Vector2& rhs) const;
    /**
     *  @brief Inequivalence overloading, exact comparsion, no epsilon.
     *  @param rhs another 2D vector object.
     *  @return Whether the two 2D vector objects are not the same.
     *  @see operator==(const Vector2& rhs) const;
     */
    bool operator!=(const Vector2& rhs) const;
    /**
     *  @brief comparsion overloading, for the purpose of sort.
     *  @param rhs another 2D vector object.
     *  @return Whether 2D vector object is less than another.
     */
    bool operator<(const Vector2& rhs) const;

    /**
     *  @brief index[] overloading.
     *  @param index 2D vector w, w[index].
     *  @return member variable, w[index], w[0], w[1]
     */
    scalar operator[](int index) const;
    /**
     *  @brief index[] overloading.
     *  @param index 2D vector w, w[index].
     *  @return member variable, w[index]
     */
    scalar& operator[](int index);

    /**
     *  @brief scalar times 2D vector.
     *  @return 2D vector.
     */
    friend Vector2 operator*(const scalar a, const Vector2 vec);
    /**
     *  @brief << overloading.
     *  @return std::ostream object
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};

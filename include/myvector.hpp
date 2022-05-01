/**
 *  Copyright (C) All rights reserved.
 *  @file myvector.hpp
 *  @brief 2D,3D,4D vector simple implementation
 *  @author haofan ren, yqykrhf@163.com
 *  @version beta 0.0
 *  @date 2222-2-26
 *  @note comment ref:https://www.doxygen.nl/manual/docblocks.html
 *  @todo copy constructor for constrain w(v), w = v, and deepcopy
 *  @todo raw.data() as pointer.
 */

#pragma once
#include <iostream>
#include <cmath>

/**
 *  @brief: Use double or float as basic scalar type, float by deatult.
    add option `-DUSING_FLOAT64` when compile if double type needed or
    `#define USING_FLOAT64` before `#include "myvector.hpp"`
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
 *  @brief Macro convert radians to degree
 */
#define RAD2DEG 180.0 / 3.141592653579

/**
 *  @brief Macro convert degree to radians
 */
#define DEG2RAD 3.141592653579 / 180.0

/**
 *  @brief choices for function angle in Vector3
 */
enum ANGLEUNIT { RAD,
                 DEG };

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
     *  Create a new 2D vector object (_x, _y).
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
     *  @see operator>(const Vector2& rhs) const;
     */
    bool operator<(const Vector2& rhs) const;
    /**
     *  @brief comparsion overloading, for the purpose of sort.
     *  @param rhs another 2D vector object.
     *  @return Whether 2D vector object is more than another.
     *  @see operator<(const Vector2& rhs) const;
     */
    bool operator>(const Vector2& rhs) const;

    /**
     *  @brief const object index[] overloading.
     *  @param index 2D vector w, w[index].
     *  @return member variable, w[index], w[0], w[1]
     *  @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     *  @brief index[] overloading.
     *  @param index 2D vector w, w[index].
     *  @return member variable, w[index]
     *  @see scalar operator[](int index) const
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

/**
 *  @brief Vector3 class used for 3D vector.
 */
struct Vector3 {
    /**
    * data in 3D vector.
    */
    scalar x, y, z;

    /**
     *  Create a new 3D vector object (0, 0, 0).
     *  @brief Default constructor.
     *  @see Vector3(scalar _x, scalar _y)
     */
    Vector3() :
        x(0), y(0), z(0){};
    /**
     *  Create a new 3D vector object (_x, _y, _z).
     *  @brief Default constructor.
     *  @see Vector3()
     */
    Vector3(scalar _x, scalar _y, scalar _z) :
        x(_x), y(_y), z(_z){};

    /** @brief Set member variables x,y,z. */
    void set(scalar _x, scalar _y, scalar _z);
    /** @brief Return length of the vector. */
    scalar length() const;
    /** @brief Alias of length(). */
    scalar norm() const;
    /** @brief Euclidean distance bewteen two vectros. */
    scalar distance(const Vector3& vec) const;
    /** @brief angle bewteen two vectros.
     *  @param vec another vector.
     *  @param unit determine the returned unit--radian or degree.
     *  angle(Vector3, DEG) or angle(Vector3, RAD)
     *  @return angle in degree [0, 180] or [0, pi]
     */
    scalar angle(const Vector3& vec, ANGLEUNIT unit = DEG) const;
    /** @brief Return the normalized vector. */
    Vector3 normalized() const;
    /** @brief In-place operation, normalized vector. */
    void normalize();
    /** @brief Dot product between two vectors. */
    scalar dot(const Vector3& vec) const;
    /** @brief cross product between two vectors. */
    Vector3 cross(const Vector3& rhs) const;
    /** @brief Determine if the 3D vector object is similar to the other. */
    bool equal(const Vector3& vec, scalar e = MYEPSILON) const;

    /** @brief Unary operator, negate a 3D vector. */
    Vector3 operator-() const;

    /**
     *  @brief Binary operator, addition of two 3D vector.
     *  @see operator+=(const Vector3& rhs)
     */
    Vector3 operator+(const Vector3& rhs) const;
    /**
     *  @brief Abbr binary operator, addition of two 3D vector.
     *  @see operator+(const Vector3& rhs)
     */
    Vector3& operator+=(const Vector3& rhs);

    /**
     *  @brief Binary operator, subtraction of two 3D vectors.
     *  @see operator-=(const Vector3& rhs)
     */
    Vector3 operator-(const Vector3& rhs) const;

    /**
     *  @brief Abbr binary operator, subtraction of two 3D vectors.
     *  @see operator-(const Vector3& rhs) const
     */
    Vector3& operator-=(const Vector3& rhs);

    /**
     *  @brief Binary operator, multiplication between two 3D vectors.
     *  @see operator*=(const Vector3& rhs)
     */
    Vector3 operator*(const Vector3& rhs) const;
    /**
     *  @brief Abbr binary operator, multiplication between two 3D vectors.
     *  @see operator*(const Vector3& rhs) const
     */
    Vector3& operator*=(const Vector3& rhs);

    /**
     *  @brief Binary operator, 3D vector times scalar.
     *  @see operator*=(const scalar scale)
     */
    Vector3 operator*(const scalar scale) const;
    /**
     *  @brief Abbr binary operator, 3D vector times scalar.
     *  @see operator*(const scalar scale) const
     */
    Vector3& operator*=(const scalar scale);

    /**
     *  @brief Binary operator, 3D vector divided by scalar.
     *  @see operator/=(const scalar scale)
     */
    Vector3 operator/(const scalar scale) const;
    /**
     *  @brief Abbr binary operator, 3D vector divided by scalar.
     *  @see operator/(const scalar scale) const
     */
    Vector3& operator/=(const scalar scale);

    /**
     *  @brief Equivalence overloading, exact comparsion, no epsilon.
     *  @param rhs another 3D vector object.
     *  @return Whether the two 3D vector objects are the same.
     *  @see operator!=(const Vector3& rhs) const;
     */
    bool operator==(const Vector3& rhs) const;
    /**
     *  @brief Inequivalence overloading, exact comparsion, no epsilon.
     *  @param rhs another 3D vector object.
     *  @return Whether the two 3D vector objects are not the same.
     *  @see operator==(const Vector3& rhs) const;
     */
    bool operator!=(const Vector3& rhs) const;
    /**
     *  @brief comparsion overloading, for the purpose of sort.
     *  @param rhs another 3D vector object.
     *  @return Whether 3D vector object is less than another.
     *  @see operator>(const Vector3& rhs) const
     */
    bool operator<(const Vector3& rhs) const;
    /**
     *  @brief comparsion overloading, for the purpose of sort.
     *  @param rhs another 3D vector object.
     *  @return Whether 3D vector object is more than another.
     *  @see operator>(const Vector3& rhs) const
     */
    bool operator>(const Vector3& rhs) const;

    /**
     *  @brief const object index[] overloading.
     *  @param index 3D vector w, w[index].
     *  @return member variable, w[index], w[0], w[1]
     *  @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     *  @brief index[] overloading.
     *  @param index 3D vector w, w[index].
     *  @return member variable, w[index]
     *  @see scalar operator[](int index) const;
     */
    scalar& operator[](int index);

    /**
     *  @brief scalar times 3D vector.
     *  @return 3D vector.
     */
    friend Vector3 operator*(const scalar a, const Vector3 vec);
    /**
     *  @brief << overloading.
     *  @return std::ostream object
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

/**
 *  @brief Vector4 class used for 2D vector.
 */

struct Vector4 {
    /**
    * data in 4D vector.
    */
    scalar x, y, z, w;

    /**
     *  Create a new 4D vector object (0, 0, 0, 0).
     *  @brief Default constructor.
     *  @see Vector4(scalar _x, scalar _y, scalar _z, scalar _w)
     */
    Vector4() :
        x(0), y(0), z(0), w(0){};
    /**
     *  Create a new 4D vector object (_x, _y, _z, _w).
     *  @brief Default constructor.
     *  @see Vector4()
     */
    Vector4(scalar _x, scalar _y, scalar _z, scalar _w) :
        x(_x), y(_y), z(_z), w(_w){};

    /** @brief Set member variables x,y,z,w. */
    void set(scalar _x, scalar _y, scalar _z, scalar _w);
    /** @brief Return length of the vector. */
    scalar length() const;
    /** @brief Alias of length(). */
    scalar norm() const;
    /** @brief Euclidean distance bewteen two vectros. */
    scalar distance(const Vector4& vec) const;
    /** @brief Return the normalized vector. */
    Vector4 normalized() const;
    /** @brief In-place operation, normalized vector. */
    void normalize();
    /** @brief Dot product between two vectors. */
    scalar dot(const Vector4& vec) const;
    /** @brief Determine if the 4D vector object is similar to the other. */
    bool equal(const Vector4& vec, scalar e = MYEPSILON) const;

    /** @brief Unary operator, negate a 4D vector. */
    Vector4 operator-() const;

    /**
     *  @brief Binary operator, addition of two 4D vector.
     *  @see operator+=(const Vector4& rhs)
     */
    Vector4 operator+(const Vector4& rhs) const;
    /**
     *  @brief Abbr binary operator, addition of two 4D vector.
     *  @see operator+(const Vector4& rhs)
     */
    Vector4& operator+=(const Vector4& rhs);

    /**
     *  @brief Binary operator, subtraction of two 4D vectors.
     *  @see operator-=(const Vector4& rhs)
     */
    Vector4 operator-(const Vector4& rhs) const;

    /**
     *  @brief Abbr binary operator, subtraction of two 4D vectors.
     *  @see operator-(const Vector4& rhs) const
     */
    Vector4& operator-=(const Vector4& rhs);

    /**
     *  @brief Binary operator, multiplication between two 4D vectors.
     *  @see operator*=(const Vector4& rhs)
     */
    Vector4 operator*(const Vector4& rhs) const;
    /**
     *  @brief Abbr binary operator, multiplication between two 4D vectors.
     *  @see operator*(const Vector4& rhs) const
     */
    Vector4& operator*=(const Vector4& rhs);

    /**
     *  @brief Binary operator, 4D vector times scalar.
     *  @see operator*=(const scalar scale)
     */
    Vector4 operator*(const scalar scale) const;
    /**
     *  @brief Abbr binary operator, 4D vector times scalar.
     *  @see operator*(const scalar scale) const
     */
    Vector4& operator*=(const scalar scale);

    /**
     *  @brief Binary operator, 4D vector divided by scalar.
     *  @see operator/=(const scalar scale)
     */
    Vector4 operator/(const scalar scale) const;
    /**
     *  @brief Abbr binary operator, 4D vector divided by scalar.
     *  @see operator/(const scalar scale) const
     */
    Vector4& operator/=(const scalar scale);

    /**
     *  @brief Equivalence overloading, exact comparsion, no epsilon.
     *  @param rhs another 4D vector object.
     *  @return Whether the two 4D vector objects are the same.
     *  @see operator!=(const Vector4& rhs) const;
     */
    bool operator==(const Vector4& rhs) const;
    /**
     *  @brief Inequivalence overloading, exact comparsion, no epsilon.
     *  @param rhs another 4D vector object.
     *  @return Whether the two 4D vector objects are not the same.
     *  @see operator==(const Vector4& rhs) const;
     */
    bool operator!=(const Vector4& rhs) const;
    /**
     *  @brief comparsion overloading, for the purpose of sort.
     *  @param rhs another 4D vector object.
     *  @return Whether 4D vector object is less than another.
     *  @see operator>(const Vector4& rhs) const;
     */
    bool operator<(const Vector4& rhs) const;
    /**
     *  @brief comparsion overloading, for the purpose of sort.
     *  @param rhs another 4D vector object.
     *  @return Whether 4D vector object is more than another.
     *  @see operator<(const Vector4& rhs) const;
     */
    bool operator>(const Vector4& rhs) const;

    /**
     *  @brief const object index[] overloading.
     *  @param index 4D vector w, w[index].
     *  @return member variable, w[index], w[0], w[1]
     *  @see scalar& operator[](int index)
     */
    scalar operator[](int index) const;
    /**
     *  @brief index[] overloading.
     *  @param index 4D vector w, w[index].
     *  @return member variable, w[index]
     *  @see scalar operator[](int index) const
     */
    scalar& operator[](int index);

    /**
     *  @brief scalar times 4D vector.
     *  @return 4D vector.
     */
    friend Vector4 operator*(const scalar a, const Vector4 vec);
    /**
     *  @brief << overloading.
     *  @return std::ostream object
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
};

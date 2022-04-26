#pragma once

#ifdef USING_FLOAT64
typedef double scalar;
#else
typedef float scalar;
#endif

#define MYEPSILON 1e-6

#include <iostream>
#include <cmath>

struct Vector2 {
    //    union {
    //        scalar data[4];
    //        struct {
    //            scalar x, y;
    //        };
    //    };
    scalar x, y;

    // contructor
    Vector2(){};
    Vector2(scalar _x, scalar _y) :
        x(_x), y(_y){};

    // utils functions
    void set(scalar _x, scalar _y);
    scalar length() const;
    scalar norm() const;
    scalar distance(const Vector2& vec) const;
    Vector2 normalized() const;
    void normalize();
    scalar dot(const Vector2& vec) const;
    bool equal(const Vector2& vec, scalar e = MYEPSILON) const; // compare with epsilon

    // operators
    Vector2 operator-() const; // unary operator (negate)

    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);

    Vector2 operator*(const Vector2& rhs) const;
    Vector2 operator*(const scalar scale) const;
    Vector2& operator*=(const Vector2& rhs);
    Vector2& operator*=(const scalar scale);

    Vector2 operator/(const scalar scale) const;
    Vector2& operator/=(const scalar scale);

    bool operator==(const Vector2& rhs) const; // exact compare, no epsilon
    bool operator!=(const Vector2& rhs) const; // exact compare, no epsilon
    bool operator<(const Vector2& rhs) const;  // for sort

    scalar operator[](int index) const; // subscript operator v[0], v[1]
    scalar& operator[](int index);      // subscript operator v[0], v[1]

    friend Vector2 operator*(const float a, const Vector2 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};

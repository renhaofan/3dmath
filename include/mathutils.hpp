#pragma once

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

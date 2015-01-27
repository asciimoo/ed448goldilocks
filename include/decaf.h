/* Copyright (c) 2015 Cryptography Research, Inc.
 * Released under the MIT License.  See LICENSE.txt for license information.
 */

/**
 * @file decaf.h
 * @author Mike Hamburg
 * @brief A group of prime order p.
 *
 * The Decaf library implements cryptographic operations on a an elliptic curve
 * group of prime order p.  It accomplishes this by using a twisted Edwards
 * curve (isogenous to Ed448-Goldilocks) and wiping out the cofactor.
 *
 * The formulas are all complete and have no special cases, except that
 * decaf_decode can fail because not every sequence of bytes is a valid group
 * element.
 *
 * The formulas contain no data-dependent branches, timing or memory accesses.
 */
#ifndef __DECAF_H__
#define __DECAF_H__ 1

#include <stdint.h>

typedef uint64_t decaf_word_t, decaf_bool_t;
#define DECAF_LIMBS (512/8/sizeof(decaf_word_t))
#define DECAF_SER_BYTES 56
typedef struct decaf_point_s {
    decaf_word_t x[DECAF_LIMBS],y[DECAF_LIMBS],z[DECAF_LIMBS],t[DECAF_LIMBS];
} decaf_point_t[1];

static const decaf_bool_t DECAF_TRUE = -(decaf_bool_t)1, DECAF_FALSE = 0;
static const decaf_bool_t DECAF_SUCCESS = DECAF_TRUE, DECAF_FAILURE = DECAF_FALSE;

const decaf_point_t decaf_identity;

#ifdef __cplusplus
extern "C" {
#endif
    
#define API_VIS __attribute__((visibility("default")))
#define WARN_UNUSED __attribute__((warn_unused_result))
#define NONNULL2 __attribute__((nonnull(1,2)))
#define NONNULL3 __attribute__((nonnull(1,2,3)))

/**
 * @brief Encode a point as a sequence of bytes.
 *
 * @param [out] ser The byte representation of the point.
 * @param [in] pt The point to encode.
 */
void decaf_encode (
    uint8_t ser[DECAF_SER_BYTES],
    const decaf_point_t pt
) API_VIS NONNULL2;

/**
 * @brief Decode a point from a sequence of bytes.
 *
 * Every point has a unique encoding, so not every
 * sequence of bytes is a valid encoding.  If an invalid
 * encoding is given, the output is undefined.
 *
 * @param [out] pt The decoded point.
 * @param [in] ser The serialized version of the point.
 * @retval DECAF_SUCCESS The decoding succeeded.
 * @retval DECAF_FAILURE The decoding didn't succeed, because
 * ser does not represent a point.
 */
decaf_bool_t decaf_decode (
    decaf_point_t pt,
    const uint8_t ser[DECAF_SER_BYTES],
    decaf_bool_t allow_identity
) API_VIS WARN_UNUSED NONNULL2;

/**
 * @brief Copy a point.  The input and output may alias,
 * in which case this function does nothing.
 *
 * @param [out] a A copy of the point.
 * @param [in] b Any point.
 */
void decaf_copy (
    decaf_point_t a,
    const decaf_point_t b
) API_VIS NONNULL2;

/**
 * @brief Test whether two points are equal.  If yes, return
 * DECAF_TRUE, else return DECAF_FALSE.
 *
 * @param [in] a A point.
 * @param [in] b Another point.
 * @retval DECAF_TRUE The points are equal.
 * @retval DECAF_FALSE The points are not equal.
 */
decaf_bool_t decaf_eq (
    const decaf_point_t a,
    const decaf_point_t b
) API_VIS WARN_UNUSED NONNULL2;

/**
 * @brief Add two points to produce a third point.  The
 * input points and output point can be pointers to the same
 * memory.
 *
 * @param [out] sum The sum a+b.
 * @param [in] a An addend.
 * @param [in] b An addend.
 */
void decaf_add (
    decaf_point_t sum,
    const decaf_point_t a,
    const decaf_point_t b
) API_VIS NONNULL3;

/**
 * @brief Subtract two points to produce a third point.  The
 * input points and output point can be pointers to the same
 * memory.
 *
 * @param [out] sum The difference a-b.
 * @param [in] a The minuend.
 * @param [in] b The subtrahend.
 */
void decaf_sub (
    decaf_point_t diff,
    const decaf_point_t a,
    const decaf_point_t b
) API_VIS NONNULL3;

/**
 * @brief Multiply a base point by a scalar.
 *
 * @param [out] scaled The scaled point base*scalar
 * @param [in] base The point to be scaled.
 * @param [in] scalar The scalar to multilpy by.
 * @param [in] scalar_words The number of words in the scalar [TODO]
 */
void decaf_scalarmul (
    decaf_point_t scaled,
    const decaf_point_t base,
    const decaf_word_t *scalar,
    unsigned int scalar_words
) API_VIS NONNULL3;
    
#undef API_VIS
#undef WARN_UNUSED
#undef NONNULL2
#undef NONNULL3

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif /* __DECAF_H__ */

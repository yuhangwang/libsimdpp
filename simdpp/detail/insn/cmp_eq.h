/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_EQ_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_EQ_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_shift_l.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/detail/null/compare.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline mask_int8x16 i_cmp_eq(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8x32 i_cmp_eq(uint8x32 a, uint8x32 b)
{
    return _mm256_cmpeq_epi8(a, b);
}
#endif

template<unsigned N>
mask_int8<N> i_cmp_eq(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, i_cmp_eq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int16x8 i_cmp_eq(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int16x16 i_cmp_eq(uint16x16 a, uint16x16 b)
{
    return _mm256_cmpeq_epi16(a, b);
}
#endif

template<unsigned N>
mask_int16<N> i_cmp_eq(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, i_cmp_eq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int32x4 i_cmp_eq(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int32x8 i_cmp_eq(uint32x8 a, uint32x8 b)
{
    return _mm256_cmpeq_epi32(a, b);
}
#endif

template<unsigned N>
mask_int32<N> i_cmp_eq(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, i_cmp_eq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int64x2 i_cmp_eq(uint64x2 a, uint64x2 b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_eq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comeq_epi64(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_cmpeq_epi64(a, b);
#elif SIMDPP_USE_SSE2
    uint64x2 r32, r32s;
    r32 = i_cmp_eq(uint32x4(a), uint32x4(b));
    // swap the 32-bit halves
    r32s = bit_or(shift_l<32>(r32), shift_r<32>(r32));
    // combine the results. Each 32-bit half is ANDed with the neighbouring pair
    r32 = bit_and(r32, r32s);
    return r32;
#elif SIMDPP_USE_NEON
    uint32x4 r32, r32s;
    r32 = cmp_eq(uint32x4(a), uint32x4(b));
    r32s = r32;
    // swap the 32-bit halves
    transpose2(r32, r32s);
    // combine the results. Each 32-bit half is ANDed with the neighbouring pair
    r32 = bit_and(r32, r32s);
    return uint64x2(r32);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 mask = make_shuffle_bytes16_mask<0, 2, 1, 3>(mask);
    uint32x4 a0, b0, r;
    a0 = a;  b0 = b;
    r = cmp_eq(a, b);
    r = permute_bytes16(uint16x8(a), mask);
    r = cmp_eq(r, uint32x4::zero();
    return r;
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int64x4 i_cmp_eq(uint64x4 a, uint64x4 b)
{
    return _mm256_cmpeq_epi64(a, b);
}
#endif

template<unsigned N>
mask_int64<N> i_cmp_eq(uint64<N> a, uint64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int64<N>, i_cmp_eq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float32x4 i_cmp_eq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_eq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_EQ_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_ps(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32x8 i_cmp_eq(float32x8 a, float32x8 b)
{
    return _mm256_cmp_ps(a, b, _CMP_EQ_OQ);
}
#endif

template<unsigned N>
mask_float32<N> i_cmp_eq(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_cmp_eq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float64x2 i_cmp_eq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_eq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_EQ_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64x4 i_cmp_eq(float64x4 a, float64x4 b)
{
    return _mm256_cmp_pd(a, b, _CMP_EQ_OQ);
}
#endif

template<unsigned N>
mask_float64<N> i_cmp_eq(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_cmp_eq, a, b);
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


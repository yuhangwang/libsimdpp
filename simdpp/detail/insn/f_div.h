/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_DIV_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_DIV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/f_rcp_e.h>
#include <simdpp/core/f_rcp_rh.h>
#include <simdpp/detail/null/foreach.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float32x4 i_div(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return detail::null::foreach<float32x4>(a, b, [](float a, float b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_ps(a, b);
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b);
    return mul(a, x);
#elif SIMDPP_USE_ALTIVEC
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b); // TODO: check how many approximation steps are needed
    return mul(a, x);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_div(float32x8 a, float32x8 b)
{
    return _mm256_div_ps(a, b);
}
#endif

template<unsigned N>
float32<N> i_div(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_div, a, b);
}

// -----------------------------------------------------------------------------

inline float64x2 i_div(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::foreach<float64x2>(a, b, [](double a, double b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_pd(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline float64x4 i_div(float64x4 a, float64x4 b)
{
    return _mm256_div_pd(a, b);
}
#endif

template<unsigned N>
float64<N> i_div(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_div, a, b);
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


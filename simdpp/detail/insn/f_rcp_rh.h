/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_RCP_RH_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_RCP_RH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/f_sub.h>
#include <simdpp/core/f_mul.h>
#include <simdpp/core/make_float.h>
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    #include <cmath>
    #include <simdpp/detail/null/foreach.h>
    #include <simdpp/detail/null/math.h>
#endif

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float32x4 i_rcp_rh(float32x4 x, float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return detail::null::foreach<float32x4>(x, a, [](float x, float a){ return x*(2.0f - x*a); });
#elif SIMDPP_USE_SSE2
    float32x4 c2, r;
    c2 = make_float(2.0f);

    r = mul(a, x);
    r = sub(c2, r);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 r;
    r = vrecpsq_f32(a, x);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_ALTIVEC
    float32x4 r, c2;
    c2 = make_float(2.0f);
    // -(x*a-c2)
    r = vec_nmsub((__vector float)x, (__vector float)a, (__vector float)c2);
    x = mul(x, r);
    return x;
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_rcp_rh(float32x8 x, float32x8 a)
{
    float32x8 c2, r;
    c2 = make_float(2.0f);

    r = mul(a, x);
    r = sub(c2, r);
    x = mul(x, r);

    return x;
}
#endif

template<unsigned N>
float32<N> i_rcp_rh(float32<N> x, float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_rcp_rh, x, a);
}


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


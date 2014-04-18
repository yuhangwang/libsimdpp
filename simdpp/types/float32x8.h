/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32X8_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int32x8.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX || SIMDPP_DOXYGEN

/// @defgroup simd_vec_fp
/// @{

/// Class representing float32x8 vector
template<>
class float32<8, void> : public any_float32<8, float32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using base_vector_type = float32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX
    using native_type = __m256;
#endif

    float32<8>() = default;
    float32<8>(const float32<8> &) = default;
    float32<8> &operator=(const float32<8> &) = default;

    template<class E> float32<8>(const float32<8,E>& d) { *this = d.eval(); }
    template<class V> explicit float32<8>(const any_vec<32,V>& d)
    {
        *this = bit_cast<float32<8>>(d.vec().eval());
    }
    template<class V> float32<8>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<float32<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    float32<8>(const native_type& d) : d_(d) {}
    float32<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> float32<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float32<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float32<8>& operator[](unsigned) const { return *this; }
          float32<8>& operator[](unsigned)       { return *this; }
    /// @}

    float32<8> eval() const { return *this; }

    /** Creates a float32x4 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32<8> zero() { return detail::make_zero(); }

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 4x 32-bit floating-point
/// vector
template<>
class mask_float32<8, void> : public any_float32<8, mask_float32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX
    using native_type = __m256;
#endif

    mask_float32<8>() = default;
    mask_float32<8>(const mask_float32<8> &) = default;
    mask_float32<8> &operator=(const mask_float32<8> &) = default;

    mask_float32<8>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX
    mask_float32<8>(const float32<8>& d) : d_(d) {}
#endif

    template<class E> explicit mask_float32<8>(const mask_int32<8,E>& d)
    {
        *this = bit_cast<mask_float32<8>>(d.eval());
    }
    template<class E> mask_float32<8>& operator=(const mask_int32<8,E>& d)
    {
        *this = bit_cast<mask_float32<8>>(d.eval()); return *this;
    }

    /// Access the underlying type
    float32<8> unmask() const
    {
    #if SIMDPP_USE_NULL
        return detail::null::unmask_mask<float32<8>>(*this);
    #else
        return float32<8>(d_);
    #endif
    }

    const mask_float32<8>& operator[](unsigned) const { return *this; }
          mask_float32<8>& operator[](unsigned)       { return *this; }

    mask_float32<8> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end defgroup

#endif // SIMDPP_USE_AVX || SIMDPP_DOXYGEN

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

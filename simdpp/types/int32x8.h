/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || SIMDPP_DOXYGEN

/// @ingroup simd_vec_int
/// @{

/** Class representing 8x 32-bit signed integer vector
*/
template<>
class int32<8, void> : public any_int32<8, int32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int32_t;
    using base_vector_type = int32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    int32<8>() = default;
    int32<8>(const int32<8> &) = default;
    int32<8> &operator=(const int32<8> &) = default;

    template<class E> int32<8>(const int32<8,E>& d) { *this = d.eval(); }
    template<class E> int32<8>(const uint32<8,E>& d) { *this = d.eval(); }
    template<class V> explicit int32<8>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int32<8>>(d.vec().eval());
    }
    template<class V> int32<8>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int32<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int32<8>(const native_type& d) : d_(d) {}
    int32<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> int32<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int32<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int32<8>& operator[](unsigned) const { return *this; }
          int32<8>& operator[](unsigned)       { return *this; }
    /// @}

    int32<8> eval() const { return *this; }

    static int32<8> zero() { return detail::make_zero(); }
    static int32<8> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/** Class representing 8x 32-bit unsigned integer vector
*/
template<>
class uint32<8, void> : public any_int32<8, uint32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint32_t;
    using base_vector_type = uint32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    uint32<8>() = default;
    uint32<8>(const uint32<8> &) = default;
    uint32<8> &operator=(const uint32<8> &) = default;

    template<class E> uint32<8>(const uint32<8,E>& d) { *this = d.eval(); }
    template<class E> uint32<8>(const int32<8,E>& d) { *this = d.eval(); }
    template<class V> explicit uint32<8>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint32<8>>(d.vec().eval());
    }
    template<class V> uint32<8>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint32<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint32<8>(const native_type& d) : d_(d) {}
    uint32<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> uint32<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint32<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint32<8>& operator[](unsigned) const { return *this; }
          uint32<8>& operator[](unsigned)       { return *this; }
    /// @}

    uint32<8> eval() const { return *this; }

    static uint32<8> zero() { return detail::make_zero(); }
    static uint32<8> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 4x 32-bit integer
/// vector
template<>
class mask_int32<8, void> : public any_int32<8, mask_int32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    mask_int32<8>() = default;
    mask_int32<8>(const mask_int32<8> &) = default;
    mask_int32<8> &operator=(const mask_int32<8> &) = default;

    mask_int32<8>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    mask_int32<8>(const uint32<8>& d) : d_(d) {}
#endif

    template<class E> explicit mask_int32<8>(const mask_float32<8,E>& d)
    {
        *this = bit_cast<mask_int32<8>>(d.eval());
    }
    template<class E> mask_int32<8>& operator=(const mask_float32<8,E>& d)
    {
        *this = bit_cast<mask_int32<8>>(d.eval()); return *this;
    }

    /// Access the underlying type
    uint32<8> unmask() const
    {
    #if SIMDPP_USE_AVX2
        return uint32<8>(d_);
    #endif
    }

    const mask_int32<8>& operator[](unsigned) const { return *this; }
          mask_int32<8>& operator[](unsigned)       { return *this; }

    mask_int32<8> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || SIMDPP_DOXYGEN

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

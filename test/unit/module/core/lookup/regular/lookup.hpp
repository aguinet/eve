//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lookup.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::lookup return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS((eve::lookup(T() , eve::detail::as_integer_t<T >())), T );
  TTS_EXPR_IS((eve::lookup(v_t(), eve::detail::as_integer_t<v_t>())), (v_t));
}

TTS_CASE_TPL("Check eve::lookup behavior", EVE_TYPE)
{
  using index_t = eve::detail::as_integer_t<T>;

  #if defined(EVE_SIMD_TESTS)
  using v_t = eve::element_type_t<T>;

  T    value{[](auto i, auto)       { return static_cast<v_t>(1+i); } };
  T    reference{[](auto i, auto c) { return static_cast<v_t>(c-i); } };
  index_t indexes{[](auto i, auto c) { return c-i-1; } };

  TTS_EQUAL(eve::lookup(value, indexes) , reference );
  TTS_EQUAL(value[indexes]              , reference );
  #else

  TTS_EQUAL(eve::lookup((T(42)), index_t( 0) ), (T(42)) );
  TTS_EQUAL(eve::lookup((T(42)), index_t(-1) ), (T(0))  );

  #endif
}

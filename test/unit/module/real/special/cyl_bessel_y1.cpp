//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/cyl_bessel_y1.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

EVE_TEST_TYPES( "Check return types of cyl_bessel_y1"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_y1(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_y1(v_t(0)), v_t);
};

EVE_TEST( "Check behavior of cyl_bessel_y1 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 200.0))
        )
  <typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_y1 =  [](auto x) { return eve::cyl_bessel_y1(x); };
  auto std__cyl_bessel_y1 =  [](auto x)->v_t { return boost::math::cyl_neumann(v_t(1), x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::minf(eve::as< T>())), eve::nan(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::inf(eve::as< T>())),  T(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(1500)), std__cyl_bessel_y1(v_t(1500)), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(500)), std__cyl_bessel_y1(v_t(500)), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(10)), std__cyl_bessel_y1(v_t(10))  , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(5)),  std__cyl_bessel_y1(v_t(5))   , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(2)),  std__cyl_bessel_y1(v_t(2))   , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(1.5)),std__cyl_bessel_y1(v_t(1.5)) , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(0.5)),std__cyl_bessel_y1(v_t(0.5)) , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(1)),  std__cyl_bessel_y1(v_t(1))   , 2.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(v_t(0)),  eve::minf(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(1500)), T(std__cyl_bessel_y1(v_t(1500))), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(500)),  T(std__cyl_bessel_y1(v_t(500)) ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(10)) ,  T(std__cyl_bessel_y1( v_t(10)) ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(5))  ,  T(std__cyl_bessel_y1( v_t(5))  ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(2))  ,  T(std__cyl_bessel_y1( v_t(2))  ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(1.5)),  T(std__cyl_bessel_y1( v_t(1.5))), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(0.5)),  T(std__cyl_bessel_y1( v_t(0.5))), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(1))  ,  T(std__cyl_bessel_y1( v_t(1))  ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1( T(0))  , eve::minf(eve::as< T>()), 0.0);


  TTS_ULP_EQUAL(eve__cyl_bessel_y1(a0), map(std__cyl_bessel_y1, a0), 16.0);
};

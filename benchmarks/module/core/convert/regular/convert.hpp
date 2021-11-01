//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/convert.hpp>

#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>())/2;
  auto lmax = eve::valmax(eve::as<EVE_VALUE>())/2;

  {
    using i_t = eve::as_integer_t<EVE_VALUE, signed>;
    auto f    = [](auto x) { return eve::convert(x, eve::as<i_t>()); };
    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin, lmax);

    eve::bench::experiment xp;
    run<EVE_VALUE>(EVE_NAME(convert_unsigned2signed), xp, f, arg0);
  }

  {
    if constexpr( std::is_integral_v<EVE_VALUE> && sizeof(EVE_VALUE) < 8 )
    {
      using i_t = eve::detail::upgrade_t<EVE_VALUE>;
      auto f    = [](auto x) { return eve::convert(x, eve::as<i_t>()); };
      auto arg0 = eve::bench::random_<EVE_VALUE>(lmin, lmax);

      eve::bench::experiment xp;
      run<EVE_VALUE>(EVE_NAME(convert_upgrade), xp, f, arg0);
    }
  }

  {
    if constexpr( std::is_integral_v<EVE_VALUE> && sizeof(EVE_VALUE) > 1 )
    {
      using i_t = eve::detail::downgrade_t<EVE_VALUE>;
      auto f    = [](auto x) { return eve::convert(x, eve::as<i_t>()); };
      auto arg0 = eve::bench::random_<EVE_VALUE>(lmin, lmax);

      eve::bench::experiment xp;
      run<EVE_VALUE>(EVE_NAME(convert_downgrade), xp, f, arg0);
    }
  }
}

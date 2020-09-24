//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_>
                  sub_(EVE_SUPPORTS(neon128_), wide<T, N, neon64_> v0, wide<T, N, neon64_> const &v1) noexcept
  {
    return v0 -= v1;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_>
                  sub_(EVE_SUPPORTS(neon128_), wide<T, N, neon128_> v0, wide<T, N, neon128_> const &v1) noexcept
  {
    return v0 -= v1;
  }
}

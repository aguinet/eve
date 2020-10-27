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

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/properties.hpp>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(log10_, log10);
  namespace detail
  {
    // range_min
    template<typename T> inline constexpr T range_min<tag::log10_(T)> =
      platform::supports_denormals
      ? std::numeric_limits<T>::denorm_min()
        : std::numeric_limits<T>::min();
  }
}

#include <eve/module/math/function/generic/log10.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/math/function/simd/x86/log10.hpp>
#endif

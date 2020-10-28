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

#include <eve/detail/overload.hpp>
#include <eve/platform.hpp>
#include <eve/function/properties.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(min_, min);
  namespace detail
  {
    template<> inline constexpr auto supports_pedantic<tag::min_> = true;
    template<> inline constexpr auto supports_numeric<tag::min_> = true;
  }
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/min.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/min.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/min.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/min.hpp>
#endif

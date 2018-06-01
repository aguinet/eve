//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_XOP_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_XOP_SPEC_HPP_INCLUDED

#if defined(EVE_SUPPORTS_XOP)
  #if defined(_MSC_VER)
    #include <intrin.h>
  #else
    #include <x86intrin.h>
    #include <xopintrin.h>
  #endif
  #include <eve/arch/x86/avx/abi_of.hpp>
  #include <eve/arch/x86/avx/as_register.hpp>
#endif

#endif
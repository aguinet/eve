//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INCREMENT_HPP
#define INCREMENT_HPP

#include <eve/pack.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;
using eve::as_aligned;

// Generator for the base values
auto baseg = [](int i, int) { return i; };
auto nextg = [](int i, int) { return i+1; };

TTS_CASE_TPL( "Check self-increment on pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;

  TTS_SETUP( "A correctly initialized pack" )
  {
    pack<Type,T> simd(baseg), next(nextg), prev(simd), res;

    TTS_SECTION( "supports operator++()" )
    {
      res = simd++;
      TTS_EXPECT( std::equal(simd.begin(),simd.end(),next.begin()));
      TTS_EXPECT( std::equal(res.begin() ,res.end() ,prev.begin()));
    }

    TTS_SECTION( "supports operator++(int)" )
    {
      res = ++simd;
      TTS_EXPECT( std::equal(simd.begin(),simd.end(),next.begin()));
      TTS_EXPECT( std::equal(res.begin() ,res.end() ,next.begin()));
    }
  }
}

#endif
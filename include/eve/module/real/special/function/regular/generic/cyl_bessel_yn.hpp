//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/log.hpp>
#include <eve/function/none.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/real/special/detail/evaluate_rational.hpp>
#include <array>

namespace eve::detail
{

  template <integral_scalar_value N, floating_real_scalar_value T>
  T bessel_yn_small_z(N n, T z, T& scale, const Policy& pol)
  {
    //
    // See http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/02/
    //
    // Note that when called we assume that x < epsilon and n is a positive integer.
    //
    assert(n >= 0);
    assert((z < eps(as(z))));
    auto euler = Ieee_constant<T, 0x3f13c468U, 0x3fe2788cfc6fb619ULL>();

    if(n == 0)
    {
      return (2 * invpi(as(z))) * (eve::log(z*half(as(z))) + euler);
    }
    else if(n == 1)
    {
      return (z* invpi(as(z))) * log(z*half(as(z))) - 2 * invpi(as(z)) * z)
      - (z / (2 * pi(as(z)) * (1 - 2 * euler);
   }
   else if(n == 2)
   {
      return sqr(z/2) / (pi(as(z))) * log(z / 2)
         - (4 / (pi(as(z)) * z * z))
         - ((z * z) / (8 * pi(as(z)))) * (T(3)/2 - 2 * constants::euler<T>());
   }
   else
   {
     T p = pow(z / 2, n);
     T result = -((T(factorial(n - 1)) / pi(as(z))));
   }

  template<integral_scalar_value N, floating_real_scalar_value T>
  EVE_FORCEINLINE T cyl_bessel_yn_(EVE_SUPPORTS(cpu_), N nu, T x) noexcept
  {
    std::cout << "cyl_bessel_yn_ scalarscalar" << std::endl;
    if (x < 0)  return nan(as(x));
    if (x == inf(as(x))) return zero(as(x));
    if (n < 0 ) return cospi(n)*cyl_bessel_yn(-n, x);
    if (x < eve::eps(as(x)))
    {
       T scale = 1;
       auto [value, scale] = bessel_yn_small_z(nu, x);
       value /= scale;
    }
    else     else if (x > T(10000))//asymp
    {
      auto [j, y] = kernel_asymp_jy(T(nu), x);
      return y;
    }
    auto y0 = cyl_bessel_y0(x);
    if (n == 0) return y0;
    auto y1 = cyl_bessel_y1(x);
    if (n == 1) return y1;

    if (x == 0) return minf(as(x));
    // main case
    auto prev = y0;
    auto current = y1;
    int k = 1;
    T init = 2*rec(x);
    T mult = init;
    auto value = fms(mult, current, prev);
    prev = current;
    current = value;
    ++k;
    if((mult > 1) && (eve::abs(current) > 1))
    {
      prev /= current;
      factor /= current;
      value /= current;
      current = 1;
    }
    while(k < nu)
    {
      mult = k*init;
      value = fms(mult, current, prev);
      prev = current;
      current = value;
      ++k;
    }
    if(eve::abs(tools::max_value<T>() * factor) < eve::abs(value))
          return sign(value) * sign(factor);
       value /= factor;
    }
  return value;
  }


  template<floating_real_simd_value T>
  EVE_FORCEINLINE T cyl_bessel_yn_(EVE_SUPPORTS(cpu_), T n, T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return n+x;
//       using v_t =  element_type_t<T>;
//       auto Pi = eve::pi(as(x));
//       T j1opi =  cyl_bessel_j(T(1), x) / Pi;

//       auto evaluate = [j1opi](auto x, auto x1, auto x11, auto x12, auto P, auto Q)
//         {
//           T y = sqr(x);
//           T z = 2 * log(x/x1) * j1opi;
// //        T r = horner( y, P)/ horner( y, Q);
//           T r = evaluate_rational(P, Q, y);
//           T factor = (x + x1) * ((x - x11/256) - x12)/x;
//           return fma(factor, r, z);
//         };

//       auto br_4 = [evaluate](auto x){
//         constexpr std::array<v_t, 7> P1 = {
//           4.0535726612579544093e+13
//           ,  5.4708611716525426053e+12
//           , -3.7595974497819597599e+11
//           ,  7.2144548214502560419e+09
//           , -5.9157479997408395984e+07
//           ,  2.2157953222280260820e+05
//           , -3.1714424660046133456e+02
//         };
//         constexpr std::array<v_t, 7> Q1 = {
//           3.0737873921079286084e+14
//           , 4.1272286200406461981e+12
//           , 2.7800352738690585613e+10
//           , 1.2250435122182963220e+08
//           , 3.8136470753052572164e+05
//           , 8.2079908168393867438e+02
//           , 1.0
//         };
//         constexpr v_t
//         x1  =   2.1971413260310170351e+00,
//         x11 =   5.620e+02,
//         x12 =   1.8288260310170351490e-03;
//         return evaluate(x, x1, x11, x12, P1, Q1);
//       };

//       auto br_8 = [evaluate](auto x){
//         constexpr std::array<v_t, 9>  P2 = {
//             1.1514276357909013326e+19
//           , -5.6808094574724204577e+18
//           , -2.3638408497043134724e+16
//           ,  4.0686275289804744814e+15
//           , -5.9530713129741981618e+13
//           ,  3.7453673962438488783e+11
//           , -1.1957961912070617006e+09
//           ,  1.9153806858264202986e+06
//           , -1.2337180442012953128e+03
//         };
//         constexpr std::array<v_t, 9> Q2 = {
//            5.3321844313316185697e+20
//           , 5.6968198822857178911e+18
//           , 3.0837179548112881950e+16
//           , 1.1187010065856971027e+14
//           , 3.0221766852960403645e+11
//           , 6.3550318087088919566e+08
//           , 1.0453748201934079734e+06
//           , 1.2855164849321609336e+03
//           , 1.0
//         };
//         constexpr v_t
//         x2  =   5.4296810407941351328e+00,
//         x21 =   1.3900e+03,
//         x22 =   -6.4592058648672279948e-06;
//         return evaluate(x, x2, x21, x22, P2, Q2);
//       };

//       auto br_large = [Pi](auto x){
//         constexpr std::array<v_t, 7> PC = {
//           -4.4357578167941278571e+06
//           , -9.9422465050776411957e+06
//           , -6.6033732483649391093e+06
//           , -1.5235293511811373833e+06
//           , -1.0982405543459346727e+05
//           , -1.6116166443246101165e+03
//           , 0.0
//         };
//         constexpr std::array<v_t, 7> QC = {
//           -4.4357578167941278568e+06
//           , -9.9341243899345856590e+06
//           , -6.5853394797230870728e+06
//           , -1.5118095066341608816e+06
//           , -1.0726385991103820119e+05
//           , -1.4550094401904961825e+03
//           , 1.0
//         };
//         constexpr std::array<v_t, 7> PS = {
//           3.3220913409857223519e+04
//           , 8.5145160675335701966e+04
//           , 6.6178836581270835179e+04
//           , 1.8494262873223866797e+04
//           , 1.7063754290207680021e+03
//           , 3.5265133846636032186e+01
//           , 0.0
//         };
//         constexpr std::array<v_t, 7> QS = {
//           7.0871281941028743574e+05
//           , 1.8194580422439972989e+06
//           , 1.4194606696037208929e+06
//           , 4.0029443582266975117e+05
//           , 3.7890229745772202641e+04
//           , 8.6383677696049909675e+02
//           , 1.0
//         };
//         T y = T(8)/x;
//         T y2 = sqr(y);
//         T rc = evaluate_rational(PC, QC, y2);//horner( y2, PC)/ horner( y2, QC);
//         T rs = evaluate_rational(PS, QS, y2);//horner( y2, PS)/ horner( y2, QS);
//         T factor = rsqrt(Pi*x);
//         //
//         // The following code is really just:
//         //
//         // T z = x - 0.75f * Pi
//         // value = factor * (rc * sin(z) + y * rs * cos(z));
//         //
//         // But using the sin/cos addition formulae and constant values for
//         // sin/cos of 3PI/4 which then cancel part of the "factor" term as they're all
//         // 1 / sqrt(2):
//         //
//         auto [sx, cx] = sincos(x);
//         return factor*fms(y, rs * (sx-cx), rc * (sx+cx));
//       };

//       auto r = nan(as(x));
//       auto notdone = is_gez(x);

//       if( eve::any(notdone) )
//       {
//         notdone = next_interval(br_4,  notdone, x <= T(4), r, x);
//         if( eve::any(notdone) )
//         {
//           notdone = next_interval(br_8,  notdone, x <= T(8), r, x);
//           if( eve::any(notdone) )
//           {
//             notdone = last_interval(br_large,  notdone, r, x);
//           }
//         }
//       }
//       r = if_else (is_eqz(x), minf(as(x)), r);
//       r = if_else (x == inf(as(x)), zero, r);
//       return r;
    }
    else return apply_over(cyl_bessel_yn, x);
  }
}

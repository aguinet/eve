#include <eve/function/cyl_bessel_j.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft x  = {0.5, 0.0, 0.1, 1.0, 3.0, 0.5, 21.5, 10.0};
  wide_ft nu = {0.0, 1.0, 2.0, 3.0, 0.5, 1.5,  2.5,  3.5};

  std::cout << "---- simd" << '\n'
            << "<- x                      = " << x << '\n'
            << "<- nu                     = " << nu  << '\n'
            << "-> cyl_bessel_j(nu, x)    = " << eve::cyl_bessel_j(nu, x) << '\n'
            << "-> cyl_bessel_j(nu,-x)    = " << eve::cyl_bessel_j(nu,-x) << '\n'
            << "-> cyl_bessel_j(3, x)     = " << eve::cyl_bessel_j(3, x) << '\n'
            << "-> cyl_bessel_j(nu, 0.1)  = " << eve::cyl_bessel_j(nu, 0.1) << '\n';

  std::cout << "---- scalar" << '\n'
            << "-> cyl_bessel_j(1.0, 3.0) = " << eve::cyl_bessel_j(1.0, 3.0) << '\n';
  return 0;
}

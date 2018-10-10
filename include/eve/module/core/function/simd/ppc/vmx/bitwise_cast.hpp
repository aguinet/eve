//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/function/simd/detail/bitwise_cast.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  template<typename T, typename N, typename U, typename M>
  EVE_FORCEINLINE pack<U,M,ppc_> bitwise_cast_( EVE_SUPPORTS(vmx_)
                                              , pack<T,N,ppc_> const& v0
                                              , as_<pack<U,M,ppc_>> const&
                                              ) noexcept
  {
    using type = pack<U,M,ppc_>;
    return type( (typename type::storage_type)(v0.storage()) );
  }

  // PPC supports logical bitwise casting
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE auto bitwise_cast_( EVE_SUPPORTS(vmx_)
                                    , pack<Source,N,ppc_>               const& v0
                                    , as_<pack<logical<Target>,M,ppc_>> const& tgt
                                    ) noexcept
  {
    return a2l_cast_(v0,tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE auto bitwise_cast_( EVE_SUPPORTS(vmx_)
                                    , pack<logical<Source>,N,ppc_>  const&  v0
                                    , as_<pack<Target,M,ppc_>>      const&  tgt
                                    ) noexcept
  {
    return l2a_cast_(v0,tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE auto bitwise_cast_( EVE_SUPPORTS(vmx_)
                                    , pack<logical<Source>,N,ppc_>      const& v0
                                    , as_<pack<logical<Target>,M,ppc_>> const& tgt
                                    ) noexcept
  {
    return l2l_cast_(v0,tgt);
  }
} }

#endif
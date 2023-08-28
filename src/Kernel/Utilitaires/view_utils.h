/****************************************************************************
* Copyright (c) 2023, CEA
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#ifndef view_utils_included
#define view_utils_included

#include <TRUSTTab.h>

#include <Kokkos_Core.hpp>
#include <Kokkos_DualView.hpp>

template<typename T>
using ViewVect = Kokkos::DualView<T *>;

template<typename T>
using ViewTab = Kokkos::DualView<T **>; // for now 2 axis max with Kokkos

//template<typename T>
//ViewVect<T> build_view_ro(const TRUSTVect<T>& v)
//{
//  using vt_host = typename ViewVect<T>::t_host;
//  using vt_size_t = typename ViewVect<T>::size_type;
//
//  // Highly inefficient!!! Should try to re-use existing allocated space:
//  ViewVect<T> ret(v.le_nom().getString(), v.size());
//
//
//  // See https://kokkos.github.io/kokkos-core-wiki/API/core/view/view.html
//  // and View(pointer_type ptr, const IntType&... indices) (unmanaged data ctor)
//  // for avoiding copy
//
//  vt_host h_view = ret.h_view;
//  for (vt_size_t i = 0; i < h_view.extent(0); i++) {
//      h_view(i) = v[i];
//  }
//
//  return ret;
//}

template<typename T>
ViewTab<T> build_view_ro(const TRUSTTab<T>& v)
{
  using vt_host = typename ViewTab<T>::t_host;
  using vt_size_t = typename ViewTab<T>::size_type;

  assert(v.nb_dim() <= 2);
  // Highly inefficient!!! Should try to re-use existing allocated space:
  ViewTab<T> ret(v.le_nom().getString(), v.dimension_tot(0) , v.dimension_tot(1));

  // See https://kokkos.github.io/kokkos-core-wiki/API/core/view/view.html
  // and View(pointer_type ptr, const IntType&... indices) (unmanaged data ctor)
  // for avoiding copy

  vt_host h_view = ret.h_view;
  for (vt_size_t i = 0; i < h_view.extent(0); i++)
    for (vt_size_t j = 0; j < h_view.extent(1); j++)
      h_view(i,j) = v(i, j);

  return ret;
}



#endif

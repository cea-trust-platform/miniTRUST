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

#ifndef TRUSTTab_compl_TPP_included
#define TRUSTTab_compl_TPP_included

#include <view_utils.h>

// Create internal DualView member, and populate it with current host data
template<typename _TYPE_>
inline void init_view() const
{
  assert(nb_dim() <= 2);

  using vt_host_t = typename ViewTab<T>::t_host;
  using vt_size_t = typename ViewTab<T>::size_type;

  // Allocate dual view with proper size:
  dual_view_ = DualViewTab<_TYPE_>(le_nom(), dimension_tot(0), dimension_tot(1));

  // Highly inefficient!!! Should try to re-use existing allocated space:
  // See https://kokkos.github.io/kokkos-core-wiki/API/core/view/view.html
  // and View(pointer_type ptr, const IntType&... indices) (unmanaged data ctor)
  // for avoiding copy
  vt_host_t h_view = dual_view_.h_view;
  for (vt_size_t i = 0; i < h_view.extent(0); i++)
    for (vt_size_t j = 0; j < h_view.extent(1); j++)
      h_view(i,j) = this(i, j);

  // Mark data modified on host so it will be sync-ed to device later
  dual_view_.modify<host_mirror_space>();
}

template<typename _TYPE_>
inline ViewTab<TYPE_>& TRUSTTab<_TYPE_>::view_ro() const
{
  // Copy to device if needed (i.e. if modify() was called):
  dual_view_.sync<memory_space>();
  return dual_view_.h_view;
}


#endif

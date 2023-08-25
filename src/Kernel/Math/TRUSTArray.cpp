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

#include <TRUSTArray.h>
#include <string.h>

// TRUSTArray kernels for device moved in .cpp file to avoid multiple definition during link
template <typename _TYPE_>
Sortie&  TRUSTArray<_TYPE_>::printOn(Sortie& os) const
{
  this->checkDataOnHost();
  int sz = size_array();
  os << sz << finl;
  if (sz > 0)
    {
      const _TYPE_* v = data_;
      os.put(v,sz,sz);
    }
  return os;
}

template <typename _TYPE_>
Entree&  TRUSTArray<_TYPE_>::readOn(Entree& is)
{
  int sz;
  is >> sz;
  if (sz >= 0)
    {
// Appel a la methode sans precondition sur le type derive (car readOn est virtuelle, les autres proprietes seront initialisees correctement)
      resize_array_(sz);
      if (sz > 0)
        {
          _TYPE_* v = data_;
          is.get(v,sz);
        }
    }
  else
    {
      Cerr << "Error in TRUSTArray:readOn : size = " << sz << finl;
      Process::exit();
    }
  return is;
}

//  Copie les elements source[first_element_source + i] dans les elements  (*this)[first_element_dest + i] pour 0 <= i < nb_elements
//    Les autres elements de (*this) sont inchanges.
// Precondition:
// Parametre:       const ArrOfDouble& m
//  Signification:   le tableau a utiliser, doit etre different de *this !
// Parametre:       int nb_elements
//  Signification:   nombre d'elements a copier, nb_elements >= -1. Si nb_elements==-1, on copie tout le tableau m.
//  Valeurs par defaut: -1
// Parametre:       int first_element_dest
//  Valeurs par defaut: 0
// Parametre:       int first_element_source
//  Valeurs par defaut: 0
// Retour: ArrOfDouble&
//    Signification: *this
// Exception: Sort en erreur si la taille du tableau m est plus grande que la taille de tableau this.
template <typename _TYPE_>
inline TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::inject_array(const TRUSTArray& source, int nb_elements, int first_element_dest, int first_element_source)
{
  assert(&source != this && nb_elements >= -1);
  assert(first_element_dest >= 0 && first_element_source >= 0);

  if (nb_elements < 0) nb_elements = source.size_array();

  assert(first_element_source + nb_elements <= source.size_array());
  assert(first_element_dest + nb_elements <= size_array());

  if (nb_elements > 0)
    {
      _TYPE_ * addr_dest = data_ + first_element_dest;
      bool kernelOnDevice = isKernelOnDevice(*this, source, "TRUSTArray<_TYPE_>::inject_array");
      const _TYPE_ * addr_source = (kernelOnDevice ? mapToDevice(source) : source.addr()) + first_element_source;
      if (kernelOnDevice)
        {
          #pragma omp target teams distribute parallel for if (computeOnDevice)
          for (int i = 0; i < nb_elements; i++)
            addr_dest[i] = addr_source[i];
        }
      else
        {
          // PL: On utilise le memcpy car c'est VRAIMENT plus rapide (10% +vite sur RNR_G20)
          memcpy(addr_dest, addr_source, nb_elements * sizeof(_TYPE_));
        }
    }
  return *this;
}

// Remplit le tableau avec la x en parametre (x est affecte a toutes les cases du tableau)
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator=(_TYPE_ x)
{
  const int n = size_array_;
  _TYPE_ *data = data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this, "TRUSTArray<_TYPE_>::operator=(_TYPE_ x)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for (int i = 0; i < n; i++) data[i] = x;
  return *this;
}

// Addition case a case sur toutes les cases du tableau : la taille de y doit etre au moins egale a la taille de this
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator+=(const TRUSTArray& y)
{
  assert(size_array()==y.size_array());
  _TYPE_* dx = data_;
  const _TYPE_* dy = y.data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this, y, "TRUSTArray<_TYPE_>::operator+=(const TRUSTArray& y)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for (int i = 0; i < size_array(); i++) dx[i] += dy[i];
  return *this;
}

// ajoute la meme valeur a toutes les cases du tableau
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator+=(const _TYPE_ dy)
{
  _TYPE_ * data = data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this, "TRUSTArray<_TYPE_>::operator+=(const _TYPE_ dy)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for(int i = 0; i < size_array(); i++) data[i] += dy;
  return *this;
}

// Soustraction case a case sur toutes les cases du tableau : tableau de meme taille que *this
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator-=(const TRUSTArray& y)
{
  assert(size_array() == y.size_array());
  _TYPE_ * data = data_;
  const _TYPE_ * data_y = y.data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this, y, "TRUSTArray<_TYPE_>::operator-=(const TRUSTArray& y)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for (int i = 0; i < size_array(); i++) data[i] -= data_y[i];
  return *this;
}

// soustrait la meme valeur a toutes les cases
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator-=(const _TYPE_ dy)
{
  _TYPE_ * data = data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this, "TRUSTArray<_TYPE_>::operator-=(const _TYPE_ dy)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for(int i = 0; i < size_array(); i++) data[i] -= dy;
  return *this;
}

// muliplie toutes les cases par dy
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator*= (const _TYPE_ dy)
{
  _TYPE_ * data = data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this, "TRUSTArray<_TYPE_>::operator*= (const _TYPE_ dy)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for(int i=0; i < size_array(); i++) data[i] *= dy;
  return *this;
}

// divise toutes les cases par dy (pas pour TRUSTArray<int>)
template <typename _TYPE_>
TRUSTArray<_TYPE_>& TRUSTArray<_TYPE_>::operator/= (const _TYPE_ dy)
{
  if (std::is_same<_TYPE_,int>::value) throw;
  const _TYPE_ i_dy = 1 / dy;
  _TYPE_ * data = data_;
#ifdef _OPENMP
  bool kernelOnDevice = isKernelOnDevice(*this,"TRUSTArray<_TYPE_>::operator/= (const _TYPE_ dy)");
  #pragma omp target teams distribute parallel for if (kernelOnDevice && Objet_U::computeOnDevice)
#endif
  for(int i=0; i < size_array(); i++) data[i] *= i_dy;
  return *this;
}

// Pour instancier les methodes templates dans un .cpp
template class TRUSTArray<double>;
template class TRUSTArray<int>;
template class TRUSTArray<float>;

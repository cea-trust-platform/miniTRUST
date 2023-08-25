/****************************************************************************
* Copyright (c) 2022, CEA
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

#include <Interface_base.h>

Implemente_base(Interface_base, "Interface_base", Objet_U);
// XD saturation_base objet_u saturation_base -1 Basic class for a liquid-gas interface (used in pb_multiphase)

Sortie& Interface_base::printOn(Sortie& os) const { return os; }

void Interface_base::set_param(Param& param) { param.ajouter("tension_superficielle", &sigma__); }

Entree& Interface_base::readOn(Entree& is)
{
  Param param(que_suis_je());
  set_param(param);
  param.lire_avec_accolades_depuis(is);
  return is;
}

void Interface_base::sigma(const SpanD T, const SpanD P, SpanD res, int ncomp, int ind) const
{
  if (sigma__ >= 0)
    for (int i =0; i < (int)P.size(); i++) res[i * ncomp + ind] = sigma__;
  else sigma_(T,P,res,ncomp,ind);
}

double Interface_base::sigma(const double T, const double P) const
{
  ArrayD Tt = {T}, Pp = {P}, res_ = {0.};
  sigma(SpanD(Tt),SpanD(Pp),SpanD(res_),1,0);
  return res_[0];
}

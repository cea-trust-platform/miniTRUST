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
//////////////////////////////////////////////////////////////////////////////
//
// File:        Eval_Diff_VDF_var_aniso.h
// Directory:   $TRUST_ROOT/src/VDF/Operateurs/Eval_Diff_Dift
// Version:     1
//
//////////////////////////////////////////////////////////////////////////////

#ifndef Eval_Diff_VDF_var_aniso_included
#define Eval_Diff_VDF_var_aniso_included

#include <Champ_Uniforme.h>
#include <Ref_Champ_base.h>
#include <Eval_Diff_VDF.h>
#include <Champ_base.h>
#include <Zone_VDF.h>

// .DESCRIPTION class Eval_Diff_VDF_var_aniso
// Cette classe represente un evaluateur de flux diffusif
// avec un coefficient de diffusivite qui n'est pas constant en espace.
//.SECTION voir aussi Evaluateur_VDF
class Eval_Diff_VDF_var_aniso : public Eval_Diff_VDF
{
public:
  inline void associer(const Champ_base& );
  inline void mettre_a_jour();
  inline const Champ_base& get_diffusivite() const;

  // Methods used by the flux computation in template class:
  inline double nu_1_impl(int i, int compo) const { return dt_diffusivite(i,compo); }
  inline double nu_2_impl(int i, int compo) const { return dt_diffusivite(i,compo); }
  inline double compute_heq_impl(double d0, int i, double d1, int j, int compo) const
  {
    return 1./(d0/dt_diffusivite(i,compo) + d1/dt_diffusivite(j,compo));
  }

  // Methods used in F5 (var face aniso)
  inline double nu_1_impl_face(int i, int j, int compo) const
  {
    return 0.5*(dt_diffusivite(i,compo)+dt_diffusivite(j,compo));
  }

  inline double nu_2_impl_face(int i, int j, int k, int l, int compo) const
  {
    return 0.25*(dt_diffusivite(i,compo)+dt_diffusivite(j,compo)+
                 dt_diffusivite(k,compo)+dt_diffusivite(l,compo));
  }

protected:
  REF(Champ_base) diffusivite_;
  DoubleTab dt_diffusivite;
};

inline void Eval_Diff_VDF_var_aniso::mettre_a_jour()
{
  diffusivite_->valeurs().echange_espace_virtuel();
  dt_diffusivite.ref(diffusivite_->valeurs());
}

inline const Champ_base& Eval_Diff_VDF_var_aniso::get_diffusivite() const
{
  assert(diffusivite_.non_nul());
  return diffusivite_.valeur();
}

// Description:
// associe le champ de diffusivite
inline void Eval_Diff_VDF_var_aniso::associer(const Champ_base& diffu)
{
  // ONLY AVAILABLE FOR TRUST : conduction problem
  // TODO : generalize ME
  if (diffu.le_nom() == "conductivite" && diffu.nb_comp() != Objet_U::dimension)
    {
      Cerr << "Error in Eval_Diff_VDF_var_aniso::associer (anisotropic diffusion VDF operator) !" << finl;
      Cerr << "Ensure that the dimension of the conductivity field is equal to the dimension of the domain !" << finl;
      Cerr << "A general conductivity tensor with non-zero cross-corellation terms is not yet supported (switch to VEF) !" << finl;
      Process::exit();
    }

  diffusivite_ = diffu;
  dt_diffusivite.ref(diffu.valeurs());
}

#endif /* Eval_Diff_VDF_var_aniso_included */

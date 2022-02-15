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
// File:        Op_Diff_VDF_Elem_leaves.h
// Directory:   $TRUST_ROOT/src/VDF/Operateurs/Op_Diff_Dift
// Version:     /main/10
//
//////////////////////////////////////////////////////////////////////////////

#ifndef Op_Diff_VDF_Elem_leaves_included
#define Op_Diff_VDF_Elem_leaves_included

#include <Eval_Diff_VDF_Elem_leaves.h>
#include <Op_Diff_VDF_Elem_base.h>
#include <Op_Diff_Dift_VDF.h>
#include <ItVDFEl.h>

/// \cond DO_NOT_DOCUMENT
class Op_Diff_VDF_Elem_leaves
{ };
/// \endcond

//////////////// CONST /////////////////

declare_It_VDF_Elem(Eval_Diff_VDF_const_Elem)
// .DESCRIPTION class Op_Diff_VDF_Elem
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_Elem : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_Elem>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_Elem);
public:
  Op_Diff_VDF_Elem();
  inline Op_Diff_VDF_Elem(const Iterateur_VDF_base& it) : Op_Diff_VDF_Elem_base(it) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_const_Elem>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_const_Elem>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_const_Elem>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_const_Elem_Axi)
// .DESCRIPTION class Op_Diff_VDF_Elem_Axi
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_Elem_Axi : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_Elem_Axi>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_Elem_Axi);
public:
  Op_Diff_VDF_Elem_Axi();
  inline Op_Diff_VDF_Elem_Axi(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_const_Elem_Axi>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_const_Elem_Axi>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_const_Elem_Axi>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_Multi_inco_const_Elem)
// .DESCRIPTION class Op_Diff_VDF_Multi_inco_Elem
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_Multi_inco_Elem : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_Multi_inco_Elem>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_Multi_inco_Elem);
public:
  Op_Diff_VDF_Multi_inco_Elem();
  inline Op_Diff_VDF_Multi_inco_Elem(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_Multi_inco_const_Elem>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_Multi_inco_const_Elem>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_Multi_inco_const_Elem>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_Multi_inco_const_Elem_Axi)
// .DESCRIPTION class Op_Diff_VDF_Multi_inco_Elem_Axi
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_Multi_inco_Elem_Axi : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_Multi_inco_Elem_Axi>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_Multi_inco_Elem_Axi);
public:
  Op_Diff_VDF_Multi_inco_Elem_Axi();
  inline Op_Diff_VDF_Multi_inco_Elem_Axi(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_Multi_inco_const_Elem_Axi>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_Multi_inco_const_Elem_Axi>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_Multi_inco_const_Elem_Axi>(); }
};

//////////////// VAR /////////////////

declare_It_VDF_Elem(Eval_Diff_VDF_var_Elem)
// .DESCRIPTION class Op_Diff_VDF_var_Elem
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_var_Elem : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_var_Elem>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_var_Elem);
public:
  Op_Diff_VDF_var_Elem();
  inline Op_Diff_VDF_var_Elem(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_var_Elem>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_var_Elem>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_var_Elem>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_var_Elem_Axi)
// .DESCRIPTION class Op_Diff_VDF_var_Elem_Axi
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_var_Elem_Axi : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_var_Elem_Axi>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_var_Elem_Axi);
public:
  Op_Diff_VDF_var_Elem_Axi();
  inline Op_Diff_VDF_var_Elem_Axi(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_var_Elem_Axi>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_var_Elem_Axi>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_var_Elem_Axi>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_var_Elem_aniso)
// .DESCRIPTION class Op_Diff_VDF_var_Elem_aniso
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_var_Elem_aniso : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_var_Elem_aniso>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_var_Elem_aniso);
public:
  Op_Diff_VDF_var_Elem_aniso();
  inline Op_Diff_VDF_var_Elem_aniso(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_var_Elem_aniso>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_var_Elem_aniso>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_var_Elem_aniso>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_Multi_inco_var_Elem)
// .DESCRIPTION class Op_Diff_VDF_Multi_inco_var_Elem
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_Multi_inco_var_Elem : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_Multi_inco_var_Elem>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_Multi_inco_var_Elem);
public:
  Op_Diff_VDF_Multi_inco_var_Elem();
  inline Op_Diff_VDF_Multi_inco_var_Elem(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_Multi_inco_var_Elem>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_Multi_inco_var_Elem>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_Multi_inco_var_Elem>(); }
};

declare_It_VDF_Elem(Eval_Diff_VDF_Multi_inco_var_Elem_Axi)
// .DESCRIPTION class Op_Diff_VDF_Multi_inco_var_Elem_Axi
//  Cette classe represente l'operateur de diffusion associe a une equation de transport.
//  La discretisation est VDF. Le champ diffuse est scalaire. Le champ de diffusivite n'est pas uniforme
//  L'iterateur associe est de type Iterateur_VDF_Elem. L'evaluateur associe est de type Eval_Diff_VDF_var_Elem
class Op_Diff_VDF_Multi_inco_var_Elem_Axi : public Op_Diff_VDF_Elem_base, public Op_Diff_Dift_VDF<Op_Diff_VDF_Multi_inco_var_Elem_Axi>
{
  Declare_instanciable_sans_constructeur(Op_Diff_VDF_Multi_inco_var_Elem_Axi);
public:
  Op_Diff_VDF_Multi_inco_var_Elem_Axi();
  inline Op_Diff_VDF_Multi_inco_var_Elem_Axi(const Iterateur_VDF_base& iterateur) : Op_Diff_VDF_Elem_base(iterateur) { } // pour FT
  inline void associer(const Zone_dis& zd, const Zone_Cl_dis& zcd, const Champ_Inc& ch) { associer_impl<Type_Operateur::Op_DIFF_ELEM,Eval_Diff_VDF_Multi_inco_var_Elem_Axi>(zd,zcd,ch); }
  inline void associer_diffusivite(const Champ_base& ch) { associer_diffusivite_impl<Eval_Diff_VDF_Multi_inco_var_Elem_Axi>(ch); }
  inline const Champ_base& diffusivite() const { return diffusivite_impl<Eval_Diff_VDF_Multi_inco_var_Elem_Axi>(); }
};

#endif /* Op_Diff_VDF_Elem_leaves_included */

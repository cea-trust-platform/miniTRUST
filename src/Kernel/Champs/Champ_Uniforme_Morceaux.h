/****************************************************************************
* Copyright (c) 2015 - 2016, CEA
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
// File:        Champ_Uniforme_Morceaux.h
// Directory:   $TRUST_ROOT/src/Kernel/Champs
// Version:     /main/13
//
//////////////////////////////////////////////////////////////////////////////

#ifndef Champ_Uniforme_Morceaux_included
#define Champ_Uniforme_Morceaux_included




#include <Champ_Don_base.h>
#include <Ref_Domaine.h>
#include <List_Ref_Sous_Zone.h>
class Motcle;

//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//     classe Champ_Uniforme_Morceaux
//     Cette classe represente champ constant par morceaux dans l'espace
//     et constant dans le temps.
// .SECTION voir aussi
//     Champ_Don_base
//////////////////////////////////////////////////////////////////////////////
class Champ_Uniforme_Morceaux : public Champ_Don_base
{

  Declare_instanciable(Champ_Uniforme_Morceaux);

public :
  Champ_base& affecter_(const Champ_base& ch);
  DoubleVect& valeur_a(const DoubleVect& position,
                       DoubleVect& valeurs) const;
  DoubleVect& valeur_a_elem(const DoubleVect& position,
                            DoubleVect& valeurs,
                            int le_poly) const ;
  double valeur_a_elem_compo(const DoubleVect& position,
                             int le_poly,int ncomp) const;

  DoubleTab& valeur_aux(const DoubleTab& positions,
                        DoubleTab& valeurs) const;
  DoubleVect& valeur_aux_compo(const DoubleTab& positions,
                               DoubleVect& valeurs, int ncomp) const;

  DoubleTab& valeur_aux_elems(const DoubleTab& positions,
                              const IntVect& les_polys,
                              DoubleTab& valeurs) const ;
  DoubleVect& valeur_aux_elems_compo(const DoubleTab& positions,
                                     const IntVect& les_polys,
                                     DoubleVect& valeurs,
                                     int ncomp) const;

  const REF(Domaine)& domaine() const;
  REF(Domaine)& domaine();
  const LIST(REF(Sous_Zone))& sous_zones() const;
  LIST(REF(Sous_Zone))& sous_zones();

protected :

  LIST(REF(Sous_Zone)) les_sous_zones;
  REF(Domaine) mon_domaine;


};


#endif


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
// File:        Champ_Fonc_Face.h
// Directory:   $TRUST_ROOT/src/VDF/Champs
// Version:     /main/28
//
//////////////////////////////////////////////////////////////////////////////

#ifndef Champ_Fonc_Face_included
#define Champ_Fonc_Face_included


#include <Champ_Fonc_base.h>
#include <Ref_Zone_VDF.h>
#include <Champ_Face_implementation.h>

//
//.DESCRIPTION  classe Champ_Fonc_Face
//
// .SECTION voir aussi
// Champ_Fonc_base Champ_Face

class Champ_Fonc_Face : public Champ_Fonc_base, public Champ_Face_implementation
{
  Declare_instanciable(Champ_Fonc_Face);

public:

  const Zone_dis_base& zone_dis_base() const;
  void associer_zone_dis_base(const Zone_dis_base&);
  inline const Zone_VDF& zone_vdf() const;
  int fixer_nb_valeurs_nodales(int);
  int imprime(Sortie& os, int ncomp) const;
  virtual void mettre_a_jour(double );
  DoubleTab& trace(const Frontiere_dis_base& , DoubleTab&, double ,int distant) const;
  Champ_base& affecter_(const Champ_base& );
  inline DoubleVect& valeur_a_elem(const DoubleVect& position,
                                   DoubleVect& val,
                                   int le_poly) const;
  inline double valeur_a_elem_compo(const DoubleVect& position,
                                    int le_poly, int ncomp) const;
  inline DoubleTab& valeur_aux_elems(const DoubleTab& positions,
                                     const IntVect& les_polys,
                                     DoubleTab& tab_valeurs) const;
  inline DoubleVect& valeur_aux_elems_compo(const DoubleTab& positions,
                                            const IntVect& les_polys,
                                            DoubleVect& tab_valeurs,
                                            int ncomp) const ;
  inline DoubleTab& valeur_aux_sommets(const Domaine&, DoubleTab&) const;
  inline DoubleVect& valeur_aux_sommets_compo(const Domaine&,
                                              DoubleVect&, int) const;
  inline DoubleTab& remplir_coord_noeuds(DoubleTab& positions) const;
  inline int remplir_coord_noeuds_et_polys(DoubleTab& positions,
                                           IntVect& polys) const;
  DoubleVect& valeur_aux_compo(const DoubleTab& positions,
                               DoubleVect& tab_valeurs, int ncomp) const ;

private :

  REF(Zone_VDF) la_zone_VDF;
  inline virtual const Champ_base& le_champ() const;
  inline virtual Champ_base& le_champ();

};


// Description :
// Renvoie la Zone_VDF
inline const Zone_VDF& Champ_Fonc_Face::zone_vdf() const
{
  return la_zone_VDF.valeur();
}


inline const Champ_base& Champ_Fonc_Face::le_champ() const
{
  return *this;
}

inline Champ_base& Champ_Fonc_Face::le_champ()
{
  return *this;
}

inline DoubleVect& Champ_Fonc_Face::valeur_a_elem(const DoubleVect& position,
                                                  DoubleVect& val,
                                                  int le_poly) const
{
  return Champ_Face_implementation::valeur_a_elem(position, val, le_poly);
}
inline double  Champ_Fonc_Face::valeur_a_elem_compo(const DoubleVect& position,
                                                    int le_poly, int ncomp) const
{
  return Champ_Face_implementation::valeur_a_elem_compo(position, le_poly, ncomp);
}
inline DoubleTab&  Champ_Fonc_Face::valeur_aux_elems(const DoubleTab& positions,
                                                     const IntVect& les_polys,
                                                     DoubleTab& tab_valeurs) const
{
  return Champ_Face_implementation::valeur_aux_elems(positions, les_polys, tab_valeurs);
}
inline DoubleVect&  Champ_Fonc_Face::valeur_aux_elems_compo(const DoubleTab& positions,
                                                            const IntVect& les_polys,
                                                            DoubleVect& tab_valeurs,
                                                            int ncomp) const
{
  return Champ_Face_implementation::valeur_aux_elems_compo(positions, les_polys,
                                                           tab_valeurs, ncomp);
}
inline DoubleTab&  Champ_Fonc_Face::valeur_aux_sommets(const Domaine& dom, DoubleTab& val) const
{
  return Champ_Face_implementation::valeur_aux_sommets(dom, val);
}
inline DoubleVect&  Champ_Fonc_Face::valeur_aux_sommets_compo(const Domaine& dom,
                                                              DoubleVect& val, int comp) const
{
  return Champ_Face_implementation::valeur_aux_sommets_compo(dom, val, comp);
}
inline DoubleTab&  Champ_Fonc_Face::remplir_coord_noeuds(DoubleTab& positions) const
{
  return Champ_Face_implementation::remplir_coord_noeuds(positions);
}
inline int  Champ_Fonc_Face::remplir_coord_noeuds_et_polys(DoubleTab& positions,
                                                           IntVect& polys) const
{
  return Champ_Face_implementation::remplir_coord_noeuds_et_polys(positions,
                                                                  polys);
}
#endif

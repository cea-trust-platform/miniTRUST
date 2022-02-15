/****************************************************************************
* Copyright (c) 2019, CEA
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
// File:        Domaine_dis.h
// Directory:   $TRUST_ROOT/src/Kernel/Framework
// Version:     /main/16
//
//////////////////////////////////////////////////////////////////////////////



#ifndef Domaine_dis_included
#define Domaine_dis_included

#include <Sous_zones_dis.h>
#include <Zones_dis.h>
//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//     classe Domaine_dis
//     Cette classe represente la notion de domaine discretise
//     Elle contient l'ensemble des objets de type Zone_dis
//     qui correspondent a la discretisation des objets
//     de type Zone contenus dans l'objet Domaine associe au
//     domaine discretise.
// .SECTION voir aussi
//     Domaine Zone Zone_dis
//     Dans TRUST V1 il n'y qu'une zone par domaine
//////////////////////////////////////////////////////////////////////////////
Declare_ref(Sous_zones_dis);
Declare_ref(Zones_dis);
class Domaine_dis : public Objet_U
{

  Declare_instanciable_sans_constructeur_ni_destructeur(Domaine_dis);

public:
  Domaine_dis();
  ~Domaine_dis();
  inline int nombre_de_zones() const;
  inline const Zone_dis& zone_dis(int) const;
  inline Zone_dis& zone_dis(int);
  inline int nombre_de_sous_zones_dis() const
  {
    return les_sous_zones_dis->size();
  }
  inline const Sous_zone_dis& sous_zone_dis(int i) const
  {
    return les_sous_zones_dis.valeur()[i];
  }
  inline Sous_zone_dis& sous_zone_dis(int i)
  {
    return les_sous_zones_dis.valeur()[i];
  }
  void associer_domaine(const Domaine&);
  void discretiser(const Nom& );
  inline Domaine& domaine();
  inline const Domaine& domaine() const;

protected:
  REF(Sous_zones_dis) les_sous_zones_dis;
  REF(Zones_dis) les_zones;
  REF(Domaine) le_domaine;

private:
  mutable Nom i_am_allocator_of_les_zones;
};


// Description:
//    Renvoie le nombre de zones contenues dans le domaine.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: int
//    Signification: le nombre de zones contenues dans le domaine
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition: la methode ne modifie pas l'objet
inline int Domaine_dis::nombre_de_zones() const
{
  return les_zones.valeur().size();
}

// Description:
//    Renvoie une reference sur la i-eme zone discretisee du domaine.
//    (version const)
// Precondition:
// Parametre: int i
//    Signification: l'index de la i-eme zone du domaine
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: Zone_dis&
//    Signification: la i-eme zone discretisee du domaine
//    Contraintes: reference constante
// Exception:
// Effets de bord:
// Postcondition: la methode ne modifie pas l'objet
inline const Zone_dis& Domaine_dis::zone_dis(int i) const
{
  return les_zones.valeur()[i];
}

// Description:
//    Renvoie une reference sur la i-eme zone discretisee du domaine.
// Precondition:
// Parametre: int i
//    Signification: l'index de la i-eme zone du domaine
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: Zone_dis&
//    Signification: la i-eme zone discretisee du domaine
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline Zone_dis& Domaine_dis::zone_dis(int i)
{
  return les_zones.valeur()[i];
}

// Description:
//    Renvoie une reference sur le Domaine associe au domaine
//    discretise.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: Domaine&
//    Signification: le Domaine associe au domaine discretise
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline Domaine& Domaine_dis::domaine()
{
  return le_domaine.valeur();
}

// Description:
//    Renvoie une reference sur le Domaine associe au domaine
//    discretise.
//    (version const)
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: Domaine&
//    Signification: le Domaine associe au domaine discretise
//    Contraintes: reference constante
// Exception:
// Effets de bord:
// Postcondition: la methode ne modifie pas l'objet
inline const Domaine& Domaine_dis::domaine() const
{
  return le_domaine.valeur();
}
#endif

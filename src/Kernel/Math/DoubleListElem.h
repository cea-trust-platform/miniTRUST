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
// File:        DoubleListElem.h
// Directory:   $TRUST_ROOT/src/Kernel/Math
// Version:     /main/10
//
//////////////////////////////////////////////////////////////////////////////
//
// WARNING: DO NOT EDIT THIS FILE! Only edit the template file DoubleListElem.h.P
//
//
#ifndef DoubleListElem_included
#define DoubleListElem_included

#include <Double.h>
#include <arch.h>
class Sortie;
class Entree;

//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//      Classe qui sert a representer une liste de reels double
//      precision. On ne peut pas utiliser la classe container
//      List avec des objets du type double car double est un type
//      predefini du C++ qui ne possede pas les fonctions exigees
//      par List< >.
// .SECTION voir aussi
//////////////////////////////////////////////////////////////////////////////

class DoubleList;
class DoubleListElem
{

public :
  friend class DoubleList;
  inline DoubleListElem();
  inline DoubleListElem(const double x);
  DoubleListElem(const DoubleListElem&);
  ~DoubleListElem();
  inline DoubleListElem& suivant();
  inline const DoubleListElem& suivant() const;
  inline int est_vide() const;
  inline int est_dernier() const;
  inline double& valeur();
  inline double valeur() const;
  DoubleListElem& add(double ) ;
  friend int operator == (const DoubleListElem& , const DoubleListElem& );

protected:

  double data;
  DoubleListElem* suivant_;
};

// Description:
//     Construit une liste vide.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour:
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline DoubleListElem::DoubleListElem()
{
  suivant_=this;
}

// Description:
//     Construit le singleton (x).
// Precondition:
// Parametre: const double x
//    Signification: element de la liste
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour:
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline DoubleListElem::DoubleListElem(const double x) : data(x), suivant_(0)
{}

// Description:
//     renvoie 1 si la liste est vide
//     renvoie 0 sinon.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: int
//    Signification: 1 si la liste est vide, 0 sinon
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline int DoubleListElem::est_vide() const
{
  return suivant_==this;
}


// Description:
//     renvoie 1 si il n'y a pas de suivant
//     renvoie 0 sinon.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: int
//    Signification: 1 si il n'y a pas de suivant, 0 sinon
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline int DoubleListElem::est_dernier() const
{
  return ((est_vide()) || (suivant_==0) );
}


// Description:
//     renvoie le reel double precision.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: double&
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline double& DoubleListElem::valeur()
{
  return data;
}


// Description:
//     renvoie le reel double precision.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: double&
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline double DoubleListElem::valeur() const
{
  return data;
}


// Description:
//     renvoie le suivant.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: const DoubleList&
//    Signification: liste sur l'element suivant
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline const DoubleListElem& DoubleListElem::suivant() const
{
  return *suivant_;
}


// Description:
//     renvoie le suivant.
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: DoubleList&
//    Signification: liste sur l'element suivant
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline DoubleListElem& DoubleListElem::suivant()
{
  return *suivant_;
}

#endif // DoubleList_H


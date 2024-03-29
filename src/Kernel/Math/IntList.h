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
// File:        IntList.h
// Directory:   $TRUST_ROOT/src/Kernel/Math
// Version:     /main/10
//
//////////////////////////////////////////////////////////////////////////////
//
// WARNING: DO NOT EDIT THIS FILE! Only edit the template file IntList.h.P
//
//
#ifndef IntList_included
#define IntList_included

#define IMAX 1000000000
#include <arch.h>
class Sortie;
class Entree;
#include <IntListElem.h>

//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//      Classe qui sert a representer une liste de reels int
//      precision. On ne peut pas utiliser la classe container
//      List avec des objets du type int car int est un type
//      predefini du C++ qui ne possede pas les fonctions exigees
//      par List< >.
// .SECTION voir aussi
//////////////////////////////////////////////////////////////////////////////
class IntList : public IntListElem
{

public :
  friend class IntList_Curseur;

  IntList(const IntList&);
  inline IntList();
  Sortie& printOn(Sortie& os) const;
  Entree& readOn(Entree& is);
  int size() const;
  int contient(int) const;
  int rang(int) const;
  IntListElem& dernier() ;
  const IntListElem& dernier() const;

  int& operator[](int );
  const int& operator[](int ) const;
  IntList& add(int ) ;
  IntList& add_if_not(int ) ;
  IntList& operator=(const IntList& );

  friend int operator == (const IntList& , const IntList& );
  void suppr(int );
  void vide();
  void calcule_min_max();

private:
  IntListElem* dernier_;
  int min_data;
  int max_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//      List_Curseur de reels int precision
// .SECTION voir aussi
//////////////////////////////////////////////////////////////////////////////
class IntList_Curseur
{
public :
  inline IntList_Curseur(const IntList& a_list);
  inline IntList_Curseur(const IntListElem& a_list);
  inline operator bool() const;
  inline void operator++();
  inline int valeur() const;
  inline int& valeur();
  inline void operator=(const IntList& a_list);
  inline const IntListElem& list() const;
  inline IntListElem& list();

private :
  IntListElem* curseur;
};

// Description:
//    Construit une liste vide
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

inline IntList::IntList() :
  IntListElem(),min_data(IMAX),max_data(-IMAX)
{
  dernier_=this;
}

// Description:
//    Constructeur
//    Construit une liste_curseur a partir d'une liste
// Precondition:
// Parametre: const IntList& list
//    Signification: la liste a utiliser
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour:
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline IntList_Curseur::IntList_Curseur(const IntList& a_list)
  : curseur(&(IntListElem&)a_list)
{
  if (a_list.est_vide())
    curseur=0;
}

// Description:
//    Constructeur
//    Construit une liste_curseur a partir d'une liste
// Precondition:
// Parametre: const IntList& list
//    Signification: la liste a utiliser
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour:
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline IntList_Curseur::IntList_Curseur(const IntListElem& a_list)
  : curseur(&(IntListElem&)a_list)
{
  if (a_list.est_vide())
    curseur=0;
}

// Description:
//    Teste si le curseur est non nul
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: int
//    Signification: 1 si le curseur est non nul, 0 si il est nul
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:

inline IntList_Curseur::operator bool() const
{
  return (curseur!=0);
}


// Description:
//    Avance le curseur dans la liste
//    Si le curseur est sur le dernier element, il devient nul
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
inline void IntList_Curseur::operator++()
{
  if(curseur->est_dernier())
    curseur=0;
  else
    curseur=&(curseur->suivant());
}


// Description:
//    retourne la valeur du curseur
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: int
//    Signification: valeur du curseur
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline int IntList_Curseur::valeur() const
{
  return curseur->valeur();
}


// Description:
//    retourne la valeur du curseur
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: int&
//    Signification: valeur du curseur
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline int& IntList_Curseur::valeur()
{
  return curseur->valeur();
}


// Description:
//    Affectation d'une liste a une liste_curseur
// Precondition:
// Parametre: const IntList& list
//    Signification: la liste a affecter
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour:
//    Signification:
//    Contraintes:
// Exception:
// Effets de bord:
//    Mise a jour du curseur sur le premier element
// Postcondition:
inline void IntList_Curseur::operator=(const IntList& a_list)
{
  curseur=(&(IntListElem&)a_list);
  if (a_list.est_vide())
    curseur=0;
}


// Description:
//    Retourne la liste associee a la liste_curseur
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: const IntList&
//    Signification: la liste associee
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline const IntListElem& IntList_Curseur::list() const
{
  return *curseur;
}


// Description:
//    Retourne la liste associee a la liste_curseur
// Precondition:
// Parametre:
//    Signification:
//    Valeurs par defaut:
//    Contraintes:
//    Acces:
// Retour: IntList&
//    Signification: la liste associee
//    Contraintes:
// Exception:
// Effets de bord:
// Postcondition:
inline IntListElem& IntList_Curseur::list()
{
  return *curseur;
}

#endif // IntList_H


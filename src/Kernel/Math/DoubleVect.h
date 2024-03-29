/****************************************************************************
* Copyright (c) 2021, CEA
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
// File:        DoubleVect.h
// Directory:   $TRUST_ROOT/src/Kernel/Math
// Version:     /main/10
//
//////////////////////////////////////////////////////////////////////////////
//
// WARNING: DO NOT EDIT THIS FILE! Only edit the template file DoubleVect.h.P
//
//

#ifndef DoubleVect_included
#define DoubleVect_included

#include <ArrOfDouble.h>
#include <MD_Vector.h>

// A nettoyer: les includes suivants ne sont pas necessaires a ce fichier
//  mais a d'autres qui ne font pas les include
#include <Vect.h>
#include <IntVect.h>

class DoubleVect : public ArrOfDouble
{
  Declare_instanciable_sans_constructeur_ni_destructeur(DoubleVect);
public:
  DoubleVect() : size_reelle_(0), line_size_(1) {};
  DoubleVect(int n);
//  DoubleVect(int n, double x);
  DoubleVect(const DoubleVect&);
  // Pas de constructeur par copie de ArrOfDouble, voir DoubleVect(const DoubleVect&)
  ~DoubleVect() {};
  virtual void reset();
  virtual void detach_vect();

  DoubleVect& operator=(const DoubleVect&);
  DoubleVect& operator=(double);

  virtual void ref(const DoubleVect&);
  virtual void ref_data(double* ptr, int new_size);
  virtual void ref_array(ArrOfDouble&, int start = 0, int sz = -1);

  inline void resize(int, Array_base::Resize_Options opt = COPY_INIT);
  virtual void resize_tab(int n, Array_base::Resize_Options opt = COPY_INIT);
  void copy(const ArrOfDouble&, Array_base::Resize_Options opt = COPY_INIT);
  void copy(const DoubleVect&, Array_base::Resize_Options opt = COPY_INIT);

  // par defaut: min et max sur items reels (compat. 1.5.6):
  double local_max_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double local_min_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double local_max_abs_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double local_min_abs_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double mp_max_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double mp_min_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double mp_max_abs_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double mp_min_abs_vect(Mp_vect_options opt = VECT_REAL_ITEMS) const;
  double mp_norme_vect() const;

  void operator+=(const DoubleVect&);
  void operator+=(const double);
  void operator-=(const DoubleVect&);
  void operator-=(const double);
  void operator*=(const DoubleVect&);
  void operator*= (const double);
  void operator/=(const DoubleVect&);
  void operator/= (const double);

  // Options par defaut choisies pour compatibilite avec la version precedente
  // Attention: il y avait un echange_espace_virtuel avant, ce n'est pas strictement equivalent
  void abs(Mp_vect_options opt = VECT_ALL_ITEMS);
  void   carre(Mp_vect_options opt = VECT_ALL_ITEMS);
  void   racine_carree(Mp_vect_options opt = VECT_ALL_ITEMS);
  void ajoute(double alpha, const DoubleVect& y, Mp_vect_options opt = VECT_ALL_ITEMS); // x+=alpha*y
  void ajoute_sans_ech_esp_virt(double alpha, const DoubleVect& y, Mp_vect_options opt = VECT_REAL_ITEMS); // x+=alpha*y sans echange_espace_virtuel
  void ajoute_produit_scalaire(double alpha, const DoubleVect&, const DoubleVect&, Mp_vect_options opt = VECT_ALL_ITEMS); // z+=alpha*x*y;
  void ajoute_carre(double alpha, const DoubleVect& y, Mp_vect_options opt = VECT_ALL_ITEMS);

  inline int size() const;
  inline int size_totale() const;
  inline int size_reelle() const;
  inline int size_reelle_ok() const;
  inline int line_size() const;

  virtual void echange_espace_virtuel();

  virtual const MD_Vector& get_md_vector() const { return md_vector_; }
  virtual void              set_md_vector(const MD_Vector&);
  virtual void jump(Entree&);
  virtual void lit(Entree&, int resize_and_read=1);
  virtual void ecrit(Sortie&) const;

protected:
  inline void set_line_size_(int n);
  inline void resize_vect_(int n, Array_base::Resize_Options opt = COPY_INIT);
  void copy_(const DoubleVect& v, Array_base::Resize_Options opt = COPY_INIT);
  void attach_vect(const DoubleVect& v, int start, int size = -1);
  //void detach_vect(); // Not used in protected mode => Need in public mode => So method moved
private:
  // Un DoubleVect est un ArrOfDouble qui possede eventuellement une structure de tableau
  // distribue. Ce pointeur peut etre nul.
  MD_Vector md_vector_;
  // Propriete size_reelle du tableau (fournie par scattered_vect_data)
  // -1 => l'appel a size_reelle() et size() est invalide pour ce vecteur.
  int size_reelle_;
  // Facteur multiplicatif a appliquer entre md_vector_.nb_items_tot() et size_array()
  //  et entre md_vector_.nb_items_reels() et size_reelle_.
  // Si l'objet est un tableau, ce facteur est generalement egal au produit
  //  des dimension(i) pour i>1 (une ligne du tableau par item geometrique du descripteur)
  // Attention, line_size_ peut etre nul pour un tableau a zero colonnes mais pas s'il y a un descripteur
  //  attache.
  int line_size_;
};

// Description: Taille de l'espace "reel" du vecteur.
//  (si md_vector_ est nul, cette valeur est identique a size_array(),
//   sinon, soit elle est egale a md_vector_....get_nb_items(),
//          soit l'appel est invalide (en particulier si les items reels ne
//           sont pas regroupes en debut de tableau)
//  On peut interroger le vecteur pour savoir si size_reelle() est valide avec size_reelle_ok()
inline int DoubleVect::size_reelle() const
{
  // Si cet assert plante, c'est que l'appel a ete declare invalide par le
  //  MD_Vect associe a ce vecteur.
  assert(size_reelle_ >= 0);
  // Si cet assert plante, c'est que le tableau a ete redimensionne avec resize_array() au lieu de resize().
  // (invalide pour un Vect ou un Tab).
  assert(size_array() == size_reelle_ || md_vector_.non_nul());
  return size_reelle_;
}

// Description renvoie 1 si l'appel a size() et size_reelle() est valide, 0 sinon
inline int DoubleVect::size_reelle_ok() const
{
  return size_reelle_ >= 0;
}

// Description: Identique a size_reelle()
inline int DoubleVect::size() const
{
  return size_reelle();
}

// Description: Identique a size_array()
inline int DoubleVect::size_totale() const
{
  return size_array();
}

inline int DoubleVect::line_size() const
{
  // Si line_size_ est nulle, size_array doit etre nul aussi
  assert(line_size_ > 0 || size_array() == 0);
  return line_size_;
}

// Description: change l'attribut line_size_ du tableau avec n >= 1
//  n == 0 est autorise uniquement si size_array_ == 0
// Precondition: le md_vector_ doit etre nul (il faut attribuer md_vector_
//  apres la line_size_ car lorsqu'on attribue md_vector_ on teste
//  la validite des tailles de tableaux en fonction de line_size_)
//  ou la line_size_ ne doit pas changer (cas d'un resize qui ne change rien)
inline void DoubleVect::set_line_size_(int n)
{
  assert(!md_vector_.non_nul() || line_size_ == n);
  assert(n >= 0);
  line_size_ = n;
}

// Description: Change la taille du vecteur (identique a resize_array()
//  pour le traitement des anciennes valeurs et de nouvelles cases).
//  Attention: Cette methode n'est pas virtuelle, et afin d'eviter d'amener
//  un DoubleTab dans un etat invalide, l'appel est interdit si l'objet
//  est de ce type. Dans ce cas, voir resize_tab.
// Precondition: l'appel est interdit si le vecteur a une structure parallele.
//  Le vecteur doit etre "resizable" (voir preconditions de ArrOfDouble::resize_array()).
//  Appel interdit si l'objet n'est pas un DoubleVect (sinon mauvaise initialisation
//  des dimensions du tableau)
inline void DoubleVect::resize(int n, Array_base::Resize_Options opt)
{
  // Verifie que l'objet est bien du type DoubleVect
  assert(n == size_array() || get_info() == DoubleVect::info());
  resize_vect_(n, opt);
}

// Description: Methode interne de resize (appellee par DoubleTab::resize(...))
//  sans precondition sur le type de l'objet.
// Precondition: l'appel est interdit si le vecteur a une structure parallele.
//  Le vecteur doit etre "resizable" (voir preconditions de ArrOfDouble::resize_array()).
//  n doit etre un multiple de line_size_
inline void DoubleVect::resize_vect_(int n, Array_base::Resize_Options opt)
{
  // Note B.M.: j'aurais voulu interdire completement resize des qu'on a un descripteur
  //  mais il y en a partout dans le code (on resize les tableaux alors qu'ils ont deja
  //  la bonne taille). Donc j'autorise si la taille ne change pas.
  //assert(!md_vector_.non_nul() || n == size_array());
  // PL: 1.7.0 is now strict about this point:
  if (md_vector_.non_nul())
    {
      Cerr << "Resize of a distributed array is forbidden!" << finl;
      exit();
    }
  assert(n == 0 || (n > 0 && line_size_ > 0 && n % line_size_ == 0));
  resize_array_(n, opt);
  size_reelle_ = n;
  // ne pas mettre line_size_ a 1 ici, voir DoubleTab::resize_dim0()
}

// Fonctions non membres de la classe DoubleVect

//int operator<(const DoubleVect&, const DoubleVect&);
//int operator>(const DoubleVect& x, const DoubleVect& y);
//int operator<=(const DoubleVect& x, const DoubleVect& y);
//int operator>=(const DoubleVect& x, const DoubleVect& y);

int operator==(const DoubleVect& x, const DoubleVect& y);
int operator!=(const DoubleVect& x, const DoubleVect& y);

// Arithmetique :
//DoubleVect operator+(const DoubleVect&, const double);
//DoubleVect operator-(const DoubleVect&, const double);
//DoubleVect operator-(const DoubleVect&);

//void ordonne(DoubleVect&);

//indice du min :
//int imin(const DoubleVect&) ;

//indice du max
//int imax(const DoubleVect&) ;

//valeur min
//double min(const DoubleVect&) ;

//valeur max
//double max(const DoubleVect&) ;

//produit scalaire :
//double operator*(const DoubleVect&, const DoubleVect&);
//DoubleVect operator * (const DoubleVect&, double);
//DoubleVect operator / (const DoubleVect&, double);
//DoubleVect operator * (double, const DoubleVect&);

int local_imax_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double local_max_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
int local_imin_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double local_min_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double mp_max_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double mp_min_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
//double mp_somme_vect_local(const DoubleVect&);
double mp_somme_vect(const DoubleVect&);
double local_max_abs_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double local_min_abs_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double mp_max_abs_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);
double mp_min_abs_vect(const DoubleVect&, Mp_vect_options opt = VECT_REAL_ITEMS);

// Valeurs par defaut choisies pour compatibilite approximative avec V1.5.6
// (compatibilite exacte non voulue car necessite echange_espace_virtuel)
void operator_add(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_add(DoubleVect& resu, const double x, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_sub(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_sub(DoubleVect& resu, const double x, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_multiply(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_multiply(DoubleVect& resu, const double x, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_negate(DoubleVect& resu, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_egal(DoubleVect& resu, double x, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_egal(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);

double local_prodscal(const DoubleVect&, const DoubleVect& );
double mp_prodscal(const DoubleVect&, const DoubleVect& );
double mp_norme_vect(const DoubleVect&);
double mp_carre_norme_vect(const DoubleVect&);
double local_carre_norme_vect(const DoubleVect& vx);
double mp_moyenne_vect(const DoubleVect&);
void ajoute_alpha_v(DoubleVect& v, double alpha, const DoubleVect& vx, Mp_vect_options opt = VECT_REAL_ITEMS);
void ajoute_carre(DoubleVect& v, double alpha, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void ajoute_produit_scalaire(DoubleVect& v, double alpha, const DoubleVect& vx, const DoubleVect& vy, Mp_vect_options opt = VECT_ALL_ITEMS);
void racine_carree(DoubleVect& v, Mp_vect_options opt = VECT_ALL_ITEMS);
void carre(DoubleVect& v, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_inverse(DoubleVect& resu, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_abs(DoubleVect& resu, Mp_vect_options opt = VECT_ALL_ITEMS);
void tab_multiply_any_shape(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void tab_divide_any_shape(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_divide(DoubleVect& resu, const DoubleVect& vx, Mp_vect_options opt = VECT_ALL_ITEMS);
void operator_divide(DoubleVect& resu, const double x, Mp_vect_options opt = VECT_ALL_ITEMS);

#endif


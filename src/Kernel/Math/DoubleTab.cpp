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
// File:        DoubleTab.cpp
// Directory:   $TRUST_ROOT/src/Kernel/Math
// Version:     /main/10
//
//////////////////////////////////////////////////////////////////////////////
//
// WARNING: DO NOT EDIT THIS FILE! Only edit the template file DoubleTab.cpp.P
//
//
#include <DoubleTab.h>
#include <math.h>
#include <MD_Vector_base.h>
#include <Ref_DoubleTab.h>
#include <DoubleTabs.h>
#include <communications.h>

Implemente_instanciable_sans_constructeur(DoubleTab, "DoubleTab",DoubleVect);
Implemente_ref(DoubleTab);
Implemente_vect(DoubleTab);

// Verifie la coherence entre size_array(), line_size() et les dimensions du tableau
#if MAXDIM_TAB != 4
#error Mettre a jour le code pour MAXDIM_TAB pour CHECK_LINE_SIZE
#endif
#define CHECK_LINE_SIZE                                                        \
  ((line_size() == ((nb_dim_>1)?dimensions_[1]:1)*((nb_dim_>2)?dimensions_[2]:1)*((nb_dim_>3)?dimensions_[3]:1)) \
   && (line_size() * dimension_tot_0_ == size_array()))

// Description: ecriture d'un tableau sequentiel
//  (idem que DoubleVect::printOn() on ne sait pas quoi faire de pertinent
//   pour un tableau distribue).
Sortie& DoubleTab::printOn(Sortie& os) const
{
  assert(CHECK_LINE_SIZE);
  if (nproc() > 1 && get_md_vector().non_nul())
    {
      Cerr << "Error in DoubleTab::printOn: try to print a parallel vector" << finl;
      exit();
    }
  os << nb_dim_ << finl;
  assert(dimensions_[0] == dimension_tot_0_);
  if (nb_dim_ > 0)
    os.put(dimensions_, nb_dim_, nb_dim_);

  const int sz = size_array();
  os << sz << finl;
  const int l_size = line_size();
  const double *data = addr();
  if (sz > 0)
    os.put(data, sz, l_size);
  return os;
}

// Description: lecture d'un tableau sequentiel
// Precondition: le md_vector_ doit etre nul.
Entree& DoubleTab::readOn(Entree& is)
{
  if (get_md_vector().non_nul())
    {
      // Que veut-on faire si on lit dans un vecteur ayant deja une structure parallele ?
      Cerr << "Error in DoubleTab::readOn: vector has a parallel structure" << finl;
      exit();
    }

  is >> nb_dim_;
  if (nb_dim_ < 1 || nb_dim_ > MAXDIM_TAB)
    {
      Cerr << "Error in DoubleTab::readOn: wrong nb_dim_ = " << nb_dim_ << finl;
      exit();
    }
  is.get(dimensions_, nb_dim_);
  if (dimensions_[0] < 0)
    {
      Cerr << "Error in DoubleTab::readOn: wrong dimension(0) = " << dimensions_[0] << finl;
      exit();
    }
  int l_size = 1;
  for (int i = 1; i < nb_dim_; i++)
    {
      if (dimensions_[i] < 0)
        {
          Cerr << "Error in DoubleTab::readOn: wrong dimension(" << i << ") = " << dimensions_[i] << finl;
          exit();
        }
      l_size *= dimensions_[i];
    }
  dimension_tot_0_ = dimensions_[0];
  DoubleVect::readOn(is);
  set_line_size_(l_size);
  if (dimension_tot_0_ * l_size != size_array())
    {
      Cerr << "Error in DoubleTab::readOn: wrong size_array " << size_array()
           << ", expected " << dimension_tot_0_ * l_size << finl;
      exit();
    }
  assert(CHECK_LINE_SIZE);
  return is;
}

static inline void init_dimensions(int * tab)
{
#ifndef NDEBUG
  for (int i = 0; i < MAXDIM_TAB; i++)
    tab[i] = -1;
#endif
}

DoubleTab::DoubleTab() :
  nb_dim_(1), dimension_tot_0_(0)
{
  init_dimensions(dimensions_);
  dimensions_[0] = 0;
}

DoubleTab::DoubleTab(const DoubleTab& dbt) :
  DoubleVect(dbt),
  nb_dim_(dbt.nb_dim_),
  dimension_tot_0_(dbt.dimension_tot_0_)
{
  for (int i = 0; i < MAXDIM_TAB; i++)
    dimensions_[i] = dbt.dimensions_[i];
}
#define PARAM_X
#define PARAM_X2

DoubleTab::DoubleTab(int n PARAM_X)
  : DoubleVect(n PARAM_X2),
    nb_dim_(1),
    dimension_tot_0_(n)
{
  init_dimensions(dimensions_);
  dimensions_[0] = n;
}

DoubleTab::DoubleTab(int n1, int n2 PARAM_X)
  : DoubleVect(n1*n2 PARAM_X2),
    nb_dim_(2),
    dimension_tot_0_(n1)
{
  assert(n1 >= 0 && n2 >= 0);
  init_dimensions(dimensions_);
  dimensions_[0]=n1;
  dimensions_[1]=n2;
  set_line_size_(n2);
}
#ifdef INT_is_64_
DoubleTab::DoubleTab(int n1, True_int n2 PARAM_X)
  : DoubleVect(n1*n2 PARAM_X2),
    nb_dim_(2),
    dimension_tot_0_(n1)
{
  assert(n1 >= 0 && n2 >= 0);
  init_dimensions(dimensions_);
  dimensions_[0]=n1;
  dimensions_[1]=n2;
  set_line_size_(n2);
}
#endif

DoubleTab::DoubleTab(int n1, int n2, int n3 PARAM_X)
  : DoubleVect(n1*n2*n3 PARAM_X2),
    nb_dim_(3),
    dimension_tot_0_(n1)
{
  assert(n1 >= 0 && n2 >= 0 && n3 >= 0);
  init_dimensions(dimensions_);
  dimensions_[0]=n1;
  dimensions_[1]=n2;
  dimensions_[2]=n3;
  set_line_size_(n2*n3);
}

DoubleTab::DoubleTab(int n1, int n2, int n3, int n4 PARAM_X)
  : DoubleVect(n1*n2*n3*n4 PARAM_X2),
    nb_dim_(4),
    dimension_tot_0_(n1)
{
  assert(n1 >= 0 && n2 >= 0 && n3 >= 0 && n4 >= 0);
  init_dimensions(dimensions_);
  dimensions_[0]=n1;
  dimensions_[1]=n2;
  dimensions_[2]=n3;
  dimensions_[3]=n4;
  set_line_size_(n2*n3*n4);
}

// Description: fait pointer le tableau sur le vecteur v et en associant
//  la meme structure parallele.
//  Attention, si line_size du vecteur v est different de 1,
//  on cree un tableau bidimensionnel (on peut avoir un vecteur
//  de ce type si on copie un Tab dans un Vect puis on prend
//  une ref sur ce Vect).
// Precondition: le vecteur v doit vraiment etre de type Vect !
//   (sinon utiliser DoubleTab::ref(const DoubleTab &)
void DoubleTab::ref(const DoubleVect& v)
{
  assert(v.get_info() == DoubleVect::info());
  DoubleVect::ref(v);
  const int l = v.line_size();
  // Attention:
  //  En prenant la ref, on est oblige de conserver l'attribut line_size
  //  du Vect (sinon echange_espace_virtuel ne fonctionnera pas car
  //  on n'aura pas le bon facteur multiplicatif des items geometriques)
  //  Si on voulait creer un tableau monodimensionnel avec line_size > 1,
  //  le tableau devient invalide car on n'a plus line_size = produit des
  //  dimensions > 1.
  //  On peut le faire a condition de laisser tomber le md_vector_ en
  //  faisant  tab.ref_array(v) au lieu de  tab.ref(v)
  if (l == 1)
    {
      nb_dim_ = 1;
    }
  else
    {
      nb_dim_ = 2;
      dimensions_[1] = l;
    }
  if (v.size_reelle_ok())
    {
      int sz = v.size_reelle();
      dimensions_[0] = sz / l;
    }
  else
    {
      dimensions_[0] = -1;
    }
  dimension_tot_0_ = size_array() / l;
  assert(CHECK_LINE_SIZE);
}

// Description: fait pointer le tableau sur le tableau t
//  en recuperant la structure parallele. Attention,
//  on fige le tableau qui ne pourra plus etre resize
void DoubleTab::ref(const DoubleTab& src)
{
  DoubleVect::ref(src);
  nb_dim_ = src.nb_dim_;
  for (int i = 0; i < MAXDIM_TAB; i++)
    dimensions_[i] = src.dimensions_[i];
  dimension_tot_0_ = src.dimension_tot_0_;
  assert(CHECK_LINE_SIZE);
}

// Description: identique a DoubleVect::ref_data()
void DoubleTab::ref_data(double* ptr, int new_size)
{
  DoubleVect::ref_data(ptr, new_size);
  assert(!get_md_vector().non_nul() && size_reelle() == size_array());
  nb_dim_ = 1;
  dimensions_[0] = dimension_tot_0_ = new_size;
  assert(CHECK_LINE_SIZE);
}

// Description: identique a DoubleVect::ref_array()
//  (cree un tableau monodimensionnel sans structure parallele)
//  Attention, le tableau source et destination sont figes (resize interdit)
//  (voir ArrOfDouble::
void DoubleTab::ref_array(ArrOfDouble& src, int start, int sz)
{
  DoubleVect::ref_array(src, start, sz);
  assert(!get_md_vector().non_nul() && size_reelle() == size_array());
  nb_dim_ = 1;
  dimensions_[0] = dimension_tot_0_ = size_array(); // pas sz qui peut valoir -1
  assert(CHECK_LINE_SIZE);
}

// Description: fait pointer le tableau sur une sous-partie du tableau t
//   definie par la valeur du premier indice et ne nombre de "lignes" du tableau
//   a recuperer (une ligne = toutes les valeurs tab(i,j,k,...) pour un i donne).
//   Le nombre de dimensions du tableau est le meme que pour t,
//   les dimension(i) pour i>=1 sont les memes et dimension(0) = nb_lines.
void DoubleTab::ref_tab(DoubleTab& t, int start_line, int nb_lines)
{
  if (nb_lines < 0)
    nb_lines = t.dimension_tot_0_ - start_line;
  assert(start_line >= 0 && nb_lines >= 0 && start_line + nb_lines <= t.dimension_tot_0_);
  const int l_size = t.line_size();
  DoubleVect::ref_array(t, start_line * l_size, nb_lines * l_size);
  assert(!get_md_vector().non_nul() && size_reelle() == size_array());
  set_line_size_(l_size);
  nb_dim_ = t.nb_dim_;
  dimension_tot_0_ = nb_lines;
  dimensions_[0] = nb_lines;
  for (int i = 1; i < MAXDIM_TAB; i++)
    dimensions_[i] = t.dimensions_[i];
  assert(CHECK_LINE_SIZE);
}

// Description: met le tableau dans l'etat obtenu par le constructeur par defaut
//  voir DoubleVect::reset()
void DoubleTab::reset()
{
  nb_dim_ = 1;
  dimensions_[0] = 0;
  dimension_tot_0_ = 0;
  DoubleVect::reset();
  assert(CHECK_LINE_SIZE);
}

// Description: methode virtuelle qui force le tableau a changer de taille.
//  Change aussi nb_dim_ a 1. Equivalent a DoubleTab::resize(n, opt)
void DoubleTab::resize_tab(int n, Array_base::Resize_Options opt)
{
  resize(n, opt);
  assert(CHECK_LINE_SIZE);
}

// Description: change la dimension[0] du tableau en conservant les autres.
// Precondition: le tableau ne doit pas avoir de structure parallele
void DoubleTab::resize_dim0(int n, Array_base::Resize_Options opt)
{
  assert(n >= 0);
  assert(dimension_tot_0_ * line_size() == size_array());
  DoubleVect::resize_vect_(n * line_size(), opt);
  dimensions_[0] = dimension_tot_0_ = n;
  assert(CHECK_LINE_SIZE);
}

void DoubleTab::resize(int n, Array_base::Resize_Options opt)
{
  assert(n >= 0);
  set_line_size_(1);
  DoubleVect::resize_vect_(n, opt);
  nb_dim_ = 1;
  dimensions_[0] = dimension_tot_0_ = n;
  assert(CHECK_LINE_SIZE);
}

void DoubleTab::resize(int n, int n2, Array_base::Resize_Options opt)
{
  assert(n >= 0 && n2 >= 0);
  set_line_size_(n2);
  int new_size = n * n2;

  DoubleVect::resize_vect_(new_size, opt);
  nb_dim_ = 2;
  dimensions_[0] = dimension_tot_0_ = n;
  dimensions_[1] = n2;
  assert(CHECK_LINE_SIZE);
}

void DoubleTab::resize(int n, int n2, int n3, Array_base::Resize_Options opt)
{
  assert(n >= 0 && n2 >= 0 && n3 >= 0);
  set_line_size_(n2 * n3);
  int new_size = n * n2 * n3;

  DoubleVect::resize_vect_(new_size, opt);
  nb_dim_ = 3;
  dimensions_[0] = dimension_tot_0_ = n;
  dimensions_[1] = n2;
  dimensions_[2] = n3;
  assert(CHECK_LINE_SIZE);
}

void DoubleTab::resize(int n, int n2, int n3, int n4, Array_base::Resize_Options opt)
{
  assert(n >= 0 && n2 >= 0 && n3 >= 0 && n4 >= 0);
  set_line_size_(n2 * n3 * n4);
  int new_size = n * n2 * n3 * n4;

  DoubleVect::resize_vect_(new_size, opt);
  nb_dim_ = 4;
  dimensions_[0] = dimension_tot_0_ = n;
  dimensions_[1] = n2;
  dimensions_[2] = n3;
  dimensions_[3] = n4;
  assert(CHECK_LINE_SIZE);
}

// Description: redimensionne le tableau (nb_dim_ sera egal a tailles.size_array()
//   et dimension(i) a tailles[i].
// Precondition: identiques a DoubleVect::resize_vect_()
void DoubleTab::resize(const ArrOfInt& tailles, Array_base::Resize_Options opt)
{
  nb_dim_ = tailles.size_array();
  if (nb_dim_ <= 0 || nb_dim_ > MAXDIM_TAB)
    {
      Cerr << "Internal error in DoubleTab::resize(const ArrOfInt & tailles, ...) \n"
           << " wrong dimensions number " << nb_dim_ << finl;
      exit();
    }
  int l_size = 1;
  for (int i = 0; i < nb_dim_; i++)
    {
      const int n = tailles[i];
      dimensions_[i] = n;
      if (i > 0)
        l_size *= n;
      if (n < 0)
        {
          Cerr << "Internal error in DoubleTab::resize(const ArrOfInt & tailles, ...) \n"
               << " wrong dimensions: " << tailles << finl;
          exit();
        }
    }
  dimension_tot_0_ = dimensions_[0];
  set_line_size_(l_size);
  resize_vect_(dimensions_[0] * l_size, opt);
  assert(CHECK_LINE_SIZE);
}

// Description: copie la structure et les valeurs du tableau src
//   Restrictions et preconditions identiques a DoubleVect::operator=(const DoubleVect & v)
DoubleTab& DoubleTab::operator=(const DoubleTab& src)
{
  copy(src);
  return *this;
}

// Description: copie la structure et les valeurs de src.
//  Attention: appel invalide si src est un type derive de Vect
//  (sinon quoi faire, un tableau unidimensionnel, ou une copie de la structure ?)
DoubleTab& DoubleTab::operator=(const DoubleVect& src)
{
  assert(src.get_info() == DoubleVect::info());
  DoubleVect::copy_(src);
  // Idem que dans ref(DoubleVect) pour le nombre de dimensions du tableau cree
  const int l = src.line_size();
  if (l == 1)
    {
      nb_dim_ = 1;
    }
  else
    {
      nb_dim_ = 2;
      dimensions_[1] = l;
    }
  if (src.size_reelle_ok())
    {
      int sz = src.size_reelle();
      dimensions_[0] = sz / l;
      assert(sz % l == 0);
    }
  else
    {
      dimensions_[0] = -1;
    }
  dimension_tot_0_ = size_array() / l;
  assert(CHECK_LINE_SIZE);
  return *this;
}

DoubleTab& DoubleTab::operator=(double d)
{
  DoubleVect::operator=(d);
  return *this;
}

void DoubleTab::copy(const DoubleTab& src, Array_base::Resize_Options opt)
{
  if (&src != this)
    {
      DoubleVect::copy_(src, opt);
      nb_dim_ = src.nb_dim_;
      for (int i = 0; i < MAXDIM_TAB; i++)
        dimensions_[i] = src.dimensions_[i];
      dimension_tot_0_ = src.dimension_tot_0_;
      assert(CHECK_LINE_SIZE);
    }
}

double& DoubleTab::operator()(const ArrOfInt& indice)
{
  assert(indice.size_array() == nb_dim_);
#if MAXDIM_TAB != 4
#error Mettre a jour le code pour MAXDIM_TAB ici
#endif
  switch(nb_dim_)
    {
    case 1:
      return operator()(indice[0]);
    case 2:
      return operator()(indice[0], indice[1]);
    case 3:
      return operator()(indice[0], indice[1], indice[2]);
    default:
      return operator()(indice[0], indice[1], indice[2], indice[3]);
    }
}
double DoubleTab::operator()(const ArrOfInt& indice) const
{
  assert(indice.size_array() == nb_dim_);
#if MAXDIM_TAB != 4
#error Mettre a jour le code pour MAXDIM_TAB ici
#endif
  switch(nb_dim_)
    {
    case 1:
      return operator()(indice[0]);
    case 2:
      return operator()(indice[0], indice[1]);
    case 3:
      return operator()(indice[0], indice[1], indice[2]);
    default:
      return operator()(indice[0], indice[1], indice[2], indice[3]);
    }
}

// Description: associe le md_vector au vecteur (voir DoubleVect::set_md_vector())
//  dimension(0) sera initialise a md_vector...get_nb_items_reels().
// Precondition: en plus des preconditions de DoubleVect::set_md_vector(),
//  dimension_tot(0) doit etre egal a get_nb_items_tot() du md_vector.
void DoubleTab::set_md_vector(const MD_Vector& md_vector)
{
  int dim0 = dimension_tot_0_;
  if (md_vector.non_nul())
    {
      // renvoie -1 si l'appel et invalide:
      dim0 = md_vector.valeur().get_nb_items_reels();
    }
  dimensions_[0] = dim0;
  assert(CHECK_LINE_SIZE);
  // a appeler meme pour un md_vector nul (pour remettre size_reelle_):
  DoubleVect::set_md_vector(md_vector);
}

void DoubleTab::ecrit(Sortie& os) const
{
  os << nb_dim_ << finl;
  if (nb_dim_ > 0)
    os.put(dimensions_, nb_dim_, nb_dim_);
  ArrOfInt tmp(nb_dim_);
  for (int i = 0; i < nb_dim_; i++)
    tmp[i] = dimension_tot(i);
  os << tmp;
  DoubleVect::ecrit(os);
}

void DoubleTab::jump(Entree& is)
{
  DoubleTab::lit(is, 0 /* Do not resize&read the array */);
}

// Description: lecture d'un tableau pour reprise de calcul. On lit les valeurs "raw".
//  Attention, si le tableau n'est pas vide, il doit deja avoir la bonne
//  taille et la bonne structure, sinon erreur !
// Parameter resize_and_read if the array is sized AND read (by default, yes)
void DoubleTab::lit(Entree& is, int resize_and_read)
{
  ArrOfInt tmp;
  is >> tmp;
  int ok = 1;
  if (tmp.size_array() != nb_dim_)
    ok = 0;
  if (ok)
    {
      if (size_reelle_ok() && dimension(0) != tmp[0])
        ok = 0;
      for (int i = 1; i < nb_dim_; i++)
        if (dimension(i) != tmp[i])
          ok = 0;
    }
  is >> tmp;
  if (ok && tmp.size_array() != nb_dim_)
    ok = 0;
  if (ok)
    for (int i = 0; i < nb_dim_; i++)
      if (dimension_tot(i) != tmp[i])
        ok = 0;
  // Autorisation ancien format des champs scalaire 183:
  if (tmp.size_array()==1 && nb_dim_==2 && dimension(1)==1 && dimension_tot(0) == tmp[0])
    ok = 1;
  if (resize_and_read)
    {
      if (size_array() == 0 && (!get_md_vector().non_nul()))
        {
          resize(tmp, NOCOPY_NOINIT);
        }
      else
        {
          if (!ok)
            {
              // Si on cherche a relire un tableau de taille inconnue, le tableau doit
              // etre reset() a l'entree. On n'aura pas la structure parallele du tableau !
              Cerr << "Error in DoubleTab::lit: array has wrong dimensions" << finl;
              exit();
            }
        }
    }
  DoubleVect::lit(is,resize_and_read);
}

void mp_norme_tab(const DoubleTab& tableau, ArrOfDouble& norme_colonne)
{
  mp_carre_norme_tab(tableau,norme_colonne);
  for (int c=0; c<norme_colonne.size_array(); c++)
    norme_colonne(c)=sqrt(norme_colonne(c));
}

void local_carre_norme_tab(const DoubleTab& tableau, ArrOfDouble& norme_colonne)
{
  const ArrOfInt& blocs = tableau.get_md_vector().valeur().get_items_to_sum();
  const int nblocs = blocs.size_array() >> 1;
  const DoubleVect& vect = tableau;
  const int lsize = vect.line_size();
  assert(lsize == norme_colonne.size_array());
  for (int ibloc = 0; ibloc < nblocs; ibloc++)
    {
      const int begin_bloc = blocs[ibloc];
      const int end_bloc = blocs[ibloc+1];
      for (int i = begin_bloc; i < end_bloc; i++)
        {
          int k = i * lsize;
          for (int j = 0; j < lsize; j++)
            {
              const double x = vect[k++];
              norme_colonne[j] += x*x;
            }
        }
    }
}

void mp_carre_norme_tab(const DoubleTab& tableau, ArrOfDouble& norme_colonne)
{
  local_carre_norme_tab(tableau, norme_colonne);
  mp_sum_for_each_item(norme_colonne);
}

void local_max_abs_tab(const DoubleTab& tableau, ArrOfDouble& max_colonne)
{
  const ArrOfInt& blocs = tableau.get_md_vector().valeur().get_items_to_compute();
  const int nblocs = blocs.size_array() >> 1;
  const DoubleVect& vect = tableau;
  const int lsize = vect.line_size();
  for (int j = 0; j < lsize; j++)
    max_colonne[j] = 0;
  assert(lsize == max_colonne.size_array());
  for (int ibloc = 0; ibloc < nblocs; ibloc++)
    {
      const int begin_bloc = blocs[ibloc];
      const int end_bloc = blocs[ibloc+1];
      for (int i = begin_bloc; i < end_bloc; i++)
        {
          int k = i * lsize;
          for (int j = 0; j < lsize; j++)
            {
              const double x = dabs(vect[k++]);
              max_colonne[j] = (x > max_colonne[j]) ? x : max_colonne[j];
            }
        }
    }
}

void mp_max_abs_tab(const DoubleTab& tableau, ArrOfDouble& max_colonne)
{
  local_max_abs_tab(tableau, max_colonne);
  mp_max_for_each_item(max_colonne);
}

// Description: Quelqu'un veut-il expliquer ce que fait cette methode ?
void DoubleTab::ajoute_produit_tensoriel(double alpha, const DoubleTab& x, const DoubleTab& y)
{
  // Tableaux vus comme des tableaux unidimensionnels (pour ne pas avoir a gerer nb_dim)
  const DoubleVect& vx = x;
  const DoubleVect& vy = y;
  DoubleVect& v = *this;

  const int line_size_x = vx.line_size();
  const int line_size_y = vy.line_size();
  const int line_size_xy = v.line_size();
  assert(line_size_xy == line_size_x * line_size_y);
  // Pour ne pas diviser par line_size()
  assert(vx.size_totale() * line_size_xy == v.size_totale() * line_size_x);
  assert(vy.size_totale() * line_size_xy == v.size_totale() * line_size_y);

  // blocs d'items a traiter (un bloc par defaut: tout le tableau)
  int default_bloc[2];
  default_bloc[0] = 0;
  default_bloc[1] = (v.line_size() > 0) ? (v.size_totale() / v.line_size()) : 0;
  const int *blocs = default_bloc;
  int nb_blocs = 1;
  if (v.get_md_vector().non_nul())
    {
      const ArrOfInt& blk = v.get_md_vector().valeur().get_items_to_compute();
      blocs = blk.addr();
      nb_blocs = blk.size_array() / 2;
    }

  for (int i_bloc = 0; i_bloc < nb_blocs; i_bloc++)
    {
      const int debut = blocs[i_bloc*2];
      const int fin = blocs[i_bloc*2+1];

      int v_index = debut * line_size_xy;
      for (int i = debut; i < fin; i++)
        {
          for (int j = 0; j < line_size_x; j++)
            {
              double xval = vx[i * line_size_x + j];
              for (int k = 0; k < line_size_y; k++)
                {
                  double yval = vy[i * line_size_y + k];
                  v[v_index] += alpha * xval * yval;
                  v_index++;
                }
            }
        }
    }
}

// Description:
//    Resolution du systeme Ax=b
int DoubleTab::inverse_LU(const ArrOfDouble& b, ArrOfDouble& solution)
{
  int n = b.size_array();
  ArrOfInt index(n);

  DoubleTab lu_dec(n,n);

  int cvg = (*this).decomp_LU(n,index,lu_dec);

  //   Cout<<"##DecompositionLU : origine"<<finl;
  //   int i,j;
  //   for (i=0;i<n;i++)
  //     {
  //       for (j=0;j<n;j++)
  //         {
  //           Cout<<"  "<<(*this)(i,j);
  //         }
  //       Cout<<finl;
  //     }
  //   Cout<<"##DecompositionLU : L"<<finl;
  //   for (i=0;i<n;i++)
  //     {
  //       for (j=0;j<i;j++)
  //         {
  //           Cout<<"  "<<lu_dec(i,j);
  //         }
  //       Cout<<"  1.00000e+00";
  //       for (j=i+1;j<n;j++)
  //         {
  //           Cout<<"  0.00000e+00";
  //         }
  //       Cout<<finl;
  //     }
  //   Cout<<"##DecompositionLU : U"<<finl;
  //   for (i=0;i<n;i++)
  //     {
  //       for (j=0;j<i;j++)
  //         {
  //           Cout<<"  0.00000e+00";
  //         }
  //       for (j=i;j<n;j++)
  //         {
  //           Cout<<"  "<<lu_dec(i,j);
  //         }
  //       Cout<<finl;
  //     }

  if(cvg == 1)
    {
      lu_dec.resoud_LU(n,index,b,solution);
    }
  //   Cout<<"Convergence decomposition matrice : "<<cvg<<finl;

  return cvg;
}

// Description:
//    Decomposition d'une matrice en L.U
//    methode de Crout (diagonale de L =1)
// Retour: matrice A_ = assemblage (L-diagonale)+U
int DoubleTab::decomp_LU(int n, ArrOfInt& index, DoubleTab& matLU)
{
  ArrOfDouble vv(n);

  int i, imax=-1, j , k;
  double big, dum, sum, temp;
  int cvg = 1;

  matLU = (*this);

  //Recupere le coeff max d'une ligne, stocke dans vv
  for (i=0 ; i<n ; i++)
    {
      big = 0;
      for (j=0 ; j<n ; j++)
        {
          if ((temp = fabs(matLU(i,j))) > big)
            {
              big = temp;
            }
        }
      //       Cout<<"decomp_LU big "<<big<<finl;
      if (big == 0)
        {
          Cerr <<"Singular matrix in LU decomposition"<<finl;
          cvg = 0;
          exit();
        }
      vv[i] = 1./big;
    }

  //calcul de la matrice matLU
  for (j=0 ; j<n ; j++)
    {
      for (i=0 ; i<j ; i++)
        {
          sum = matLU(i,j);
          for (k=0 ; k<i ; k++)
            {
              sum -= matLU(i,k) * matLU(k,j);
            }
          matLU(i,j) = sum;
        }

      big = 0;
      for (i=j ; i<n ; i++)
        {
          sum = matLU(i,j);
          for (k=0 ; k<j ; k++)
            {
              sum -= matLU(i,k) * matLU(k,j);
            }
          matLU(i,j) = sum;
          if ((dum = vv(i)*fabs(sum)) >= big)
            {
              big = dum;
              imax = i;
            }
        }

      if (j != imax)
        {
          for (k=0 ; k<n ; k++)
            {
              dum = matLU(imax,k);
              matLU(imax,k) = matLU(j,k);
              matLU(j,k) = dum;
            }
          vv(imax) = vv(j);
        }

      index(j) = imax;
      dum = 1./matLU(j,j);
      for (i=j+1 ; i<n ; i++)
        {
          matLU(i,j) *= dum;
        }
    }

  return cvg;
}

// Description:
//    Resolution du systeme A_x=b
//    A_ contenant le decompostion LU de A (stockee dans une seule matrice)
void DoubleTab::resoud_LU(int n, ArrOfInt& index, const ArrOfDouble& b, ArrOfDouble& solution)
{
  int i,ii=-1,ip,j;
  double sum;

  solution = b;

  for (i=0 ; i<n ; i++)
    {
      ip = index(i);
      sum = solution(ip);
      solution(ip) = solution(i);
      if (ii!=-1)
        {
          for (j=ii ; j<i ; j++)
            {
              sum -= (*this)(i,j)*solution(j);
            }
        }
      else
        {
          if (sum)
            {
              ii =i;
            }
        }
      solution(i) = sum;
    }

  for (i=n-1 ; i>=0 ; i--)
    {
      sum = solution(i);
      for (j=i+1 ; j<n ; j++)
        {
          sum -= (*this)(i,j)*solution(j);
        }
      solution(i) = sum/(*this)(i,i);
    }
}

// Description:
//    Fonction utilisee pour le calcul du du/u (pour convergence implicite)
//    renvoie le max de abs(du(i)/u(i))
//    utilisation    max_ = (u(n+1)-u(n)).max_du_u(u(n))
double DoubleTab::max_du_u(const DoubleTab& u)
{
  assert(size_array() == u.size_array());
  const double *du_ptr = addr();
  const double *u_ptr = u.addr();
  const double epsilon = 1.e-8;
  double res = 0.;
  for (int n = size_array(); n; n--)
    {
      double a = fabs(*du_ptr);
      double b = fabs(*u_ptr);
      double c = a / (b + epsilon);
      if (b > 1.e-2 && c > res)
        res = c;
      du_ptr++;
      u_ptr++;
    }
  return res;
}


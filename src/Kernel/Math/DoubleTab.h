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
// File:        DoubleTab.h
// Directory:   $TRUST_ROOT/src/Kernel/Math
// Version:     /main/10
//
//////////////////////////////////////////////////////////////////////////////
//
// WARNING: DO NOT EDIT THIS FILE! Only edit the template file DoubleTab.h.P
//
//
#ifndef DoubleTab_included
#define DoubleTab_included

#include <DoubleVect.h>

// Nombre maximal de dimensions d'un tableau.
// Meme macro dans IntTab et DoubleTab, test si c'est deja defini
#ifndef MAXDIM_TAB
#define MAXDIM_TAB 4
#endif

class FDoubleTab;
class ArrOfInt;

//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//    Tableau a n entrees pour n<= 4
//    Repose sur un DoubleVect avec calculs de l'indice corespondant
//    Voir les commentaires de DoubleVect
// .SECTION voir aussi
//    DoubleVect
//////////////////////////////////////////////////////////////////////////////
class DoubleTab : public DoubleVect
{
  Declare_instanciable_sans_constructeur(DoubleTab);
public:
  DoubleTab();
  DoubleTab(const DoubleTab&);
  // Les DoubleTab peuvent prendre un argument de plus dans la signature: valeur de remplissage
  // Pour les IntTab on ne peut pas: sinon confusion entre dimension et valeur de remplissage
  DoubleTab(int n);
#ifdef INT_is_64_
  DoubleTab(int n1, True_int n2);
#endif
  DoubleTab(int n1, int n2);
  DoubleTab(int n1, int n2, int n3);
  DoubleTab(int n1, int n2, int n3, int n4);
  virtual void ref(const DoubleVect&);
  virtual void ref(const DoubleTab&);
  virtual void ref_data(double* ptr, int size);
  virtual void ref_array(ArrOfDouble&, int start = 0, int sz = -1);
  virtual void ref_tab(DoubleTab&, int start_line = 0, int nb_lines = -1);
  virtual void reset();

  virtual void resize_tab(int n, Array_base::Resize_Options opt = COPY_INIT);
  void resize_dim0(int n, Array_base::Resize_Options opt = COPY_INIT);
  void resize(int n, Array_base::Resize_Options opt = COPY_INIT);
  void resize(int n1, int n2, Array_base::Resize_Options opt = COPY_INIT);
  void resize(int n1, int n2, int n3, Array_base::Resize_Options opt = COPY_INIT);
  void resize(int n1, int n2, int n3, int n4, Array_base::Resize_Options opt = COPY_INIT);
  void resize(const ArrOfInt& tailles, Array_base::Resize_Options opt = COPY_INIT);
  DoubleTab& operator=(const DoubleTab&);
  DoubleTab& operator=(const DoubleVect&);
  DoubleTab& operator=(const FDoubleTab&);
  DoubleTab& operator=(double d);
  //void copy(const ArrOfDouble &, Array_base::Resize_Options opt = COPY_INIT);
  //void copy(const DoubleVect &, Array_base::Resize_Options opt = COPY_INIT);
  void copy(const DoubleTab&, Array_base::Resize_Options opt = COPY_INIT);

  double& operator()(const ArrOfInt& indice);
  double operator()(const ArrOfInt& indice) const;
  inline double& operator[](int i);
  inline const double& operator[](int i) const ;
  inline double& operator()(int i);
  inline const double& operator()(int i) const ;
  inline double& operator()(int i1, int i2);
  inline const double& operator()(int i1, int i2) const ;
  inline double& operator()(int i1, int i2, int i3);
  inline const double& operator()(int i1, int i2, int i3) const ;
  inline double& operator()(int i1, int i2, int i3, int i4);
  inline const double& operator()(int i1, int i2, int i3, int i4) const ;

  inline int dimension(int) const;
  inline int dimension_tot(int) const;
  inline int nb_dim() const;

  // Attention: pour des vecteurs distribues, la liste des cases calculees depend
  //  du type du MD_Vect associe au vecteur (calcul des cases specifiees
  //  par MD_Vect::get_items_to_compute())
  void ajoute_produit_tensoriel(double alpha, const DoubleTab&, const DoubleTab&); // z+=alpha*x*y;
  int  inverse_LU(const ArrOfDouble&, ArrOfDouble&);
  int  decomp_LU(int, ArrOfInt&, DoubleTab&);
  void resoud_LU(int, ArrOfInt&, const ArrOfDouble&, ArrOfDouble&);
  double max_du_u(const DoubleTab&);

  virtual void set_md_vector(const MD_Vector&);
  virtual void jump(Entree&);
  virtual void lit(Entree&, int resize_and_read=1);
  virtual void ecrit(Sortie&) const;

  inline void append_line(double);
  inline void append_line(double, double);
  inline void append_line(double, double, double);
  inline void append_line(double, double, double, double);

private:
  // Nombre de dimensions du tableau (nb_dim_>=1)
  int nb_dim_;
  // Dimensions "reelles" (dimensions_[0] * line_size() = size_reelle())
  // line_size() est egal au produit des dimensions_[i] pour 1 <= i < nb_dim_
  int dimensions_[MAXDIM_TAB];
  // Dimension totale (nombre de lignes du tableau)
  // = nb lignes reeles + nb lignes virtuelles
  // Les dimensions dimension_tot(i>=1) sont implicitement
  // egales a dimension(i)
  int dimension_tot_0_;
};

// DoubleTab operator + (const DoubleTab&, const double) ;

// DoubleTab operator - (const DoubleTab&, const double) ;

// DoubleTab operator -(const DoubleTab&) ;

// DoubleTab operator * (const DoubleTab&, double) ;

// DoubleTab operator / (const DoubleTab&, double) ;

// DoubleTab operator * (double, const DoubleTab&) ;

// DoubleTab operator / (double, const DoubleTab&) ;

//int DoubleTab_test();
void mp_norme_tab(const DoubleTab& tableau, ArrOfDouble& norme_colonne);
void local_carre_norme_tab(const DoubleTab& tableau, ArrOfDouble& norme_colonne);
void mp_carre_norme_tab(const DoubleTab& tableau, ArrOfDouble& norme_colonne);
void local_max_abs_tab(const DoubleTab& tableau, ArrOfDouble& max_colonne);
void mp_max_abs_tab(const DoubleTab& tableau, ArrOfDouble& max_colonne);
inline double& DoubleTab::operator[](int i)
{
  assert(nb_dim_ == 1 || (nb_dim_ == 2 && dimensions_[1] == 1));
  assert(i >= 0 && i < dimension_tot_0_);
  return DoubleVect::operator[](i);
}

inline const double& DoubleTab::operator[](int i) const
{
  assert(nb_dim_ == 1 || (nb_dim_ == 2 && dimensions_[1] == 1));
  assert(i >= 0 && i < dimension_tot_0_);
  return DoubleVect::operator[](i);
}

inline double& DoubleTab::operator()(int i)
{
  assert(nb_dim_ == 1 || (nb_dim_ == 2 && dimensions_[1] == 1));
  assert(i >= 0 && i < dimension_tot_0_);
  return DoubleVect::operator[](i);
}

inline const double& DoubleTab::operator()(int i) const
{
  assert(nb_dim_ == 1 || (nb_dim_ == 2 && dimensions_[1] == 1));
  assert(i >= 0 && i < dimension_tot_0_);
  return DoubleVect::operator[](i);
}

inline double& DoubleTab::operator()(int i1, int i2)
{
  assert(nb_dim_ == 2);
  assert(i1 >= 0 && i1 < dimension_tot_0_);
  assert(i2 >= 0 && i2 < dimensions_[1]);
  return DoubleVect::operator[](i1*dimensions_[1]+i2);
}

inline const double& DoubleTab::operator()(int i1, int i2) const
{
  assert(nb_dim_ == 2);
  assert(i1 >= 0 && i1 < dimension_tot_0_);
  assert(i2 >= 0 && i2 < dimensions_[1]);
  return DoubleVect::operator[](i1*dimensions_[1]+i2);
}

inline double& DoubleTab::operator()(int i1, int i2, int i3)
{
  assert(nb_dim_ == 3);
  assert(i1 >= 0 && i1 < dimension_tot_0_);
  assert(i2 >= 0 && i2 < dimensions_[1]);
  assert(i3 >= 0 && i3 < dimensions_[2]);
  return DoubleVect::operator[]((i1*dimensions_[1]+i2)*dimensions_[2]+i3);
}

inline const double& DoubleTab::operator()(int i1, int i2, int i3) const
{
  assert(nb_dim_ == 3);
  assert(i1 >= 0 && i1 < dimension_tot_0_);
  assert(i2 >= 0 && i2 < dimensions_[1]);
  assert(i3 >= 0 && i3 < dimensions_[2]);
  return DoubleVect::operator[]((i1*dimensions_[1]+i2)*dimensions_[2]+i3);
}

inline double& DoubleTab::operator()(int i1, int i2, int i3, int i4)
{
  assert(nb_dim_ == 4);
  assert(i1 >= 0 && i1 < dimension_tot_0_);
  assert(i2 >= 0 && i2 < dimensions_[1]);
  assert(i3 >= 0 && i3 < dimensions_[2]);
  assert(i4 >= 0 && i4 < dimensions_[3]);
  return DoubleVect::operator[](((i1*dimensions_[1]+i2)*dimensions_[2]+i3)*dimensions_[3]+i4);
}
inline const double& DoubleTab::operator()(int i1, int i2, int i3, int i4) const
{
  assert(nb_dim_ == 4);
  assert(i1 >= 0 && i1 < dimension_tot_0_);
  assert(i2 >= 0 && i2 < dimensions_[1]);
  assert(i3 >= 0 && i3 < dimensions_[2]);
  assert(i4 >= 0 && i4 < dimensions_[3]);
  return DoubleVect::operator[](((i1*dimensions_[1]+i2)*dimensions_[2]+i3)*dimensions_[3]+i4);
}

// Description: Returns one of the "real" dimensions of the multi-dimensionnal array,
//  as defined by:
//   dimension(0) = size_reelle() / line_size(), or 0 if line_size()==0
//  and, for i >= 1:
//   dimension(i) is equal to dimension_tot(i)
//  If size_reelle_ok() returns 0, it is invalid to ask for dimension(0). You can only ask for
//   dimension_tot(0) (see DoubleVect::size_reelle_ok())
inline int DoubleTab::dimension(int i) const
{
  assert(i >= 0 && i < nb_dim_);
  // Si dimension_[0] == -1, c'est que c'est un vecteur distribue et que l'attribut size() est invalide.
  // Il faut alors utiliser dimension_tot pour ce tableau.
  assert(dimensions_[i] >= 0);
  return dimensions_[i];
}

// Description: Returns the total dimensions of the multi-dimensionnal array, including
//  virtual items (used in parallel distributed arrays)
inline int DoubleTab::dimension_tot(int i) const
{
  assert(i >= 0 && i < nb_dim_);
  if (i == 0)
    return dimension_tot_0_;
  else
    return dimensions_[i];
}

// Description: Returns the number of dimensions of the array (>= 1)
inline int DoubleTab::nb_dim() const
{
  return nb_dim_;
}

// Description: Adds 1 to dimension_tot(0) and puts a in the added line.
// Precondition: line_size() must be equal to 1 and the array must be resizable.
inline void DoubleTab::append_line(double a)
{
  assert(line_size() == 1);
  assert(dimension_tot_0_ * line_size() == size_array());
  const int n = dimension_tot_0_;
  dimensions_[0] = ++dimension_tot_0_;
  DoubleVect::resize_vect_(n+1, COPY_NOINIT);
  double * ptr = addr() + n;
  ptr[0] = a;
}

// Description: Adds 1 to dimension_tot(0) and puts a and b in the added line.
// Precondition: line_size() must be equal to 2 and the array must be resizable.
inline void DoubleTab::append_line(double a, double b)
{
  assert(line_size() == 2);
  assert(dimension_tot_0_ * line_size() == size_array());
  const int n = dimension_tot_0_ * 2;
  dimensions_[0] = ++dimension_tot_0_;
  DoubleVect::resize_vect_(n+2, COPY_NOINIT);
  double * ptr = addr() + n;
  ptr[0] = a;
  ptr[1] = b;
}

// Description: Like append_line(i,j), but for arrays with line_size()==3
inline void DoubleTab::append_line(double a, double b, double c)
{
  assert(line_size() == 3);
  assert(dimension_tot_0_  * line_size() == size_array());
  const int n = dimension_tot_0_ * 3;
  dimensions_[0] = ++dimension_tot_0_;
  DoubleVect::resize_vect_(n+3, COPY_NOINIT);
  double * ptr = addr() + n;
  ptr[0] = a;
  ptr[1] = b;
  ptr[2] = c;
}

// Description: Like append_line(i,j), but for arrays with line_size()==4
inline void DoubleTab::append_line(double a, double b, double c, double d)
{
  assert(line_size() == 4);
  assert(dimension_tot_0_  * line_size() == size_array());
  const int n = dimension_tot_0_ * 4;
  dimensions_[0] = ++dimension_tot_0_;
  DoubleVect::resize_vect_(n+4, COPY_NOINIT);
  double * ptr = addr() + n;
  ptr[0] = a;
  ptr[1] = b;
  ptr[2] = c;
  ptr[3] = d;
}
#endif


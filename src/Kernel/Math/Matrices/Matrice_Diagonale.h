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
// File:        Matrice_Diagonale.h
// Directory:   $TRUST_ROOT/src/Kernel/Math/Matrices
// Version:     /main/17
//
//////////////////////////////////////////////////////////////////////////////

#ifndef Matrice_Diagonale_included
#define Matrice_Diagonale_included

#include <Matrice_Base.h>
#include <DoubleVect.h>

//////////////////////////////////////////////////////////////////////////////
//
// .DESCRIPTION
//    Classe Matrice_Diagonale
//    Represente une matrice diagonale.
// .SECTION voir aussi
//    Matrice_Base
//////////////////////////////////////////////////////////////////////////////
class Matrice_Diagonale : public Matrice_Base
{

  Declare_instanciable_sans_constructeur(Matrice_Diagonale);

public :
  virtual int ordre( void ) const;
  virtual int nb_lignes( void ) const;
  virtual int nb_colonnes( void ) const;

  virtual DoubleVect& ajouter_multvect_( const DoubleVect& x, DoubleVect& r ) const;
  virtual DoubleVect& ajouter_multvectT_( const DoubleVect& x, DoubleVect& r ) const;
  virtual DoubleTab& ajouter_multTab_( const DoubleTab& x, DoubleTab& r ) const;

  virtual void scale( const double& x );

  virtual void get_stencil( IntTab& stencil ) const;

  virtual void get_symmetric_stencil( IntTab& stencil ) const;

  virtual void get_stencil_and_coefficients( IntTab&      stencil,
                                             ArrOfDouble& coefficients ) const;

  virtual void get_symmetric_stencil_and_coefficients( IntTab&      stencil,
                                                       ArrOfDouble& coefficients ) const;
public :
  Matrice_Diagonale( void );
  Matrice_Diagonale( int size );
  Matrice_Diagonale(const DoubleVect& coefficients);

  DoubleVect& get_coefficients( void );
  const DoubleVect& get_coefficients( void ) const;

  void dimensionner( int size );

  double  coeff( int i, int j ) const;
  double& coeff( int i, int j );

protected :
  DoubleVect coefficients_;

};

#endif

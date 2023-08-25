/****************************************************************************
* Copyright (c) 2023, CEA
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

#ifndef Mod_turb_hyd_included
#define Mod_turb_hyd_included

#include <Mod_turb_hyd_base.h>
#include <TRUST_Deriv.h>

/*! @brief Classe Mod_turb_hyd Classe generique de la hierarchie des modeles de turbulence utilises
 *
 *     par une equation_base
 *     un objet Mod_turb_hyd peut referencer n'importe quel objet derivant de
 *     Mod_turb_hyd_base.
 *     La plupart des methodes appellent les methodes de l'objet Mod_turb_hyd
 *     sous-jacent via la methode valeur() declaree grace a la macro
 *
 * @sa Mod_turb_hyd_base MorEqn
 */
class Mod_turb_hyd : public MorEqn , public DERIV(Mod_turb_hyd_base)
{
  Declare_instanciable(Mod_turb_hyd);

public:

  inline Mod_turb_hyd& operator=(const Mod_turb_hyd_base& );
  inline const Champ_Fonc& viscosite_turbulente() const;
  /*Modification pour utilisation des fonctions de la classe MorEqn*/
  inline const Turbulence_paroi& loi_paroi() const;

  inline int preparer_calcul();
  inline void mettre_a_jour(double );
  inline void discretiser();
  inline void completer();
  inline int sauvegarder(Sortie& os) const override;
  inline int reprendre(Entree& is) override;
  inline void imprimer(Sortie& os) const;
};


/*! @brief Operateur d'affectation d'un Mod_turb_hyd_base dans un Mod_turb_hyd.
 *
 * @param (Mod_turb_hyd_base& x) partie droite de l'affectation
 * @return (Mod_turb_hyd&) resultat de l'affectation (*this)
 */
inline Mod_turb_hyd& Mod_turb_hyd::operator=(const Mod_turb_hyd_base& x)
{
  DERIV(Mod_turb_hyd_base)::operator=(x);
  return *this;
}


/*! @brief Appel a l'objet sous-jacent.
 *
 * Renvoie la viscosite turbulente.
 *
 * @return (Champ_Fonc&) le champ representant la viscosite turbulente
 */
inline const Champ_Fonc& Mod_turb_hyd::viscosite_turbulente() const
{
  return valeur().viscosite_turbulente();
}

/*! @brief Appel a l'objet sous-jacent.
 *
 * Renvoie la loi de turbulence sur la paroi
 *
 * @return (Turbulence_paroi&) la loi de turbulence sur la paroi
 */
inline const Turbulence_paroi& Mod_turb_hyd::loi_paroi() const
{
  return valeur().loi_paroi();
}

/*! @brief Appel a l'objet sous-jacent
 *
 */
inline int Mod_turb_hyd::preparer_calcul()
{
  return valeur().preparer_calcul();
}


/*! @brief Appel a l'objet sous-jacent.
 *
 * Effectue une mise a jour en temps
 *
 * @param (double temps) le temps de mise a jour
 */
inline void Mod_turb_hyd::mettre_a_jour(double temps)
{
  valeur().mettre_a_jour(temps);
}


/*! @brief Appel a l'objet sous-jacent Effectue une sauvegarde sur un flot de sortie
 *
 * @param (Sortie& os) un flot de sortie
 * @return (int) code de retour propage
 */
inline int Mod_turb_hyd::sauvegarder(Sortie& os) const
{
  return valeur().sauvegarder(os);
}


/*! @brief Appel a l'objet sous-jacent Effectue une reprise sur un flot d'entree
 *
 * @param (Entree& is) un flot d'entree
 * @return (int) code de retour propage
 */
inline int Mod_turb_hyd::reprendre(Entree& is)
{
  return valeur().reprendre(is);
}


/*! @brief Appel a l'objet sous-jacent Discretise le modele de turbulence
 *
 */
inline void Mod_turb_hyd::discretiser()
{
  valeur().discretiser();
}


/*! @brief Appel a l'objet sous-jacent
 *
 */
inline void Mod_turb_hyd::completer()
{
  valeur().completer();
  valeur().loi_paroi()->completer();
}

/*! @brief Appel a l'objet sous-jacent
 *
 */
inline void Mod_turb_hyd::imprimer(Sortie& os) const
{
  valeur().imprimer(os);
}


#endif


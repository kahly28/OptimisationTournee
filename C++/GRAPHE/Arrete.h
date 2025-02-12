#ifndef PROJETPPIL_ARRETE_H
#define PROJETPPIL_ARRETE_H

#include <ostream>
#include "GElement.h"
#include "Sommet.h"
#include "Ville.h"
#include "../ERREUR/Erreur.h"

template <typename S, typename T>

/**
 * @class Arrete
 * @brief Représente une arête dans un graphe, reliant deux sommets.
 *
 * Cette classe générique hérite de `GElement` et permet de définir une arête avec une clé, une valeur,
 * et des sommets de début et de fin. Elle gère également les degrés des sommets.
 *
 * @tparam S Type de la valeur associée à l'arête.
 * @tparam T Type de la valeur associée aux sommets reliés par l'arête.
 */

class Arrete : public GElement<S> {
public:
    Sommet<T> * debut; ///< Pointeur vers le sommet de début de l'arête.
    Sommet<T> * fin; ///< Pointeur vers le sommet de fin de l'arête.

    //Constructeur
    /**
     * @brief Constructeur par défaut.
     *
     * Initialise une arête sans valeurs ni sommets associés.
     */
    Arrete() = default;

    /**
     * @brief Constructeur paramétré.
     *
     * Initialise une arête avec une clé, une valeur, et deux sommets de début et de fin.
     * Incrémente les degrés des sommets associés.
     *
     * @param clef Clé unique identifiant l'arête.
     * @param v Valeur associée à l'arête.
     * @param debut Pointeur vers le sommet de début de l'arête.
     * @param fin Pointeur vers le sommet de fin de l'arête.
     */

    Arrete(int clef, const S& v, Sommet<T>* debut, Sommet<T>* fin): GElement<S>(clef, v), debut(debut), fin(fin) {
        if (debut != nullptr) debut->degre++;
        if (fin != nullptr) fin->degre++;
    }

/**
     * @brief Destructeur.
     *
     * Décrémente les degrés des sommets de début et de fin avant la destruction de l'arête.
     */
    virtual ~Arrete() {
        if (this->debut != nullptr) this->debut->degre--;
        if (this->fin != nullptr) this->fin->degre--;
    }

    /**
 * @brief Récupère la latitude minimale entre les deux sommets de l'arête.
 *
 * Cette méthode accède aux coordonnées des deux sommets (`debut` et `fin`) et retourne la latitude la plus petite (coordonnée X) parmi les deux.
 * Elle vérifie d'abord que le type générique `T` est bien `Ville`, et que les sommets ne sont pas nuls avant de procéder.
 *
 * @return La latitude minimale entre les deux sommets (valeur numérique de type `double`).
 *
 * @throws Erreur Si le type `T` n'est pas `Ville`.
 * @throws std::logic_error Si les sommets de l'arête sont nuls.
 */
    double getMinLat() {
        // Vérifie dynamiquement que T est bien de type Ville
        if (typeid(T) != typeid(Ville)) {
            throw new Erreur("Le type T n'est pas Ville");
        }

        // Vérifie que les sommets ne sont pas nuls
        if (!debut || !fin) {
            throw std::logic_error("Les sommets de l'arête ne peuvent pas être nuls.");
        }

        // Accède aux coordonnées des deux sommets
        double longDebut = debut->v.getCoordonees().getX();
        double longFin = fin->v.getCoordonees().getX();

        // Retourne la plus petite des deux longitudes
        return std::min(longDebut, longFin);
    }

    /**
 * @brief Récupère la longitude minimale entre les deux sommets de l'arête.
 *
 * Cette méthode accède aux coordonnées des deux sommets (`debut` et `fin`) et retourne la longitude la plus petite (coordonnée Y) parmi les deux.
 * Elle vérifie d'abord que le type générique `T` est bien `Ville`, et que les sommets ne sont pas nuls avant de procéder.
 *
 * @return La longitude minimale entre les deux sommets (valeur numérique de type `double`).
 *
 * @throws Erreur Si le type `T` n'est pas `Ville`.
 * @throws std::logic_error Si les sommets de l'arête sont nuls.
 */
    double getMinLong() {
        // Vérifie dynamiquement que T est bien de type Ville
        if (typeid(T) != typeid(Ville)) {
            throw new Erreur("Le type T n'est pas Ville");
        }

        // Vérifie que les sommets ne sont pas nuls
        if (!debut || !fin) {
            throw std::logic_error("Les sommets de l'arête ne peuvent pas être nuls.");
        }

        // Accède aux coordonnées des deux sommets
        double longDebut = debut->v.getCoordonees().getY();
        double longFin = fin->v.getCoordonees().getY();

        // Retourne la plus petite des deux longitudes
        return std::min(longDebut, longFin);
    }

    /**
 * @brief Récupère la latitude maximale entre les deux sommets de l'arête.
 *
 * Cette méthode accède aux coordonnées des deux sommets (`debut` et `fin`) et retourne la latitude la plus grande (coordonnée X) parmi les deux.
 * Elle vérifie d'abord que le type générique `T` est bien `Ville`, et que les sommets ne sont pas nuls avant de procéder.
 *
 * @return La latitude maximale entre les deux sommets (valeur numérique de type `double`).
 *
 * @throws Erreur Si le type `T` n'est pas `Ville`.
 * @throws std::logic_error Si les sommets de l'arête sont nuls.
 */
    double getMaxLat() {
        // Vérifie dynamiquement que T est bien de type Ville
        if (typeid(T) != typeid(Ville)) {
            throw new Erreur("Le type T n'est pas Ville");
        }

        // Vérifie que les sommets ne sont pas nuls
        if (!debut || !fin) {
            throw std::logic_error("Les sommets de l'arête ne peuvent pas être nuls.");
        }

        // Accède aux coordonnées des deux sommets
        double longDebut = debut->v.getCoordonees().getX();
        double longFin = fin->v.getCoordonees().getX();

        // Retourne la plus petite des deux longitudes
        return std::max(longDebut, longFin);
    }

    /**
 * @brief Récupère la longitude maximale entre les deux sommets de l'arête.
 *
 * Cette méthode accède aux coordonnées des deux sommets (`debut` et `fin`) et retourne la longitude la plus grande (coordonnée Y) parmi les deux.
 * Elle vérifie d'abord que le type générique `T` est bien `Ville`, et que les sommets ne sont pas nuls avant de procéder.
 *
 * @return La longitude maximale entre les deux sommets (valeur numérique de type `double`).
 *
 * @throws Erreur Si le type `T` n'est pas `Ville`.
 * @throws std::logic_error Si les sommets de l'arête sont nuls.
 */
    double getMaxLong() {
        // Vérifie dynamiquement que T est bien de type Ville
        if (typeid(T) != typeid(Ville)) {
            throw new Erreur("Le type T n'est pas Ville");
        }

        // Vérifie que les sommets ne sont pas nuls
        if (!debut || !fin) {
            throw std::logic_error("Les sommets de l'arête ne peuvent pas être nuls.");
        }

        // Accède aux coordonnées des deux sommets
        double longDebut = debut->v.getCoordonees().getY();
        double longFin = fin->v.getCoordonees().getY();

        // Retourne la plus petite des deux longitudes
        return std::max(longDebut, longFin);
    }

    /**
     * @brief Opérateur de conversion en chaîne de caractères.
     *
     * Représente l'arête sous forme de chaîne contenant ses informations principales
     * (clé, valeur, sommet de début et sommet de fin).
     *
     * @return Une chaîne de caractères décrivant l'arête.
     */

    operator string() const {
        ostringstream oss;
        oss << "Arrete[Clef: " << this->clef
            << ", Valeur: " << this->v
            << ", Sommet de debut: " << this->debut
            << ", Sommet de fin: " <<this->fin;
        return oss.str();
    }

/**
     * @brief Opérateur d'écriture sur un flux.
     *
     * Permet d'écrire une représentation de l'arête dans un flux (ex : console ou fichier).
     *
     * @param os Flux de sortie.
     * @param arrete Arête à écrire dans le flux.
     * @return Une référence au flux de sortie modifié.
     */

    friend ostream &operator<<(ostream &os, const Arrete &arrete) {
        os << arrete.operator string();
        return os;
    }

/**
     * @brief Vérifie si deux sommets forment cette arête.
     *
     * Compare les sommets donnés avec ceux de l'arête, quelle que soit leur orientation.
     *
     * @param s1 Premier sommet à comparer.
     * @param s2 Second sommet à comparer.
     * @return `true` si les deux sommets forment cette arête (dans un ordre quelconque), `false` sinon.
     */

    bool estEgal(const Sommet<T>* s1, const Sommet<T>* s2)const {
        return (this->debut == s1 && this->fin == s2) || (this->debut == s2 && this->fin == s1);
    }

};

#endif //PROJETPPIL_ARRETE_H
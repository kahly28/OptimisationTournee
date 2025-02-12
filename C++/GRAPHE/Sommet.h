#ifndef PROJETPPIL_SOMMET_H
#define PROJETPPIL_SOMMET_H


#include <ostream>
#include "GElement.h"

template <typename T>
/**
 * @class Sommet
 * @brief Représente un sommet dans un graphe.
 *
 * Cette classe générique hérite de `GElement` et permet de définir un sommet avec une clé unique, une valeur,
 * et un degré représentant le nombre d'arêtes connectées au sommet.
 *
 * @tparam T Type de la valeur associée au sommet.
 */

class Sommet : public GElement<T> {
public:
    int degre; ///< Degré du sommet, représentant le nombre d'arêtes connectées.

    /**
     * @brief Constructeur paramétré.
     *
     * Initialise un sommet avec une clé, une valeur, et un degré.
     * Vérifie que le degré est positif, sinon lève une exception.
     *
     * @param clef Clé unique identifiant le sommet.
     * @param v Valeur associée au sommet.
     * @param degre Degré initial du sommet (par défaut à 0).
     *
     * @throws std::invalid_argument Si le degré est négatif.
     */
    Sommet(int clef, T v, int degre = 0) : GElement<T>(clef, v) {
        if (degre < 0) {
            throw std::invalid_argument("Le degré d'un sommet ne peut pas être négatif.");
        }
        this->degre = degre;
    }

// Opérateurs

    /**
     * @brief Opérateur d'affectation.
     *
     * Permet de copier les attributs d'un autre sommet dans celui-ci,
     * tout en évitant l'auto-affectation.
     *
     * @param other Référence constante vers le sommet à copier.
     * @return Une référence vers le sommet actuel modifié.
     */
    Sommet& operator=(const Sommet& other) {
        if (this != &other) { // Éviter l'auto-affectation
            GElement<T>::operator=(other); // Copie des attributs de la classe de base
            this->degre = other.degre; // Copie du degré
        }
        return *this;
    }

/**
     * @brief Opérateur de conversion en chaîne de caractères.
     *
     * Génère une représentation textuelle du sommet contenant sa clé,
     * sa valeur, et son degré.
     *
     * @return Une chaîne de caractères décrivant le sommet.
     */
    operator string() const {
        ostringstream oss;
        oss << "Sommet[Clef: " << GElement<T>::clef
        << ", Valeur: " << GElement<T>::v
        << ", Degré: " << degre << "]";
        return oss.str();
    }


/**
     * @brief Opérateur d'écriture sur un flux.
     *
     * Permet d'écrire une représentation du sommet dans un flux
     * (ex : console ou fichier).
     *
     * @param os Flux de sortie.
     * @param sommet Sommet à écrire dans le flux.
     * @return Une référence au flux de sortie modifié.
     */
    friend ostream &operator<<(ostream &os, const Sommet &sommet) {
        os << sommet.operator string();
        return os;
    }

};

#endif //PROJETPPIL_SOMMET_H

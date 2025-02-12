#ifndef PROJETPPIL_GELEMENT_H
#define PROJETPPIL_GELEMENT_H


#include <ostream>
#include "AElement.h"

template <typename T>
/**
 * @class GElement
 * @brief Classe générique représentant un élément avec une clé et une valeur.
 *
 * Cette classe hérite de la classe `AElement` et ajoute un attribut générique `v`
 * pour représenter une valeur associée à la clé.
 *
 * @tparam T Type de la valeur associée à l'élément.
 */
class GElement : public AElement {
public:
    T v; ///< Attribut générique représentant la valeur associée à l'élément.

    /**
     * @brief Constructeur de la classe GElement.
     *
     * Initialise un élément avec une clé et une valeur.
     *
     * @param clef La clé de l'élément.
     * @param v La valeur associée à l'élément.
     */

    GElement(int clef, T v) : AElement(clef), v(v) {}

    /**
     * @brief Opérateur de conversion en chaîne de caractères.
     *
     * Cette méthode permet de représenter un objet de type GElement sous
     * forme de chaîne de caractères au format "GElement[clef=<valeur>, valeur=<valeur>]".
     *
     * @return Une chaîne de caractères représentant l'objet.
     */

    operator string() const {
        ostringstream oss;
        oss << "GElement[clef=" << clef << ", valeur=" << v << "]";
        return oss.str();
    }

    /**
     * @brief Opérateur d'écriture sur un flux de sortie.
     *
     * Cette méthode permet d'écrire l'objet dans un flux (par exemple, un fichier ou la console),
     * en affichant la clé héritée et la valeur associée sous la forme :
     * "clef: <valeur> v: <valeur>".
     *
     * @param os Le flux de sortie.
     * @param element L'objet GElement à écrire dans le flux.
     * @return Une référence au flux de sortie modifié.
     */

    friend ostream &operator<<(ostream &os, const GElement &element) {
        // Appelle l'opérateur << de la classe de base (AElement) pour écrire la clé
        os << static_cast<const AElement &>(element) << " v: " << element.v;
        return os;
    }

};


#endif //PROJETPPIL_GELEMENT_H

#ifndef PROJETPPIL_AELEMENT_H
#define PROJETPPIL_AELEMENT_H


#include <ostream>
#include <sstream>

using namespace std;

/**
 * @class AElement
 * @brief Classe représentant un élément avec une clé.
 *
 * Cette classe encapsule un entier `clef` et fournit des fonctionnalités
 * pour convertir l'objet en chaîne de caractères et pour l'écrire dans un flux.
 */
class AElement {
public :
    int clef; ///< Attribut représentant la clé associée à l'élément.

    //Constructeur
    /**
     * @brief Constructeur de la classe AElement.
     * @param clef La valeur de la clé à associer à l'élément.
     */

    AElement(int clef) : clef(clef) {}

//Opérateur de conversion en string
    /**
     * @brief Opérateur de conversion en chaîne de caractères.
     *
     * Cette méthode permet de représenter un objet de type AElement sous
     * forme de chaîne de caractères au format "AElement[clef=<valeur>]".
     *
     * @return Une chaîne de caractères représentant l'objet.
     */
    operator string() const {
        ostringstream oss;
        oss << "AElement[clef=" << clef << "]";
        return oss.str();
    }

//Opérateur << d'écriture sur un flux
    /**
     * @brief Opérateur d'écriture sur un flux de sortie.
     *
     * Cette méthode permet d'écrire la clé de l'objet dans un flux (par exemple, un fichier
     * ou la console) sous la forme "clef: <valeur>".
     *
     * @param os Le flux de sortie.
     * @param element L'objet AElement à écrire dans le flux.
     * @return Une référence au flux de sortie modifié.
     */

    friend ostream &operator<<(ostream &os, const AElement &element) {
        os << "clef: " << element.clef;
        return os;
    }

};


#endif //PROJETPPIL_AELEMENT_H

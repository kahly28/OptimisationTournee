//
// Created by Enzo-pc on 03/01/2025.
//

#ifndef PROJET_ACL_INITCOR_H
#define PROJET_ACL_INITCOR_H


#include "ExpertFichierCOR.h"
#include "ExpertFichierJSON.h"
template <typename S, typename T>

/**
 * @brief Classe responsable de l'initialisation de la chaîne de responsabilité pour le traitement des fichiers.
 *
 * Cette classe permet d'initialiser la chaîne de responsabilité en créant et en renvoyant le premier maillon, qui est un `ExpertFichierJSON` dans ce cas.
 * Elle s'assure également que les types des paramètres génériques sont corrects (le type `T` doit être `Ville` et le type `S` doit être un type numérique).
 *
 * @tparam S Type représentant les poids des arêtes (doit être un type numérique).
 * @tparam T Type représentant les sommets du graphe (doit être de type `Ville`).
 */
class InitCor {
    static_assert(std::is_same<T, Ville>::value, "Erreur : le type du sommet doit être une Ville !");
    static_assert(std::is_arithmetic<S>::value, "Erreur : le type de l'arete doit être un un nombre  !");
public:
    /**
     * @brief Initialise la chaîne de responsabilité pour le traitement des fichiers.
     *
     * Cette méthode crée et renvoie le premier expert de la chaîne de responsabilité, qui est un `ExpertFichierJSON` dans ce cas.
     * Le maillon suivant dans la chaîne est `NULL`, ce qui signifie qu'il n'y a pas d'expert supplémentaire après cet expert dans cette configuration.
     *
     * @return Un pointeur vers le premier maillon de la chaîne de responsabilité (un objet `ExpertFichierCOR<S,T>`).
     */
    static ExpertFichierCOR<S,T> * InitCorFichier(){
        ExpertFichierCOR<S,T> * e1;
        e1=new ExpertFichierJSON<S,T>(NULL);
        return e1;
    }
};


#endif //PROJET_ACL_INITCOR_H

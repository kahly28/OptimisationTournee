#ifndef PROJETPPIL_EXPERTFICHIER_H
#define PROJETPPIL_EXPERTFICHIER_H

#include <string>
#include "../VISITOR_FICHIER/Visitor_Fichier.h"

/**
 * @brief Interface de la chaîne de responsabilité pour la gestion des fichiers.
 */
template<typename S,typename T>
class ExpertFichier {
public:
    /**
     * @brief Résout le traitement du fichier spécifié.
     * @param s Nom du fichier à traiter.
     * @return Visiteur associé au traitement du fichier.
     */
    virtual Visitor_Fichier<S,T>* resoudre(const string & s) const = 0;
};

#endif // PROJETPPIL_EXPERTFICHIER_H

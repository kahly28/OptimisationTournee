#ifndef PROJETPPIL_EXPERTFICHIERCOR_H
#define PROJETPPIL_EXPERTFICHIERCOR_H

#include <stdexcept>
#include "ExpertFichier.h"
#include "../VISITOR_FICHIER/Visitor_Fichier.h"
template <typename S, typename T>
/**
 * @brief Classe abstraite représentant un maillon de la chaîne de responsabilité pour la gestion des fichiers.
 */
class ExpertFichierCOR : public ExpertFichier<S,T> {
public:
    ExpertFichierCOR * suivant; /**< Pointeur vers le maillon suivant dans la chaîne de responsabilité. */

    /**
     * @brief Constructeur de la classe ExpertFichierCOR.
     * @param suivant Pointeur vers le maillon suivant dans la chaîne de responsabilité.
     */
    ExpertFichierCOR(ExpertFichierCOR * suivant): suivant(suivant) {}

    /**
     * @brief Résout le traitement du fichier spécifié.
     * @param s Nom du fichier à traiter.
     * @return Visiteur associé au traitement du fichier.
     * @throws invalid_argument Si le type de fichier n'est pas géré par cette classe ni par les suivantes dans la chaîne.
     */
    virtual Visitor_Fichier<S,T>* resoudre(const string & s) const override {
        if(saitTraiter(s)) {
            return Traiter();
        } else {
            if(this->suivant != NULL) {
                return this->suivant->resoudre(s);
            } else {
                throw invalid_argument("Type de fichier impossible à traiter\n");
            }
        }
    }

    /**
     * @brief Vérifie si le maillon actuel peut traiter le fichier spécifié.
     * @param s Nom du fichier à traiter.
     * @return true si le maillon peut traiter le fichier, sinon false.
     */
    virtual bool saitTraiter(const string &s) const = 0;

    /**
     * @brief Traite le fichier.
     * @return Visiteur associé au traitement du fichier.
     */
    virtual Visitor_Fichier<S,T>* Traiter() const = 0;
};

#endif // PROJETPPIL_EXPERTFICHIERCOR_H

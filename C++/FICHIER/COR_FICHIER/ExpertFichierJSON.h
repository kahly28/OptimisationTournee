//
// Created by Enzo-pc on 27/12/2024.
//

#ifndef PROJET_ACL_EXPERTFICHIERJSON_H
#define PROJET_ACL_EXPERTFICHIERJSON_H


#include "ExpertFichierCOR.h"
#include "JSON.h"
template <typename S, typename T>
/**
 * @brief Classe représentant un expert pour traiter les fichiers JSON.
 *
 * Cette classe fait partie du modèle de chaîne de responsabilité (Chain of Responsibility).
 * Elle permet de traiter spécifiquement les fichiers JSON en vérifiant leur extension et en créant le visiteur approprié pour charger les données depuis un fichier JSON.
 *
 * @tparam S Type représentant les poids des arêtes (doit être un type numérique).
 * @tparam T Type représentant les sommets du graphe (doit être de type `Ville`).
 */
class ExpertFichierJSON : public ExpertFichierCOR<S,T>{
public:
/**
     * @brief Constructeur de la classe ExpertFichierJSON.
     * @param suivant Pointeur vers le maillon suivant dans la chaîne de responsabilité.
     *
     * Ce constructeur initialise l'expert et lui associe un maillon suivant dans la chaîne de responsabilité.
     * Il permet de créer une instance de `ExpertFichierJSON` avec la possibilité de déléguer le traitement à un autre expert si nécessaire.
     */
    ExpertFichierJSON(ExpertFichierCOR<S,T> * suivant): ExpertFichierCOR<S,T>(suivant) {}

    /**
     * @brief Vérifie si le maillon actuel peut traiter le fichier spécifié.
     * @param s Nom du fichier à traiter.
     * @return true si le maillon peut traiter le fichier JSON, sinon false.
     */
    virtual bool saitTraiter(const string &s) const override {
        size_t dernier = s.find_last_of('.');
        if (dernier != string::npos && dernier + 1 < s.length()) {
            string extension = s.substr(dernier + 1);
            if (extension == "json") {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Vérifie si le maillon actuel peut traiter le fichier spécifié.
     *
     * Cette méthode permet de vérifier si le fichier donné peut être traité par cet expert en vérifiant son extension.
     * Dans ce cas, le maillon peut traiter les fichiers ayant l'extension `.json`.
     *
     * @param s Nom du fichier à traiter.
     * @return `true` si le fichier peut être traité (fichier JSON), sinon `false`.
     */
    virtual Visitor_Fichier<S,T>* Traiter() const override {
        Visitor_Fichier<S,T> * f = new JSON<S,T>();
        return f;
    }
};


#endif //PROJET_ACL_EXPERTFICHIERJSON_H

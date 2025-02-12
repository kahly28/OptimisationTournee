#ifndef PROJETPPIL_FICHIER_H
#define PROJETPPIL_FICHIER_H

#include <string>
#include "COR_FICHIER/ExpertFichierCOR.h"
#include "ExpertFichierJSON.h"
template <typename S, typename T>
/**
 * @brief Classe représentant un gestionnaire de fichiers.
 *
 * La classe `Fichier` permet de charger et sauvegarder des fichiers contenant des informations géométriques,
 * telles que des villes et des camions, dans un format structuré. Elle utilise un modèle de chaîne de responsabilité
 * pour le chargement des fichiers et veille à ce que les types des données soient corrects.
 *
 * @details Sauvegarde dans le dossier Projet/Fichier. Le chargement ne prend en compte que les fichiers
 *          se trouvant dans ce dossier.
 * @details Le type des sommets doit être une instance de `Ville` et le type des arêtes doit être un nombre.
 * @warning Le chargement de groupes contenant d'autres groupes provoquera une erreur, car cette fonctionnalité
 *          n'est pas prise en charge par cette classe.
 *
 * @tparam S Type représentant les poids des arêtes (doit être un type numérique).
 * @tparam T Type représentant les sommets du graphe (doit être de type `Ville`).
 */
class Fichier {
    // Vérification que le type T est Ville et que le type S est un nombre
    static_assert(std::is_same<T, Ville>::value, "Erreur : le type du sommet doit être une Ville !");
    static_assert(std::is_arithmetic<S>::value, "Erreur : le type de l'arete doit être un un nombre  !");
private:
    ExpertFichierCOR<S,T> * e; // Gestionnaire de la chaîne de responsabilité pour les fichiers

public:
    /**
     * @brief Constructeur de la classe Fichier.
     *
     * Le constructeur initialise la chaîne de responsabilité pour le traitement des fichiers, en lui passant
     * un gestionnaire d'experts.
     *
     * @param e Un objet de type `ExpertFichierCOR<S, T>` qui gère le traitement des fichiers.
     */
    Fichier(ExpertFichierCOR<S,T> * e){
        this->e=e;
    }

    /**
     * @brief Charge un fichier contenant des formes géométriques.
     *
     * Cette méthode charge un fichier spécifié, analyse son contenu et crée des objets géométriques comme des
     * camions en fonction des données du fichier. Elle utilise un visiteur pour charger les informations.
     *
     * @param nomFichier Le nom du fichier à charger, situé dans le répertoire `Projet/Fichier`.
     * @param nbCamion Le nombre de camions à charger depuis le fichier.
     *
     * @return Un vecteur contenant les camions chargés depuis le fichier.
     *
     * @throws Erreur Si le fichier ne peut pas être ouvert ou s'il y a un problème lors du chargement.
     */
    vector<Camion<S,T> *>ChargerFichier(const string& nomFichier,int nbCamion){
        try{
            Visitor_Fichier<S,T> * v=e->resoudre(nomFichier);
            return v->visiteChargement(nomFichier,nbCamion);
        } catch ( Erreur& erreur) {
            cerr<<erreur;
        }

    }
};

#endif //PROJETPPIL_FICHIER_H

//
// Created by Enzo-pc on 27/12/2024.
//

#ifndef PROJET_ACL_JSON_H
#define PROJET_ACL_JSON_H


#include <sstream>
#include "Visitor_Fichier.h"
#include "../../ERREUR/Erreur.h"
#include "../../GRAPHE/Ville.h"

template <typename S, typename T>
/**
 * @brief Classe représentant un visiteur pour charger des fichiers JSON contenant des données géographiques.
 *
 * La classe `JSON` implémente un visiteur qui permet de charger un fichier JSON contenant des informations sur
 * des villes et de les répartir entre un nombre donné de camions. Le fichier JSON doit contenir des données sur
 * les villes (nom, latitude, longitude), et chaque camion recevra un certain nombre de villes.
 *
 * @tparam S Type représentant les poids des arêtes (doit être un type numérique).
 * @tparam T Type représentant les sommets du graphe (doit être de type `Ville`).
 */
class JSON : public Visitor_Fichier<S,T>{
private:
    /**
     * @brief Fonction interne pour traiter le fichier JSON et répartir les villes entre les camions.
     *
     * Cette fonction ouvre un fichier JSON, extrait les données des villes, et répartit les villes entre
     * un nombre donné de camions, en veillant à ce que chaque camion reçoive un nombre équilibré de villes.
     *
     * @param fichier Le fichier JSON à charger.
     * @param nbCamion Le nombre de camions à charger et à assigner des villes.
     *
     * @return Un vecteur contenant les camions avec les villes distribuées.
     *
     * @throws Erreur Si le fichier ne peut pas être ouvert ou si la distribution des villes échoue.
     */
    vector<Camion<S,T> *> LogiqueFichier(ifstream &fichier, int nbCamion) {
        vector<Camion<S,T> *> Camions;
        vector<Ville*> villes;

        // Ouvrir le fichier
        if (!fichier.is_open()) {
            throw new Erreur("Impossible d'ouvrir le fichier JSON : ");
        }

        // Lire tout le fichier dans une chaîne
        stringstream buffer;
        buffer << fichier.rdbuf();
        std::string contenu = buffer.str();

        // Parcourir le contenu du fichier JSON
        size_t pos = 0;
        while ((pos = contenu.find("{", pos)) != std::string::npos) {
            // Extraire les champs
            size_t debutVille = contenu.find("\"ville\":", pos);
            size_t debutLatitude = contenu.find("\"latitude\":", pos);
            size_t debutLongitude = contenu.find("\"longitude\":", pos);

            if (debutVille == std::string::npos || debutLatitude == std::string::npos || debutLongitude == std::string::npos) {
                break; // Pas d'autres objets valides
            }

            // Récupérer le nom de la ville
            debutVille = contenu.find("\"", debutVille + 8) + 1;
            size_t finVille = contenu.find("\"", debutVille);
            std::string nomVille = contenu.substr(debutVille, finVille - debutVille);

            // Récupérer la latitude
            debutLatitude = contenu.find(":", debutLatitude) + 1;
            size_t finLatitude = contenu.find(",", debutLatitude);
            double latitude = std::stod(contenu.substr(debutLatitude, finLatitude - debutLatitude));

            // Récupérer la longitude
            debutLongitude = contenu.find(":", debutLongitude) + 1;
            size_t finLongitude = contenu.find("}", debutLongitude);
            double longitude = std::stod(contenu.substr(debutLongitude, finLongitude - debutLongitude));

            // Créer un nouvel objet Ville et l'ajouter au vecteur
            Ville *v = new Ville(nomVille, longitude, latitude);
            villes.push_back(v);

            // Avancer la position pour chercher le prochain objet
            pos = finLongitude;
        }

        // S'assurer qu'il y a suffisamment de villes pour les camions
        if (villes.size() < nbCamion) {
            throw Erreur("Il n'y a pas assez de villes pour les camions.");
        }

        // Diviser les villes entre les camions
        int idxVille = 0;
        for (int i = 0; i < nbCamion; ++i) {
            vector<Ville> villesCamion;
            // Ajouter les villes au camion i (répartir les villes)
            for (int j = 0; j < villes.size() / nbCamion; ++j) {
                if (idxVille < villes.size()) {
                    villesCamion.push_back(*villes[idxVille]);
                    idxVille++;
                }
            }

            // Si ce n'est pas un camion ayant des villes supplémentaires, assigner les restes
            if (i < villes.size() % nbCamion) {
                villesCamion.push_back(*villes[idxVille]);
                idxVille++;
            }

            // Créer un camion avec les villes distribuées
            Camions.push_back(new Camion<S, T>(villesCamion));
        }

        return Camions;
    }

public:
    /**
     * @brief Charge les camions à partir d'un fichier JSON.
     *
     * Cette méthode permet de charger un fichier JSON situé dans le dossier Projet/Fichier, d'extraire les données
     * des villes et de répartir ces villes entre un nombre de camions spécifié.
     *
     * @param nomFichier Le nom du fichier à charger.
     * @param nbCamion Le nombre de camions à charger et à assigner des villes.
     *
     * @return Un vecteur contenant les camions avec les villes distribuées.
     *
     * @throws Erreur Si le fichier ne peut pas être ouvert ou si une erreur survient lors du chargement.
     */
    vector<Camion<S,T> *> visiteChargement(const string &nomFichier,int nbCamion) {
        string chemin = R"(..\..\Fichier\)";
        chemin = chemin + nomFichier;
        ifstream f(chemin);
        if (f) {
                return LogiqueFichier(f,nbCamion);
        } else {
            throw Erreur("Erreur d'ouverture");
        }
    }

};


#endif //PROJET_ACL_JSON_H

#ifndef PROJETPPIL_VISITOR_FICHIER_H
#define PROJETPPIL_VISITOR_FICHIER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../GRAPHE/Ville.h"
#include "../../OUTILS/Camion.h"

using namespace std;
template <typename S, typename T>

/**
 * @brief Interface pour un visiteur de fichier.
 *
 * Cette classe définit l'interface d'un visiteur pour le chargement de fichiers contenant des informations géométriques.
 * Le visiteur peut être utilisé pour charger des données depuis différents formats de fichiers (par exemple JSON, XML, etc.).
 * Elle permet de récupérer des informations sur les camions et les villes à partir d'un fichier donné.
 *
 * @tparam S Type représentant les poids des arêtes (doit être un type numérique).
 * @tparam T Type représentant les sommets du graphe (doit être de type `Ville`).
 */
class Visitor_Fichier {
    vector<Camion<S,T> *> Camions;

public:
    /**
     * @brief Charge les formes géométriques à partir d'un fichier.
     *
     * Cette méthode doit être implémentée par chaque classe dérivée pour spécifier comment charger les données
     * depuis un fichier dans un format particulier.
     * Elle retourne un vecteur de camions représentant les formes géométriques chargées.
     *
     * @param nomFichier Nom du fichier à charger.
     * @param nbCamion Le nombre de camions à charger et à assigner des villes.
     *
     * @return Un vecteur contenant les camions avec les villes distribuées.
     *
     * @throws Erreur Si une erreur survient lors du chargement du fichier.
     */
    virtual vector<Camion<S,T> *> visiteChargement(const string &nomFichier,int nbCamion) = 0;
};

#endif //PROJETPPIL_VISITOR_FICHIER_H
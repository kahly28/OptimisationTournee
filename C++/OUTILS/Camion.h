//
// Created by Enzo-pc on 03/01/2025.
//

#ifndef PROJET_ACL_CAMION_H
#define PROJET_ACL_CAMION_H

#include <vector>
#include <ostream>
#include "../GRAPHE/Ville.h"
#include "../GRAPHE/Graphe.h"

using namespace std;
template <typename S, typename T>

/**
 * @brief Classe représentant un camion, avec un graphe complet de villes.
 *
 * La classe `Camion` gère un ensemble de villes et leur organisation sous forme de graphe. Elle est capable de
 * construire un graphe complet entre les villes, calculer un trajet optimal à l'aide de l'algorithme de Kruskal,
 * et d'afficher les informations du graphe associé.
 *
 * @tparam S Type représentant les poids des arêtes (doit être un type numérique).
 * @tparam T Type représentant les sommets du graphe (doit être de type `Ville`).
 */
class Camion {
    // Vérification que le type T est Ville et que le type S est un nombre
    static_assert(std::is_same<T, Ville>::value, "Erreur : le type du sommet doit être une Ville !");
    static_assert(std::is_arithmetic<S>::value, "Erreur : le type de l'arete doit être un un nombre  !");
    vector<Ville> LVille; // Liste des villes desservies par le camion
    Graphe<S,T> graphe; // Graphe représentant les connexions entre les villes

    /**
     * @brief Construit un graphe complet à partir des villes.
     *
     * La méthode crée les sommets pour chaque ville et ajoute des arêtes entre toutes les paires de villes
     * pour rendre le graphe complet. Les arêtes sont créées en utilisant la distance géodésique entre les villes.
     */
    void construireGrapheComplet(){
        //On crée les sommets
        for(Ville  elt: LVille){
            graphe.creeSommet( elt);
        }

        // Créer des arêtes pour rendre le graphe complet
        const auto& sommets = graphe.getLSommets();
        for (size_t i = 0; i < sommets.size(); ++i) {
            for (size_t j = i + 1; j < sommets.size(); ++j) {
                Sommet<Ville>* sommet1 = sommets[i];
                Sommet<Ville>* sommet2 = sommets[j];

                // Créer l'arête entre les deux sommets si elle n'existe pas déjà
                if(graphe.getAreteParSommets(sommet1,sommet2)== nullptr){
                    graphe.creeArete(sommet1->v.distancesGeodesique(sommet2->v), sommet1, sommet2);
                }
            }
        }
    }


public:
    /**
    * @brief Constructeur de la classe `Camion`.
    *
    * Le constructeur prend une liste de villes et construit le graphe complet associé.
    *
    * @param lVille Liste des villes desservies par le camion.
    */
    explicit Camion(const vector<Ville>& lVille) : LVille(lVille) {
        construireGrapheComplet();
    }

    /**
     * @brief Récupère la liste des villes desservies par le camion.
     *
     * @return Une référence constante vers la liste des villes.
     */
    const vector<Ville> &getLVille() const {
        return LVille;
    }

    /**
     * @brief Récupère le graphe associé au camion.
     *
     * @return Une référence constante vers le graphe du camion.
     */
    const Graphe<S, T> &getGraphe() const {
        return graphe;
    }

    /**
     * @brief Calcule le trajet optimal entre les villes en utilisant l'algorithme de Kruskal.
     *
     * Cette méthode calcule le trajet optimal pour desservir toutes les villes en minimisant la distance totale
     * en utilisant l'algorithme de Kruskal pour trouver un arbre couvrant minimal.
     *
     * @return Un vecteur d'arêtes représentant le trajet optimal.
     */
    vector<Arrete<S, T> *> CalculerTrajet(){
        return graphe.algoKruskal();

    }

    /**
     * @brief Surcharge de l'opérateur d'affichage pour la classe `Camion`.
     *
     * Cette méthode permet d'afficher les informations du camion, incluant le graphe associé.
     *
     * @param os Le flux de sortie dans lequel les informations seront affichées.
     * @param camion Le camion dont les informations doivent être affichées.
     * @return Le flux de sortie modifié.
     */
    friend ostream &operator<<(ostream &os, const Camion &camion) {

        os<<"graphe correspondant : \n" << camion.graphe;
        return os;
    }
};





#endif //PROJET_ACL_CAMION_H

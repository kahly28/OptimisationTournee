#ifndef PROJETPPIL_GRAPHE_H
#define PROJETPPIL_GRAPHE_H

#include <vector>
#include <ostream>
#include <algorithm>
#include "Sommet.h"
#include "Arrete.h"
#include "UnionFind.h"

using namespace std;

template <typename S, typename T>

/**
 * @class Graphe
 * @brief Représente un graphe générique composé de sommets et d'arêtes.
 *
 * Cette classe fournit une implémentation de base pour un graphe, permettant
 * de gérer des sommets, des arêtes, et d'exécuter des algorithmes de graphes tels que celui de Kruskal.
 * Les sommets et les arêtes sont modélisés via des pointeurs pour permettre une gestion dynamique.
 *
 * @tparam S Type de la valeur associée aux arêtes.
 * @tparam T Type de la valeur associée aux sommets.
 */
class Graphe {
private:
    vector<Sommet<T>*> lSommets; ///< Liste des sommets du graphe.
    vector<Arrete<S, T>*> lAretes; ///< Liste des arêtes du graphe.
    int prochaineClef; ///< Clé primaire pour identifier le prochain élément ajouté au graphe.

    /**
     * @brief Copie le contenu d'un autre graphe dans l'instance actuelle.
     *
     * Cette méthode crée de nouvelles instances pour les sommets et les arêtes.
     *
     * @param autre Graphe à copier.
     */
    void copier(const Graphe<S, T>& autre) {
        lSommets.clear();
        for (const auto& s : autre.lSommets) {
            lSommets.push_back(new Sommet<T>(*s));
        }
        lAretes.clear();
        for (const auto& a : autre.lAretes) {
            lAretes.push_back(new Arrete<S, T>(*a));
        }
        prochaineClef = autre.prochaineClef;
    }

    /**
     * @brief Libère les ressources allouées pour les sommets et les arêtes.
     */
    void liberer() {
        for (auto& s : lSommets) {
            delete s;
        }
        lSommets.clear();
        for (auto& a : lAretes) {
            delete a;
        }
        lAretes.clear();
    }

public:
    /**
     * @brief Constructeur par défaut.
     *
     * Initialise un graphe vide.
     */
    Graphe() = default;

    /**
     * @brief Constructeur par copie.
     *
     * Copie les sommets et les arêtes d'un autre graphe.
     *
     * @param copie Graphe à copier.
     */
    Graphe(const Graphe<S, T>& copie) : prochaineClef(0) {
        copier(copie);
    }

    /**
     * @brief Destructeur.
     *
     * Libère la mémoire allouée pour les sommets et les arêtes.
     */
    virtual ~Graphe() {
        liberer();
    }

    /**
     * @brief Retourne la liste des sommets du graphe.
     *
     * @return Référence constante vers le vecteur des sommets.
     */
    const vector<Sommet<T> *> &getLSommets() const {
        return lSommets;
    }

    /**
     * @brief Retourne la liste des arêtes du graphe.
     *
     * @return Référence constante vers le vecteur des arêtes.
     */
    const vector<Arrete<S, T> *> &getLAretes() const {
        return lAretes;
    }

    /**
     * @brief Crée un sommet isolé et l'ajoute au graphe.
     *
     * @param info Valeur associée au sommet.
     * @return Pointeur vers le nouveau sommet créé.
     */
    Sommet<T> * creeSommet(const T & info) {
        int clef = nombreSommets(); // Clé basée sur la taille actuelle
        Sommet<T>* nouveauSommet = new Sommet<T>(clef, info);
        this->lSommets.push_back(nouveauSommet); // Ajout au conteneur des sommets
        return nouveauSommet;
    }

    /**
     * @brief Crée une arête reliant deux sommets et l'ajoute au graphe.
     *
     * @param info Valeur associée à l'arête.
     * @param debut Pointeur vers le sommet de début.
     * @param fin Pointeur vers le sommet de fin.
     * @return Pointeur vers la nouvelle arête créée.
     * @throws std::invalid_argument Si l'un des sommets est nul.
     *
     */
    Arrete<S, T>* creeArete(const S& info, Sommet<T>* debut, Sommet<T>* fin) {
        if (!debut || !fin) {
            throw std::invalid_argument("Les sommets ne peuvent pas être nuls.");
        }

        int clef = nombreAretes(); // Clé basée sur la taille actuelle
        Arrete<S,T>* nouveauArete = new Arrete<S,T>(clef, info, debut, fin);
        this->lAretes.push_back(nouveauArete); // Ajout au conteneur des sommets
        return nouveauArete;
    }

    /**
     * @brief Retourne le nombre de sommets dans le graphe.
     *
     * @return Nombre de sommets.
     */
    int nombreSommets() const {
        return lSommets.size();
    }

    /**
     * @brief Retourne le nombre d'arêtes dans le graphe.
     *
     * @return Nombre d'arêtes.
     */
    int nombreAretes() const {
        return lAretes.size();
    }

    /**
     * @brief Retourne les adjacences pour un sommet donné.
     *
     * @param sommet Sommet pour lequel chercher les adjacences.
     * @return Vecteur de paires contenant les sommets voisins et les arêtes correspondantes.
     */
    vector<pair<Sommet<T>*, Arrete<S, T>*>> adjacences(const Sommet<T>* sommet) const {
        vector<pair<Sommet<T>*, Arrete<S, T>*>> result;
        for (const auto& arete : lAretes) {
            if (arete->debut == sommet) {
                result.emplace_back(arete->fin, arete);
            } else if (arete->fin == sommet) {
                result.emplace_back(arete->debut, arete);
            }
        }
        return result;
    }

    /**
     * @brief Retourne les arêtes adjacentes à un sommet donné.
     *
     * @param sommet Sommet pour lequel chercher les arêtes adjacentes.
     * @return Vecteur des arêtes adjacentes.
     */
    vector<Arrete<S, T>*> aretesAdjacentes(const Sommet<T>* sommet) const {
        std::vector<Arrete<S, T>*> result;
        for (const auto& adj : adjacences(sommet)) {
            result.push_back(adj.second);
        }
        return result;
    }

    /**
     * @brief Retourne les voisins d'un sommet donné.
     *
     * @param sommet Sommet pour lequel chercher les voisins.
     * @return Vecteur des sommets voisins.
     */
    vector<Sommet<T>*> voisins(const Sommet<T>* sommet) const {
        vector<Sommet<T>*> result;
        for (const auto& adj : adjacences(sommet)) {
            result.push_back(adj.first);
        }
        return result;
    }

    /**
     * @brief Retourne l'arête reliant deux sommets, s'il en existe une.
     *
     * @param s1 Premier sommet.
     * @param s2 Second sommet.
     * @return Pointeur vers l'arête, ou `nullptr` si aucune arête ne relie les deux sommets.
     */
    Arrete<S, T>* getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const {
        for (const auto& arete : lAretes) {
            if (arete->estEgal(s1, s2)) {
                return arete;
            }
        }
        return nullptr;
    }

    /**
     * @brief Exécute l'algorithme de Kruskal pour trouver l'arbre couvrant minimal.
     *
     * @return Vecteur des arêtes de l'arbre couvrant minimal.
     */
    vector<Arrete<S, T>*> algoKruskal() {
        // Résultat final : un vecteur d'arêtes de l'arbre couvrant minimal
        vector<Arrete<S, T>*> mst;

        // Tri des arêtes par poids (valeur "v" dans votre implémentation)
        trierAretesParV();

        // Initialisation de la structure Union-Find
        UnionFind uf(nombreSommets());

        // Parcours des arêtes triées
        for (const auto& arete : lAretes) {
            int u = arete->debut->clef;
            int v = arete->fin->clef;

            // Si les deux sommets de l'arête ne sont pas dans le même ensemble
            if (!uf.estDansLeMemeEnsemble(u, v)) {
                // Ajouter l'arête à l'arbre couvrant minimal
                mst.push_back(arete);

                // Union des deux ensembles
                uf.unionSets(u, v);
            }

            // Arrêter si on a atteint n-1 arêtes (n = nombre de sommets)
            if (mst.size() == nombreSommets() - 1) {
                break;
            }
        }

        return mst;
    }

    /**
     * @brief Trie les arêtes par leur poids (valeur `v`) dans l'ordre croissant.
     */
    void trierAretesParV() {
        sort(lAretes.begin(), lAretes.end(), [](const Arrete<S, T>* a, const Arrete<S, T>* b) {
            return a->v < b->v;
        });
    }

    /**
     * @brief Calcule le poids total des arêtes du graphe.
     *
     * @return Poids total sous la forme d'une valeur de type `S`.
     */
    S poidsTotal() const {
        S total = S(); // Initialisation avec la valeur par défaut de S
        for (const auto& arete : lAretes) {
            total += arete->v; // Ajouter le poids (valeur v) de chaque arête
        }
        return total;
    }

    /**
     * @brief Surcharge de l'opérateur d'affectation.
     *
     * @param autre Graphe à copier.
     * @return Référence vers l'instance actuelle après copie.
     */
    Graphe<S, T>& operator = (const Graphe<S, T>& autre) {
        if (this != &autre) {
            liberer();
            copier(autre);
        }
        return *this;
    }

    /**
     * @brief Convertit le graphe en une chaîne de caractères.
     *
     * @return Une chaîne de caractères décrivant le graphe.
     */
    operator string() const {
        ostringstream oss;
        oss << "Graphe[\n";
        oss << "\tListe des sommets : \n";
        for (size_t i = 0; i < nombreSommets(); ++i) {
            oss << "\t\t" << lSommets[i]->operator string();
        }
        oss << "\n \tListe des arretes : \n";
        for (size_t i = 0; i < nombreAretes(); ++i) {
            oss << "\t\t" << lAretes[i]->operator string();
        }
        oss << "]\n";
        return oss.str();
    }

    /**
      * @brief Surcharge de l'opérateur `<<` pour écrire le graphe dans un flux.
      *
      * @param os Flux de sortie.
      * @param graphe Graphe à écrire dans le flux.
      * @return Référence vers le flux modifié.
      */
    friend ostream &operator<<(ostream &os, const Graphe &graphe) {
        os << graphe.operator string();
        return os;
    }

};

/**
 * @brief Surcharge de l'opérateur `<<` pour écrire le graphe dans un flux.
 *
 * @param os Flux de sortie.
 * @param graphe Graphe à écrire dans le flux.
 * @return Référence vers le flux modifié.
 */
template <typename T>
ostream& operator<<(ostream& os, const vector<Sommet<T>*>& sommets) {
    os << "[";
    for (size_t i = 0; i < sommets.size(); ++i) {
        os << (i ? ", " : "") << *sommets[i];
    }
    os << "]";
    return os;
}

/**
 * @brief Surcharge de l'opérateur `<<` pour écrire le graphe dans un flux.
 *
 * @param os Flux de sortie.
 * @param graphe Graphe à écrire dans le flux.
 * @return Référence vers le flux modifié.
 */
template <typename S, typename T>
ostream& operator<<(ostream& os, const vector<Arrete<S, T>*>& aretes) {
    os << "[";
    for (size_t i = 0; i < aretes.size(); ++i) {
        os << (i ? ", " : "") << *aretes[i];
    }
    os << "]";
    return os;
}
#endif //PROJETPPIL_GRAPHE_H

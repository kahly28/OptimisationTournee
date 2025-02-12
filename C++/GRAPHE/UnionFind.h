#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>
using namespace std;
/**
 * @class UnionFind
 * @brief Implémentation de la structure de données Union-Find (ou Disjoint Set Union - DSU).
 *
 * Cette classe permet de gérer un ensemble d'éléments en réalisant des unions entre eux et en
 * vérifiant si deux éléments appartiennent au même ensemble. Elle utilise deux optimisations
 * : la compression de chemin et l'union par rang, pour garantir une efficacité optimale dans les opérations.
 */
class UnionFind {
private:
    vector<int> parent;  ///< Tableau représentant les parents de chaque élément.
    vector<int> rank;    ///< Tableau représentant le "rang" (ou profondeur) de chaque arbre.

public:
    /**
     * @brief Constructeur.
     *
     * Initialise une structure UnionFind pour n éléments, chaque élément étant initialement son propre parent.
     * Le rang de chaque élément est initialisé à zéro.
     *
     * @param n Nombre d'éléments dans l'ensemble.
     */
    explicit UnionFind(int n) {
        parent.resize(n);    // Redimensionne le tableau parent pour contenir n éléments
        rank.resize(n, 0);   // Initialise tous les rangs à 0
        for (int i = 0; i < n; ++i) {
            parent[i] = i;  // Chaque élément est son propre parent
            parent[i] = i;  // Chaque élément est son propre parent (chaque élément est dans un ensemble distinct)
        }
    }

    /**
     * @brief Trouve le représentant de l'ensemble contenant l'élément x.
     *
     * Cette méthode utilise la compression de chemin pour améliorer les performances en
     * raccourcissant les chemins dans l'arbre des parents.
     *
     * @param x L'élément dont on veut trouver le représentant de l'ensemble.
     * @return Le parent (représentant) de l'ensemble auquel appartient x.
     */
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Compression de chemin
        }
        return parent[x];
    }

    /**
     * @brief Effectue l'union de deux ensembles, ceux contenant les éléments x et y.
     *
     * Cette méthode utilise l'union par rang pour équilibrer les arbres, de manière à ce que
     * l'arbre de profondeur minimale soit toujours choisi comme racine pour éviter des arbres trop profonds.
     *
     * @param x L'un des éléments de l'ensemble à unionner.
     * @param y L'autre élément de l'ensemble à unionner.
     */

    void unionSets(int x, int y) {
        int rootX = find(x);                  // Trouve le représentant de l'ensemble contenant x
        int rootY = find(y);               // Trouve le représentant de l'ensemble contenant y

        if (rootX != rootY) {                 // Si les représentants sont différents, on effectue l'union
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;        // Attache l'arbre de rootX sous rootY
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;       // Attache l'arbre de rootY sous rootX
            } else {
                parent[rootY] = rootX;      // Si les rangs sont égaux, on fait de rootX la racine
                rank[rootX]++;              // On augmente le rang de rootX
            }
        }
    }

    /**
     * @brief Vérifie si deux éléments sont dans le même ensemble.
     *
     * Cette méthode vérifie si les représentants des deux éléments sont identiques, ce qui
     * indique qu'ils font partie du même ensemble.
     *
     * @param x Le premier élément à vérifier.
     * @param y Le second élément à vérifier.
     * @return true Si les éléments x et y appartiennent au même ensemble, sinon false.
     */
    bool estDansLeMemeEnsemble(int x, int y) {
        return find(x) == find(y); // Si les représentants de x et y sont identiques, alors ils sont dans le même ensemble
    }
};

#endif // UNION_FIND_H

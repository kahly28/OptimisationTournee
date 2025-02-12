//
// Created by jules on 15/02/2024.
//

#ifndef PROJETPPIL_MATRICE_H
#define PROJETPPIL_MATRICE_H

#include <vector>
#include <iostream>
#include "Vecteur2D.h"

using namespace std;

/**
 * @brief Class representing a matrix.
 */
class Matrice {
private:
    vector<vector<int>> val; /**< 2D vector to store the matrix values */
    int lignes; /**< Number of rows in the matrix */
    int colonnes; /**< Number of columns in the matrix */

public:
    /**
     * @brief Constructor to initialize a matrix with specified number of rows and columns.
     *
     * @param lignes Number of rows.
     * @param colonnes Number of columns.
     */
    Matrice(const int & lignes = 0, const int & colonnes = 0) : lignes(lignes), colonnes(colonnes) {
        // Initializing the matrix with default values, for example, 0
        val.resize(lignes, vector<int>(colonnes, 0));
    }

    /**
     * @brief Accessor to get the number of rows of the matrix.
     *
     * @return int Number of rows.
     */
    int getLignes() const {
        return lignes;
    }

    /**
     * @brief Accessor to get the number of columns of the matrix.
     *
     * @return int Number of columns.
     */
    int getColonnes() const {
        return colonnes;
    }

    /**
     * @brief Check if the matrix is empty.
     *
     * @return true If the matrix is empty.
     * @return false Otherwise.
     */
    bool estVide() const {
        return (lignes == 0 && colonnes == 0);
    }

    /**
     * @brief Function to access and modify the elements of the matrix.
     *
     * @param i Row index.
     * @param j Column index.
     * @return int& Reference to the element at the specified row and column.
     */
    int& operator()(int i, int j) {
        if (i < 0 || i >= lignes || j < 0 || j >= colonnes) {
            throw out_of_range("Indice hors limites");
        }
        return val[i][j];
    }

    /**
     * @brief Assignment operator to copy the contents of one matrix to another.
     *
     * @param o Matrix to copy from.
     * @return Matrice& Reference to the modified matrix.
     */
    Matrice& operator=(const Matrice& o) {
        if (this != &o) { // Check if the matrices are different
            lignes = o.lignes;
            colonnes = o.colonnes;
            val = o.val; // Copy the data from the other matrix to the current matrix
        }
        return *this;
    }

    /**
     * @brief Matrix multiplication operator.
     *
     * @param M1 Matrix to multiply with.
     * @return Matrice Resulting matrix after multiplication.
     */
    Matrice operator*(const Matrice &M1) const {
        if(this->colonnes != M1.lignes) {
            throw invalid_argument("Operation impossible : Colonnes de M1 different de lignes de M2");
        }
        Matrice res(M1.colonnes, this->lignes);
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < M1.colonnes; ++j) {
                res(i, j) = 0;
                for (int k = 0; k < colonnes; ++k) {
                    res(i, j) += val[i][k] * M1.val[k][j];
                }
            }
        }
        return res;
    }

    /**
     * @brief Matrix multiplication operator with a vector.
     *
     * @param V Vector to multiply with.
     * @return Vecteur2D Resulting vector after multiplication.
     */
    Vecteur2D operator*(const Vecteur2D &V) const {
        if(this->colonnes != 2) {
            throw invalid_argument("Nombre de colonnes de la matrice différent de 2 : Calcul impossible");
        }
        Vecteur2D res(V.x * this->val[0][0] + V.y * this->val[0][1], V.x * this->val[1][0] + V.y * this->val[1][1]);
        return res;
    }

    /**
     * @brief Scalar multiplication operator with a matrix.
     *
     * @param x Scalar value to multiply with.
     * @return Matrice Resulting matrix after scalar multiplication.
     */
    Matrice operator*(const double x) const {
        Matrice res(lignes, colonnes);
        for(int i = 0 ; i < this->lignes ; i++) {
            for(int j = 0 ; j < this->colonnes ; j++) {
                res.val[i][j] = this->val[i][j] * x;
            }
        }
        return res;
    }

    /**
     * @brief Function to display the matrix.
     */
    void afficher() const {
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                cout << val[i][j] << " ";
            }
            cout << endl;
        }
    }
};

#endif //PROJETPPIL_MATRICE_H

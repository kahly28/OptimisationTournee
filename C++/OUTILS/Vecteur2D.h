//
// Created by jules on 15/02/2024.
//

#ifndef PROJETPPIL_VECTEUR2D_H
#define PROJETPPIL_VECTEUR2D_H

#include <string>
#include <sstream>
#include <ostream>
#include <cmath>

using namespace std;

/**
 * @brief Classe représentant un vecteur 2D.
 */
class Vecteur2D {
public:
    double x, y; ///< Coordonnées du vecteur.

    /**
     * @brief Constructeur par défaut de Vecteur2D.
     * @param x La coordonnée x du vecteur.
     * @param y La coordonnée y du vecteur.
     */
    inline explicit Vecteur2D(const double &x = 0, const double &y = 0) : x(x), y(y) {}

    /**
     * @brief Constructeur de Vecteur2D prenant une chaîne de caractères.
     * @param s La chaîne de caractères représentant les coordonnées du vecteur.
     */
    inline Vecteur2D(const char *s);

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void setX(double x) {
        Vecteur2D::x = x;
    }

    void setY(double y) {
        Vecteur2D::y = y;
    }

    /**
     * @brief Calcule la norme du vecteur.
     * @return La norme du vecteur.
     */
    double norme() const {
        return sqrt(x * x + y * y);
    }


    /**
     * @brief Vérifie si le vecteur est vide (nul).
     * @return true si le vecteur est vide, sinon false.
     */
    bool estVide() const {
        return (x == 0 && y == 0);
    }

    /**
     * @brief Surcharge de l'opérateur d'affectation.
     * @param o Le vecteur à copier.
     * @return Une référence vers le vecteur courant.
     */
    inline Vecteur2D &operator=(const Vecteur2D &o) {
        if (this != &o) {
            x = o.x;
            y = o.y;
        }
        return *this;
    }

    /**
     * @brief Surcharge de l'opérateur d'addition.
     * @param u Le vecteur à ajouter.
     * @return Le résultat de l'addition des deux vecteurs.
     */
    inline const Vecteur2D operator+(const Vecteur2D &u) const {
        return Vecteur2D(x + u.x, y + u.y);
    }

    /**
     * @brief Surcharge de l'opérateur de soustraction.
     * @param v Le vecteur à soustraire.
     * @return Le résultat de la soustraction des deux vecteurs.
     */
    inline const Vecteur2D operator-(const Vecteur2D &v) const {
        return Vecteur2D(x - v.x, y - v.y);
    }

    /**
     * @brief Surcharge de l'opérateur de multiplication par un scalaire.
     * @param a Le scalaire.
     * @return Le résultat de la multiplication du vecteur par le scalaire.
     */
    inline const Vecteur2D operator*(const double &a) const {
        return Vecteur2D(x * a, y * a);
    }

    /**
     * @brief Surcharge de l'opérateur de produit scalaire.
     * @param V Le vecteur avec lequel effectuer le produit scalaire.
     * @return Le résultat du produit scalaire entre les deux vecteurs.
     */
    inline const Vecteur2D operator*(Vecteur2D V) const {
        return Vecteur2D(x * V.x, y * V.y);
    }

    /**
     * @brief Surcharge de l'opérateur unaire de négation.
     * @return Le vecteur avec ses coordonnées inversées.
     */
    inline const Vecteur2D operator-() const {
        return Vecteur2D(-x, -y);
    }

    /**
     * @brief Calcule le déterminant entre deux vecteurs.
     * @param V Le vecteur avec lequel calculer le déterminant.
     * @return La valeur du déterminant entre les deux vecteurs.
     */
    const double determinant(const Vecteur2D &V) const {
        float det = (this->x * V.y) - (this->y * V.x);
        return det;
    }

    /**
     * @brief Conversion du vecteur en chaîne de caractères.
     * @return La représentation du vecteur sous forme de chaîne de caractères.
     */
    operator string() const {
        ostringstream os;
        os << x << "," << y;
        return os.str();
    }

    /**
     * @brief Convertit une valeur en degrés en radians.
     *
     * Cette méthode prend un angle en degrés et le convertit en radians.
     * Elle est utilisée pour effectuer des calculs géodésiques.
     *
     * @param degre L'angle en degrés à convertir.
     * @return L'angle en radians.
     */
    double convertirEnRadians(double degre){
        return degre * M_PI / 180.0;
    }

    /**
     * @brief Calcule la distance géodésique entre deux points sur la surface de la Terre.
     *
     * Cette méthode calcule la distance géodésique (ou distance orthodromique) entre le point représenté par l'objet courant
     * (dont les coordonnées sont données par `x` et `y`) et un autre point donné par un objet `Vecteur2D`
     * (avec ses propres coordonnées `x` et `y`).
     *
     * La distance géodésique est calculée en utilisant la formule de Haversine, et retourne la distance en kilomètres.
     * Le rayon de la Terre utilisé dans ce calcul est de 6371 kilomètres.
     *
     * @param v Un objet `Vecteur2D` représentant le second point de coordonnées (latitude, longitude).
     * @return La distance géodésique en kilomètres entre les deux points.
     *
     * @warning Les coordonnées doivent être en degrés et la conversion en radians est effectuée automatiquement.
     */
    double distanceGeodesique(const Vecteur2D& v){
        int RAYON_TERRE = 6371;
        double phi1 = convertirEnRadians(this->x);
        double lambda1 = convertirEnRadians(this->y);
        double phi2 = convertirEnRadians(v.x);
        double lambda2 = convertirEnRadians(v.y);

        // Différence des longitudes
        double deltaLambda = lambda2 - lambda1;

        // Calcul de l'angle central (Delta sigma)
        double deltaSigma = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(deltaLambda);
        deltaSigma = acos(deltaSigma);

        // Distance géodésique
        return RAYON_TERRE * deltaSigma;
    }

/**
     * @brief Surcharge de l'opérateur de flux de sortie pour l'affichage.
     * @param os Le flux de sortie.
     * @param u Le vecteur à afficher.
     * @return Le flux de sortie contenant la représentation du vecteur.
     */
    friend ostream &operator<<(ostream &os, const Vecteur2D &u) {
        os << (string)u;
        return os;
    }
};

/**
 * @brief Surcharge de l'opérateur de multiplication par un scalaire.
 * @param a Le scalaire.
 * @param u Le vecteur à multiplier.
 * @return Le résultat de la multiplication du vecteur par le scalaire.
 */
inline const Vecteur2D operator*(const double &a, const Vecteur2D &u) { return u * a; }

#endif //PROJETPPIL_VECTEUR2D_H

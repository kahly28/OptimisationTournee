#ifndef PROJETPPIL_VILLE_H
#define PROJETPPIL_VILLE_H

#include <ostream>
#include "../OUTILS/Vecteur2D.h"

using namespace std;

/**
 * @class Ville
 * @brief Représente une ville avec un nom, des coordonnées géographiques, et une quantité de marchandises à livrer.
 *
 * Cette classe encapsule les attributs et méthodes nécessaires pour gérer les informations
 * relatives à une ville dans un contexte logistique.
 */

class Ville {
private:
    string nom; ///< Nom de la ville.
    Vecteur2D coordonees; ///< Coordonnées géographiques de la ville (latitude, longitude).
    double quantiteALivrer; ///< Quantité de marchandises à livrer à cette ville.

public:
    /**
     * @brief Constructeur de la classe Ville.
     *
     * Initialise une ville avec son nom, ses coordonnées géographiques, et une quantité à livrer.
     *
     * @param nom Nom de la ville.
     * @param lattitude Latitude de la ville (doit être entre -90 et 90).
     * @param longitude Longitude de la ville (doit être entre -180 et 180).
     * @param q Quantité de marchandises à livrer (doit être positive ou nulle).
     */

    Ville(const string &nom, const double lattitude, const double longitude, double q) : nom(nom), coordonees(lattitude,longitude), quantiteALivrer(q) {}

    /**
     * @brief Constructeur de la classe Ville (sans la quantité de marchandises).
     *
     * Initialise une ville avec son nom et ses coordonnées géographiques sans spécifier la quantité de marchandises à livrer.
     *
     * @param nom Nom de la ville.
     * @param lattitude Latitude de la ville (doit être entre -90 et 90).
     * @param longitude Longitude de la ville (doit être entre -180 et 180).
     */
    Ville(const string &nom, const double lattitude, const double longitude) : nom(nom), coordonees(lattitude,longitude){}

    // Getters
    /**
     * @brief Obtient la quantité de marchandises à livrer.
     * @return Quantité de marchandises à livrer.
     */
    double getQuantiteALivrer() const {
        return quantiteALivrer;
    }

    /**
     * @brief Obtient le nom de la ville.
     * @return Une référence constante vers le nom de la ville.
     */
    const string &getNom() const {
        return nom;
    }


    /**
     * @brief Obtient les coordonnées géographiques de la ville.
     * @return Une référence constante vers l'objet `Vecteur2D` représentant les coordonnées.
     */
    const Vecteur2D &getCoordonees() const {
        return coordonees;
    }

    // Setters

    /**
     * @brief Définit les coordonnées géographiques de la ville.
     *
     * Vérifie que la latitude est comprise entre -90 et 90, et que la longitude est entre -180 et 180.
     *
     * @param lattitude Nouvelle latitude de la ville.
     * @param longitude Nouvelle longitude de la ville.
     * @throws invalid_argument Si les coordonnées ne respectent pas les bornes spécifiées.
     */
    void setCoordonees(const double lattitude, const double longitude) {
        if (lattitude < -90 || lattitude > 90) {
            throw invalid_argument("La latitude doit être entre -90 et 90.");
        }
        if (longitude < -180 || longitude > 180) {
            throw invalid_argument("La longitude doit être entre -180 et 180.");
        }
        this->coordonees.setX(lattitude);
        this->coordonees.setY(longitude);
    }


    /**
     * @brief Définit la quantité de marchandises à livrer.
     *
     * Vérifie que la quantité n'est pas négative.
     *
     * @param quantiteALivrer Nouvelle quantité de marchandises à livrer.
     * @throws invalid_argument Si la quantité est négative.
     */
    void setQuantiteALivrer(double quantiteALivrer) {
        this->quantiteALivrer = quantiteALivrer;
    }

    /**
     * @brief Définit le nom de la ville.
     * @param nom Nouveau nom de la ville.
     */
    void setNom(const string &nom) {
        this->nom = nom;
    }

    /**
     * @brief Calcule la distance géodésique entre cette ville et une autre.
     *
     * @param v Une autre ville.
     * @return La distance géodésique entre les deux villes.
     */
    double distancesGeodesique(Ville v){
        return this->coordonees.distanceGeodesique(v.coordonees);
    }

    /**
     * @brief Opérateur de conversion en chaîne de caractères.
     *
     * Permet de représenter un objet Ville sous forme de chaîne contenant son nom,
     * sa quantité à livrer, et ses coordonnées géographiques.
     *
     * @return Une chaîne de caractères représentant la ville.
     */
    operator string() const {
        ostringstream oss;
        oss << "Nom de la ville : " << this->nom
            << "\n Quantite a livrer : " << this->quantiteALivrer
            << "\n coordonnees : " << this->coordonees << "\n";
        return oss.str();
    }

    /**
     * @brief Opérateur d'écriture sur un flux de sortie.
     *
     * Permet d'écrire un objet Ville dans un flux (ex : console ou fichier).
     *
     * @param os Flux de sortie.
     * @param ville Objet Ville à écrire.
     * @return Une référence au flux de sortie modifié.
     */
    friend ostream &operator<<(ostream &os, const Ville &ville) {
        os << ville.operator string();
        return os;
    }

};


#endif //PROJETPPIL_VILLE_H

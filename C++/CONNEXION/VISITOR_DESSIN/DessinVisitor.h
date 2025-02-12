#ifndef PROJETPPIL_DESSINVISITOR_H
#define PROJETPPIL_DESSINVISITOR_H

#include <string>
#include "../GRAPHE/Arrete.h"
#include "../GRAPHE/Sommet.h"
//#include "../FENETRE/Fenetre.h"

//class Fenetre; // Déclaration anticipée

using namespace std;
template <typename S, typename T>
class Fenetre;

template <typename S, typename T>

/**
 * @brief Interface pour un visiteur de dessin.
 *
 * Cette classe abstraite définit un ensemble de méthodes pour implémenter un motif Visiteur, permettant de réaliser différentes actions
 * (comme dessiner ou gérer des connexions) sur des éléments d'une fenêtre graphique.
 *
 * Les types `S` et `T` représentent les types génériques des données manipulées par les arêtes et sommets.
 */
class DessinVisitor {
    static_assert(std::is_same<T, Ville>::value, "Erreur : le type du sommet doit être une Ville !");
    static_assert(std::is_arithmetic<S>::value, "Erreur : le type de l'arete doit être un un nombre  !");
public:
    /**
    * @brief Constructeur par défaut.
    */
    DessinVisitor() {}

    /**
     * @brief Méthode virtuelle pure pour gérer la connexion.
     *
     * Cette méthode est appelée lorsqu'une connexion est établie, et elle prend en entrée un message décrivant la connexion.
     *
     * @param msg Message de connexion sous forme de chaîne de caractères.
     */
    virtual void visiteConnecte(string msg) = 0;

    /**
     * @brief Méthode virtuelle pure pour gérer la déconnexion.
     *
     * Cette méthode est appelée lorsqu'une déconnexion est effectuée.
     */
    virtual void visiteDeconnecte() = 0;

    /**
     * @brief Méthode virtuelle pure pour dessiner une arête sur la fenêtre.
     *
     * Cette méthode permet de dessiner une arête dans une fenêtre donnée.
     *
     * @param a Pointeur vers l'arête à dessiner.
     * @param f Pointeur vers la fenêtre où dessiner l'arête.
     */
    virtual void visiteDessiner( Arrete<S,T> * a,Fenetre<S,T> * f ) const = 0;

    /**
     * @brief Méthode virtuelle pure pour dessiner un sommet sur la fenêtre.
     *
     * Cette méthode permet de dessiner un sommet dans une fenêtre donnée.
     *
     * @param A Pointeur vers le sommet à dessiner.
     * @param f Pointeur vers la fenêtre où dessiner le sommet.
     */
    virtual void visiteDessiner( Sommet<T> * A, Fenetre<S,T> * f) const = 0;

    /**
     * @brief Méthode virtuelle pure pour afficher une distance totale sur la fenêtre.
     *
     * Cette méthode permet d'afficher une distance totale calculée dans une fenêtre donnée.
     *
     * @param distTot Distance totale à afficher.
     * @param f Pointeur vers la fenêtre où afficher la distance.
     */
    virtual void visiteDessiner(double distTot,Fenetre<S,T> * f)const =0;
};

#endif //PROJETPPIL_DESSINVISITOR_H
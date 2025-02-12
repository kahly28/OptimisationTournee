//
// Created by jules on 05/02/2024.
//

#ifndef PROJETPPIL_FENETRE_H
#define PROJETPPIL_FENETRE_H

#include <iostream>
#include <sstream>
#include <string>
#include <winsock2.h>
#include <unistd.h>
#include "../../ERREUR/Erreur.h"
#include "../../OUTILS/Matrice.h"
#include "../VISITOR_DESSIN/DessinVisitor.h"
#include "../../GRAPHE/Arrete.h"

/**
 * @brief Classe Fenetre
 *
 * Cette classe représente une fenêtre graphique permettant de dessiner des éléments
 * comme des sommets (villes) et des arêtes (connexions entre les sommets). Elle est
 * intégrée à un système de rendu basé sur le pattern Visitor.
 *
 * @tparam S Type pour les poids ou distances des arêtes.
 * @tparam T Type pour les données associées aux sommets.
 */
template <typename S, typename T>

class Fenetre {
    static_assert(std::is_same<T, Ville>::value, "Erreur : le type du sommet doit être une Ville !");
    static_assert(std::is_arithmetic<S>::value, "Erreur : le type de l'arete doit être un un nombre  !");
private:
    const int MARGE = 50; ///< Marge utilisée pour les calculs d'échelle.
    vector<Arrete<S, T> *> _TabArete; ///< Vecteur stockant des pointeurs vers des formes géométriques.
    Vecteur2D _P1; ///< Point P1.
    Vecteur2D _P2; ///< Point P2.
    Vecteur2D _P1Prime; ///< Point P1'.
    Vecteur2D _P2Prime; ///< Point P2'.
    double _Lambda{}; ///< Lambda.
    double _petitLambda1{}; ///< Petit Lambda1.
    double _petitLambda2{}; ///< Petit Lambda2.
    int _eps1{};  ///< Epsilon1.
    int _eps2{}; ///< Epsilon2.
    Vecteur2D _C; ///< Point centre C.
    Vecteur2D _CPrime; ///< Point centre C'.
    int _a{}; ///< a.
    int _b{}; ///< b.
    bool calculsEffectues{}; ///< Indicateur indiquant si les calculs sont effectués.

    const static int L = 200; /**< La longueur par défaut de la fenêtre. */
    int _longueur; /**< La longueur de la fenêtre. */
    int _largeur; /**< La largeur de la fenêtre. */
    int _x; /**< La position en x de la fenêtre. */
    int _y; /**< La position en y de la fenêtre. */
    DessinVisitor <S,T> * _visitor; ///< Pointeur vers le visiteur utilisé pour dessiner les éléments.

public:


    /**
     * @brief Constructeur de la classe Fenetre.
     *
     * @param x La position en x de la fenêtre.
     * @param y La position en y de la fenêtre.
     * @param lon La longueur de la fenêtre.
     * @param lar La largeur de la fenêtre.
     * @param visitor Le visiteur pour dessiner sur la fenêtre.
     */
     Fenetre(int x, int y, int lon, int lar,DessinVisitor<S,T> * v){
        _longueur=lon;
        _largeur=lar;
        _x=x;
        _y=y;
        _visitor=v;
        string requete= to_string(_x)+","+to_string(_y)+","+to_string( _longueur)+","+to_string(_largeur);
        _visitor->visiteConnecte(requete);
     }

    // Getters et Setters pour les attributs principaux
    int getLongueur() const {
        return _longueur;
    }

    int getLargeur() const {
        return _largeur;
    }

    int getX() const {
        return _x;
    }

    int getY() const {
        return _y;
    }

    const Vecteur2D &getP1() const {
        return _P1;
    }

    const Vecteur2D &getP2() const {
        return _P2;
    }

    const Vecteur2D &getP1Prime() const {
        return _P1Prime;
    }

    const Vecteur2D &getP2Prime() const {
        return _P2Prime;
    }

    double getLambda() const {
        return _Lambda;
    }

    double getPetitLambda1() const {
        return _petitLambda1;
    }

    double getPetitLambda2() const {
        return _petitLambda2;
    }

    int getEps1() const {
        return _eps1;
    }

    int getEps2() const {
        return _eps2;
    }

    const Vecteur2D &getC() const {
        return _C;
    }

    const Vecteur2D &getCPrime() const {
        return _CPrime;
    }

    int getA() const {
        return _a;
    }

    int getB() const {
        return _b;
    }


    const vector<Arrete<S, T> *> &getTabArete() const {
        return _TabArete;
    }

    void setTabArete(const vector<Arrete<S, T> *> &tabArete) {
        _TabArete = tabArete;
    }

    /**
     * @brief Ajoute une arête au vecteur d'arêtes de la fenêtre.
     *
     * @param a Pointeur vers l'arête à ajouter.
     * @return Référence vers la fenêtre pour permettre les appels chaînés.
     */
    Fenetre & ajouterArete(Arrete<S,T> * a)
    {
        _TabArete.push_back(&a);
        return *(this);
    }

    /**
     * @brief Ajoute une liste d'arête au vecteur d'arêtes de la fenêtre.
     *
     * @param a Reference vers une liste d'arête à ajouter.
     * @return Référence vers la fenêtre pour permettre les appels chaînés.
     */
    Fenetre & ajouterListeArete(const vector<Arrete<S, T> *> &tabArete)
    {
         for(Arrete<S,T> * a: tabArete)
            _TabArete.push_back(a);

        return *(this);
    }

    /**
     * @brief Retire une arête du vecteur d'arêtes.
     *
     * @param a Pointeur vers l'arête à retirer.
     * @return Référence vers la fenêtre pour permettre les appels chaînés.
     */
    Fenetre & retirerArete(Arrete<S, T> *a) {
        for (auto it = _TabArete.begin(); it != _TabArete.end(); ++it) {
            if (*it == a) {
                _TabArete.erase(it); // Supprime l'élément à la position de l'itérateur.
                break; // Sortir de la boucle une fois l'élément supprimé.
            }
        }
        return *this;
    }

    /**
     * @brief Retourne le nombre d'arêtes dans le graphe.
     *
     * @return Nombre d'arêtes.
     */
    int getNbArete() const
    {
        return _TabArete.size();
    }

    /**
     * @brief Destructeur de la classe Fenetre.
     *
     * Informe le visiteur de la déconnexion avant de détruire l'objet.
     */
    ~Fenetre(){
        _visitor->visiteDeconnecte();
    }

    /**
     * @brief Dessine les éléments du graphe (sommets et arêtes) sur la fenêtre.
     */
    void Dessiner(){
        if(!isCalculsEffectues()) {
            //Détermination de lambda
            CalculP1();
            CalculP2();
            CalculP1Prime();
            CalculP2Prime();
            CalculLambda();
            getP1Prime();
            getP2Prime();
            getP1();
            getP2();
            CalculEps1();
            CalculEps2();
            CalculC();
            CalculCPrime();
            CalculPetitLambda1();
            CalculPetitLambda2();
            aCalcul();
            bCalcul();
            setCalculsEffectues(true);
        }
        //Dessiner
        vector<Sommet<T> *> tmp = getListeSommet();
        for(Sommet<T> *  elt: tmp){
            _visitor->visiteDessiner(elt, &(* this));
        }

        for(Arrete<S,T> * elt:_TabArete){
            _visitor->visiteDessiner(elt, &(* this));
        }
        _visitor->visiteDessiner(calculerDistanceTotale(),&(*this));
        sleep(10);
    }

private:
    // Méthodes pour les calculs géométriques et transformations (voir code original pour détails).

    void CalculP1() {

        double x = _TabArete[0]->getMinLat();
        for(Arrete<S,T> * elt:_TabArete)
        {
            double z;
            Arrete<S,T> * f = elt;
            z = f->getMinLat();
            if(z < x)
            {
                x = z;
            }
        }
        double y = _TabArete[0]->getMinLong();
        for(Arrete<S,T> * elt:_TabArete)
        {
            double z;
            Arrete<S,T> * F = elt;
            z = F->getMinLong();
            if(z < y)
            {
                y = z;
            }
        }
        Vecteur2D v(x,y);
        _P1 = v;
        cout <<"P1 : " <<  _P1 << endl;
    }

    void CalculP2() {
        double x = _TabArete[0]->getMaxLat();
        for(Arrete<S,T> * elt:_TabArete)
        {
            double z;
            Arrete<S,T> * f = elt;
            z = f->getMaxLat();
            if(z > x)
            {
                x = z;
            }
        }

        double y = _TabArete[0]->getMaxLong();
        for(Arrete<S,T> * elt:_TabArete)
        {
            double z;
            Arrete<S,T> * F = elt;
            z = F->getMaxLong();
            if(z > y)
            {
                y = z;
            }
        }


        Vecteur2D v(x,y);
        _P2 = v;
        cout <<"P2 : " <<  _P2 << endl;

    }

    void CalculP1Prime()
    {
        Vecteur2D v(MARGE,_largeur-MARGE);
        _P1Prime = v;
    }

    void CalculP2Prime()
    {
        Vecteur2D v(_longueur-MARGE,MARGE);
        _P2Prime = v;
    }

    void CalculLambda()
    {
        double val1;
        double val2;

        val1 =  abs(getP2Prime().x - getP1Prime().x) / abs(getP2().x - getP1().x);
        val2 = abs(getP2Prime().y - getP1Prime().y)/ abs(getP2().y - getP1().y);


        _Lambda = min(val1,val2);
    }

    void CalculEps1()
    {
        int rep = (( (getP2().x - getP1().x >= 0) && (getP2Prime().x - getP1Prime().x >= 0) ) ||
                   (getP2().x - getP1().x < 0 && getP2Prime().x - getP1Prime().x < 0) ) ? 1 : -1;
        _eps1 = rep;
    }

    void CalculEps2()
    {
        int rep = (( (getP2().y - getP1().y >= 0) && (getP2Prime().y - getP1Prime().y >= 0) ) ||
                   (getP2().y - getP1().y < 0 && getP2Prime().y - getP1Prime().y < 0) ) ? 1 : -1;
        _eps2 = rep;
    }

    void CalculC()
    {
        double x;
        double y;

        x = (getP1().x + getP2().x)/2;
        y = (getP1().y + getP2().y)/2;
        Vecteur2D v(x,y);
        _C = v;
    }

    void CalculCPrime()
    {
        double x;
        double y;
        x = (getP1Prime().x + getP2Prime().x)/2;
        y = (getP1Prime().y + getP2Prime().y)/2;
        Vecteur2D v(x,y);
        _CPrime = v;
    }

    void CalculPetitLambda1()
    {
        double rep = _eps1 * _Lambda;
        _petitLambda1 = rep;
    }

    void CalculPetitLambda2()
    {
        double rep = _eps2 * _Lambda;
        _petitLambda2 = rep;
    }

    void aCalcul()
    {
        double rep = _CPrime.x - (_petitLambda1*_C.x);
        int x = (int) rep;

        _a = x;
    }

    void bCalcul()
    {
        double rep = _CPrime.y - (_petitLambda2*_C.y);
        int x = (int) rep;
        _b = x;
    }

    bool isCalculsEffectues() const {
        return calculsEffectues;
    }

    void setCalculsEffectues(bool effectues) {
        calculsEffectues = effectues;
    }

    /**
     * @brief Permet d'avoir la liste des sommets défini dans la liste des arêtes.
     *
     * @return une liste de Sommet.
     */
    vector<Sommet<T> *>  getListeSommet(){
        vector<Sommet<T>*> sommets;

        for (Arrete<S, T>* arrete : _TabArete) {
            if (arrete->debut && find(sommets.begin(), sommets.end(), arrete->debut) == sommets.end()) {
                sommets.push_back(arrete->debut); // Ajouter le sommet de départ s'il n'est pas déjà présent
            }
            if (arrete->fin && find(sommets.begin(), sommets.end(), arrete->fin) == sommets.end()) {
                sommets.push_back(arrete->fin); // Ajouter le sommet de fin s'il n'est pas déjà présent
            }
        }
        return sommets;
    }

    /**
     * @brief Calcule la distance totale du graphe en sommant les poids des arêtes.
     *
     * @return La distance totale.
     */
    double calculerDistanceTotale()const{
        double somme=0;
        for (Arrete<S, T>* a: _TabArete){
            somme+=a->v;
        }
        return somme;
    }
};

#endif // PROJETPPIL_FENETRE_H

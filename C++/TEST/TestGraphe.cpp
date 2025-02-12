//
// Created by jules on 15/02/2024.
//

#include <algorithm>
#include "../OUTILS/Matrice.h"
#include "../GRAPHE/Graphe.h"
#include "../GRAPHE/Ville.h"


int main() {
    char ch;
    //----------------------------------- test kruskal prem --------------------------------------------
    Graphe<int, double> graphe;

    auto* S0 = graphe.creeSommet(0);
    auto* S1 = graphe.creeSommet(1);
    auto* S2 = graphe.creeSommet(2);
    auto* S3 = graphe.creeSommet(3);

    graphe.creeArete(1.0, S0, S1);
    graphe.creeArete(3.0, S0, S2);
    graphe.creeArete(2.0, S1, S2);
    graphe.creeArete(4.0, S1, S3);
    graphe.creeArete(5.0, S2, S3);


    auto mst = graphe.algoKruskal();

    // Affichage des résultats
    cout << "Arbre couvrant minimal : " << endl;
    double poidsTotal = 0.0;
    for (const auto& arete : mst) {
        cout << "Arête " << arete->debut->clef << "-"
             << arete->fin->clef << " (poids: " << arete->v << ")" << endl;
        poidsTotal += arete->v;
    }
    cout << "Poids total : " << poidsTotal << endl;

    cin>>ch;

    // Vérification attendue
    // MST devrait contenir les arêtes : 0-1, 1-2, 1-3 avec un poids total de 7.0

    //-------------------------------- test kruskal -----------------------------------

    Graphe<int, string> gTest, gKruskal;
    Sommet<string> *A,*B,*C,*D,*E,*F;
    Arrete<int, string> *AB,*AF,*AC,*BC,*CF,*CD,*CE,*ED;
    A = gTest.creeSommet("A");
    B = gTest.creeSommet("B");
    C = gTest.creeSommet("C");
    D = gTest.creeSommet("D");
    E = gTest.creeSommet("E");
    F = gTest.creeSommet("F");

    AB = gTest.creeArete(3,A,B);
    AF = gTest.creeArete(7,A,F);
    AC = gTest.creeArete(4,A,C);
    BC = gTest.creeArete(4,B,C);
    CF = gTest.creeArete(1,C,F);
    CD = gTest.creeArete(9,C,D);
    CE = gTest.creeArete(9,C,E);
    ED = gTest.creeArete(5,E,D);

    cout << gTest; cin >> ch;
    cout << "Transformation : \n";
    auto acm = gTest.algoKruskal();
    cout << acm;
    cin >> ch;

    //-------------------------------- distances géodésiques -------------------------------------------


    Ville T("Tokyo",49.12,6.17,12);
    Ville Ax("Tokyo",47.75,7.34,17);

    double test = T.distancesGeodesique(Ax);
    cout << "La distance est de : " << test << endl; cin >> ch;

    //____________________________________________________________

    cout << "Partie Graphe \n";

    Graphe<char, string> g2;

    Graphe<char,string> g1;	// création à vide

    Graphe<int, string> g0;

    Sommet<string> *s0, *s1, *s2, *s3;

//------------------ on insère des nouveaux sommets isolés --------------------

        s0 = g1.creeSommet("King's Landing");
        s1 = g1.creeSommet("Winterfell");
        s2 = g1.creeSommet("DragonStone");
        s3 = g1.creeSommet("The wall");

        cout << *s0 << *s1 << *s2 << *s3;

//----------------- on connecte certains sommets -------------------

    Arrete<char,string> * a0, * a1, *a2, *a3;
    Arrete<int ,string> * a01, * a11, *a21, *a31;

        a01 = g0.creeArete(12,s1,s0);
        a11 = g0.creeArete(4,s2,s1);
        a21 = g0.creeArete(26,s3,s2);
        a31 = g0.creeArete(18,s3,s1);

        cout << "Avant tri :";
        cout << g0.getLAretes();
        cin >> ch;
        g0.trierAretesParV();
        cout << "Après tri :";
        cout << g0.getLAretes();
        cin >> ch;


        a0 = g1.creeArete('a',s1,s0);
        a1 = g1.creeArete('b',s2,s1);
        a2 = g1.creeArete('c',s3,s2);
        a3 = g1.creeArete('d',s3,s1);

        cout << *a0 << *a1 << *a2 << *a3;

        //Vérifier les bons degrés
        cout << *s0 << *s1 << *s2 << *s3;
//------------------ faire le dessin du graphe sur papier en notant les noms et les degrés pour comprendre la suite ----------------

        cout << g1;

        cout <<"le nombre de sommets de g1 est : " << g1.nombreSommets() << endl;
        cout <<"le nombre d'arêtes de g1 est : " << g1.nombreAretes() << endl;

        vector<Sommet<string>*> l0 = g1.voisins(s0);
        cout << "la liste des voisins de s0 est : " << endl << l0 << endl; cin >> ch;

        vector<Arrete<char,string>*> adj0 = g1.aretesAdjacentes(s0);
        cout << "la liste des arêtes adjacentes à s0 est : " << endl << adj0 << endl; cin >> ch;

        vector<Sommet<string>*> l1 = g1.voisins(s1);
        cout << "la liste des voisins de s1 est : " << endl << l1 << endl;

        vector<Arrete<char,string>*> adj1 = g1.aretesAdjacentes(s1);
        cout << "la liste des arêtes adjacentes à s1 est : " << endl << adj1 << endl; cin >> ch;

        Arrete<char,string> * a = g1.getAreteParSommets(s1,s3);

        cout <<"l'arête joignant s1 et s3 est : " << endl << *a << endl; cin >> ch;

        g2 = g1;

    cout <<"le graphe créé g2 comme copie de g1 est :" << endl << g2 << endl; cin >> ch;


    return 0;
}
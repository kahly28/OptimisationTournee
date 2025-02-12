#include "../CONNEXION/VISITOR_DESSIN/JavaVisitor.h"
#include "../CONNEXION/FENETRE/Fenetre.h"

#include "Fichier.h"
#include "../FICHIER/COR_FICHIER/InitCor.h"
#include "../OUTILS/Camion.h"
int main(){
    DessinVisitor<double, Ville> * visitor = new JavaVisitor<double, Ville>; // Création dynamique de visitor
    auto* f1 = new Fenetre <double, Ville> (0, 0, 1000, 650, visitor); // Allocation dynamique de f1


    Fichier<double,Ville> f(InitCor<double,Ville>::InitCorFichier());
    Graphe<double,Ville> g;

    int nbCamion=3;
    vector<Camion<double,Ville> *> Camions;

    string fichier="GrandEst";
    Camions=f.ChargerFichier(fichier+".json",nbCamion);

    cout<<"fichier choisi :"<<fichier<<endl;

    for(Camion<double,Ville> * c:Camions){
        cout<<*c<<endl;
    }


    f1->ajouterListeArete(Camions[0]->CalculerTrajet());

    f1->Dessiner();

    cout<<"coucou4";

    return 0;
}
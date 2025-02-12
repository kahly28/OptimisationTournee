#ifndef PROJETPPIL_JAVAVISITOR_H
#define PROJETPPIL_JAVAVISITOR_H

#include "../SINGLETON/SingJavaLib.h"
#include "DessinVisitor.h"
#include "../../ERREUR/Erreur.h"
#include "../../GRAPHE/Ville.h"
#include "../FENETRE/Fenetre.h"

#include <iostream>
#include <sstream>

template <typename S, typename T>
/**
 * @brief Classe représentant un visiteur Java, qui interagit avec un serveur via un socket.
 *
 * Cette classe permet de connecter le client à un serveur Java et d'envoyer des informations concernant
 * des objets géométriques (sommets, arêtes, etc.) pour les dessiner sur une fenêtre distante.
 */
class JavaVisitor:public DessinVisitor<S,T> {
private:
    SOCKET sock{}; /**< @brief Socket pour la communication avec le serveur. */

    /**
     * @brief Envoie un message au serveur via le socket.
     *
     * Cette fonction formate le message et l'envoie au serveur. Elle utilise le socket pour établir la communication.
     * @param msg Message à envoyer au serveur.
     * @throws Erreur Si l'envoi échoue.
     */
    void sendMessage(string msg) const{
        int r;
        msg="\""+msg+"\"\r\n";
        r = send( sock, msg.c_str(),msg.size(), 0);             //------------------ envoi de la requête au serveur -------------------------------
        cout<<msg<<endl;
        // envoie au plus l'octets
        if (r == SOCKET_ERROR)
            throw Erreur("echec de l'envoi de la requete");
        cout<<"reussite de l'envoi de la requete\n\n"<<endl;
    }

    /**
     * @brief Calcule le coin supérieur gauche d'un sommet dans la fenêtre.
     *
     * Cette méthode calcule les coordonnées du coin supérieur gauche d'un sommet à afficher dans la fenêtre
     * en fonction des transformations géométriques appliquées.
     * @param a Sommet à convertir.
     * @param f Fenêtre graphique contenant les transformations.
     * @return Vecteur2D Coordonnées calculées du coin supérieur gauche.
     * @throws Erreur Si le type `T` n'est pas un `Ville`.
     */
    Vecteur2D getCoinSupGauche(Sommet<T> * a,Fenetre<S,T> * f) const {
        if (typeid(T) != typeid(Ville)) {
            throw new Erreur("Le type T n'est pas Ville");
        }
        int x = (f->getEps1() * f->getLambda() * a->v.getCoordonees().getX() - 1) + f->getA();
        int y = (f->getEps2() * f->getLambda() * a->v.getCoordonees().getY() + 1) + f->getB();
        return Vecteur2D(x,y);
    }

public:
    /**
     * @brief Connexion au serveur Java.
     *
     * Cette méthode établit la connexion avec un serveur en créant un socket et en envoyant un message
     * de connexion au serveur.
     * @param arg Argument à envoyer après la connexion pour identifier le client.
     */
    void visiteConnecte(string arg) {
        SingJavaLib::GetInstance();
        int r;
        //---------------------- création socket -------------------------------------------------

        int familleAdresses = AF_INET;         // IPv4
        int typeSocket = SOCK_STREAM;           // mode connecté TCP
        int protocole = IPPROTO_TCP;            // protocole. On peut aussi mettre 0 et la fct choisit le protocole en fct des 2 1ers paramètres
        // pour les valeurs des paramètres : cf. fct socket dans la doc sur winsock

        sock =  socket( familleAdresses, typeSocket, protocole);

        if (sock == INVALID_SOCKET)
        {
            ostringstream oss;
            oss << "la creation du socket a echoue : code d'erreur = " << WSAGetLastError() << endl;	// pour les valeurs renvoyées par WSAGetLastError() : cf. doc réf winsock
            throw Erreur(oss.str().c_str());
        }
        cout << "socket cree" << endl;

        //------------------------------ création du représentant du serveur ----------------------------------------

        SOCKADDR_IN sockaddr; // informations concernant le serveur avec lequel on va communiquer

        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");   // inet_addr() convertit de l'ASCII en entier
        sockaddr.sin_port = htons(789);                 //htons() assure que le port est bien inscrit dans le format du réseau (little-endian ou big-endian)

        //-------------- connexion du client au serveur ---------------------------------------
        do {
            r = connect( sock, (SOCKADDR * ) &sockaddr, sizeof(sockaddr)); // renvoie une valeur non nulle en cas d'échec.
            cout<<"connexion au serveur..."<<endl;
        }while(r == SOCKET_ERROR);
        cout << "connexion au serveur reussie" << endl;
        sendMessage(arg);
    }

    /**
     * @brief Déconnexion du serveur Java.
     *
     * Cette méthode ferme proprement la connexion avec le serveur et le socket.
     */
    void visiteDeconnecte() {
        int r;
        r = shutdown(sock,SD_BOTH);							// on coupe la connexion pour l'envoi et la réception

        // renvoie une valeur non nulle en cas d'échec. Le code d'erreur peut être obtenu par un appel à WSAGetLastError()

        if (r == SOCKET_ERROR)
            throw Erreur("la coupure de connexion a echoue");


        r = closesocket(sock);                          // renvoie une valeur non nulle en cas d'échec. Le code d'erreur peut être obtenu par un appel à WSAGetLastError()
        if (r) throw Erreur("La fermeture du socket a echoue");

        WSACleanup();
        sock=0;
        cout << "arret normal du client" << endl;
    }

    /**
     * @brief Dessine une arête dans la fenêtre.
     *
     * Cette méthode calcule les coordonnées des deux extrémités de l'arête et les envoie au serveur pour
     * être dessinées dans la fenêtre.
     * @param a Arête à dessiner.
     * @param f Fenêtre graphique où l'arête doit être dessinée.
     */
    void visiteDessiner(Arrete<S,T> * a,Fenetre<S,T> * f) const {
        Vecteur2D v1,v2;
        string x1,y1,x2,y2;
        v1=getCoinSupGauche(a->debut,f);
        v2=getCoinSupGauche(a->fin,f);
        x1=to_string(v1.x);y1=to_string(v1.y);
        x2=to_string(v2.x);y2=to_string(v2.y);
        sendMessage("arete:"+to_string(a->v)+",x1:"+x1+",y1:"+y1+",x2:"+x2+",y2:"+y2);
    }

    /**
     * @brief Dessine un sommet dans la fenêtre.
     *
     * Cette méthode calcule les coordonnées du sommet et l'envoie au serveur pour être dessiné.
     * @param A Sommet à dessiner.
     * @param f Fenêtre graphique où le sommet doit être dessiné.
     */
    void visiteDessiner( Sommet<T> * A,Fenetre<S,T> * f) const{
        string Nom=A->v.getNom();
        Vecteur2D v= getCoinSupGauche(A,f);
        string XString = to_string(v.x);
        string YString = to_string(v.y);
        sendMessage("ville:"+Nom+",x:"+XString+",y:"+YString);
    }

    /**
     * @brief Dessine une distance totale dans la fenêtre.
     *
     * Cette méthode envoie au serveur l'information sur la distance totale, ainsi que les coordonnées pour
     * afficher cette distance dans la fenêtre.
     * @param distTot Distance totale à afficher.
     * @param f Fenêtre graphique où la distance doit être affichée.
     */
    void visiteDessiner(double distTot,Fenetre<S,T> * f)const{
        sendMessage("distance:"+to_string(distTot)+",x:"+to_string(f->getLongueur()-50)+",y:"+to_string(f->getLargeur()-50));
    }
};



#endif //PROJETPPIL_JAVAVISITOR_H

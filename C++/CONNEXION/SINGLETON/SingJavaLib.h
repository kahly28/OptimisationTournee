#ifndef MAQUETTEC___INITSERVERSING_H
#define MAQUETTEC___INITSERVERSING_H

#include <winsock2.h>
#include <string>
#include "../../ERREUR/Erreur.h"

using namespace std;
/**
 * @brief Classe représentant un singleton pour initialiser la librairie Winsock.
 */
class SingJavaLib {
private:
    static SingJavaLib* singleton; /**< Instance unique du singleton. */

    /**
     * @brief Constructeur privé pour empêcher l'instanciation de la classe.
     */
    SingJavaLib() {}

public:
    /**
     * @brief Constructeur de copie supprimé pour éviter la duplication d'instances.
     */
    SingJavaLib(SingJavaLib &other) = delete;

    /**
     * @brief Opérateur d'assignation supprimé pour éviter la duplication d'instances.
     */
    void operator=(const SingJavaLib &)= delete;

    /**
     * @brief Méthode statique pour récupérer l'instance unique du singleton.
     * @return L'instance unique du singleton.
     */
    static SingJavaLib * GetInstance(){

        WSADATA wsaData;        // structure contenant les données de la librairie winsock à initialiser

        int r = WSAStartup( MAKEWORD(2,0), &wsaData);       // MAKEWORD(2,0) sert à indiquer la version de la librairie à utiliser : 1 pour winsock et 2 pour winsock2

        /* en cas de succès, wsaData a été initialisée et l'appel a renvoyé la valeur 0 */
        if (r) throw Erreur("L'initialisation a echoue");
        cout << "initialisation effectuee"<<endl;

        if(singleton == nullptr){
            singleton = new SingJavaLib;
        }
        return singleton;
    }
};

#endif //MAQUETTEC___INITSERVERSING_H

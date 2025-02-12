#ifndef PROJETPPIL_ERREUR_H
#define PROJETPPIL_ERREUR_H

#include <string>
#include <iostream>

/**
 * @brief Classe représentant une erreur.
 */
class Erreur {
public:
    const static int LONGUEURMESSAGE = 100; /**< Longueur maximale du message d'erreur */
    char message[1+LONGUEURMESSAGE]; /**< Message d'erreur */

    /**
     * @brief Constructeur par défaut de l'erreur.
     */
    Erreur();

    /**
     * @brief Constructeur avec un message d'erreur.
     * @param messageErreur Message d'erreur.
     */
    Erreur(const char * messageErreur);

    /**
     * @brief Convertit l'objet en une chaîne de caractères.
     * @return Chaîne de caractères représentant l'erreur.
     */
    operator std::string() const;
};

/**
 * @brief Surcharge de l'opérateur << pour afficher une erreur.
 * @param os Flux de sortie.
 * @param erreur Erreur à afficher.
 * @return Référence vers le flux de sortie.
 */
std::ostream & operator << (std::ostream & os, const Erreur & erreur);

#endif // PROJETPPIL_ERREUR_H


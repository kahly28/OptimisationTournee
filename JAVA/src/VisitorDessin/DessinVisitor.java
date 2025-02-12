package VisitorDessin;


import java.awt.*;

/**
 * Interface DessinVisitor
 *
 * Cette interface définit un ensemble de méthodes pour dessiner différents éléments
 * (villes, arêtes, et distance totale) dans une application graphique.
 * Les classes qui implémentent cette interface doivent fournir une logique spécifique
 * pour chaque méthode, en utilisant un objet Graphics.
 */
public interface DessinVisitor {

    /**
     * Méthode pour dessiner une ville.
     *
     * @param Ville Chaîne de caractères contenant les informations sur la ville.
     *              Format attendu : "nom:<nom_ville>,x:<x_coord>,y:<y_coord>"
     * @param g     Objet Graphics utilisé pour dessiner la ville.
     */
    void visitDessinVille(String Ville, Graphics g);

    /**
     * Méthode pour dessiner une arête (ligne entre deux villes).
     *
     * @param Arete Chaîne de caractères contenant les informations sur l'arête.
     *              Format attendu : "poids:<poids>,x1:<x1>,y1:<y1>,x2:<x2>,y2:<y2>"
     * @param g     Objet Graphics utilisé pour dessiner l'arête.
     */
    void visitDessinArete(String Arete, Graphics g);
    
    /**
     * Méthode pour afficher la distance totale d'un chemin trouvé.
     *
     * @param Distance Chaîne de caractères contenant les informations sur la distance totale.
     *                 Format attendu : "distance:<distance_totale>,x:<x_coord>,y:<y_coord>"
     * @param g        Objet Graphics utilisé pour afficher la distance.
     */
    void visitDessinDistance(String Distance, Graphics g);
}

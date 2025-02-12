package VisitorDessin;

import java.awt.*;

/**
 * Classe AWTVisitor
 *
 * Implémentation de l'interface DessinVisitor utilisant la bibliothèque AWT pour dessiner des éléments
 * (villes, arêtes, et distance totale) sur une interface graphique.
 */
public class AWTVisitor implements DessinVisitor{

    /**
     * Dessine une ville sur le graphique.
     *
     * @param ville Chaîne de caractères représentant les informations sur une ville.
     *              Format attendu : "nom:<nom_ville>,x:<x_coord>,y:<y_coord>"
     * @param g     Objet Graphics utilisé pour dessiner.
     */
    @Override
    public void visitDessinVille(String ville, Graphics g) {
        // Dessiner la ville (cercle rouge)
        String parts[]=ville.split(",");

        // Extraire chaque partie
        String nom = parts[0].split(":")[1];
        int x = (int)Math.round(Double.parseDouble( parts[1].split(":")[1]));
        int y = (int)Math.round(Double.parseDouble( parts[2].split(":")[1]));

        g.setColor(Color.RED);
        g.fillOval(x - 5, y - 5, 10, 10);

        // Dessiner le nom de la ville
        g.setColor(Color.BLACK);
        g.drawString(nom, x + 5, y - 5);
    }

    /**
     * Dessine une arête (ligne entre deux villes) sur le graphique.
     *
     * @param Arete Chaîne de caractères représentant les informations sur une arête.
     *              Format attendu : "poids:<poids>,x1:<x1>,y1:<y1>,x2:<x2>,y2:<y2>"
     * @param g     Objet Graphics utilisé pour dessiner.
     */
    @Override
    public void visitDessinArete(String Arete, Graphics g) {
        //Dessiner l'arete (segment noire)
        String parts[]=Arete.split(",");

        // Extraire chaque partie
        String poids =Double.toString(Math.round(Double.parseDouble(parts[0].split(":")[1])));
        int x1 = (int)Math.round(Double.parseDouble( parts[1].split(":")[1]));
        int y1 = (int)Math.round(Double.parseDouble( parts[2].split(":")[1]));
        int x2 = (int)Math.round(Double.parseDouble( parts[3].split(":")[1]));
        int y2 = (int)Math.round(Double.parseDouble( parts[4].split(":")[1]));

        g.setColor(Color.BLUE);
        g.drawLine(x1,y1,x2,y2);

        // Calculer le milieu de l'arête
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        g.drawString(poids, midX, midY);

    }
    /**
     * Affiche la distance totale du chemin trouvé en bas de la fenêtre.
     *
     * @param Distance Chaîne de caractères représentant les informations sur la distance totale.
     *                 Format attendu : "distance:<distance_totale>,x:<x_coord>,y:<y_coord>"
     * @param g        Objet Graphics utilisé pour dessiner.
     */
    @Override
    public void visitDessinDistance(String Distance, Graphics g) {
        String parts[]=Distance.split(",");

        // Extraire chaque partie
        String DistanceTotal = parts[0].split(":")[1];
        int x = (int)Math.round(Double.parseDouble( parts[1].split(":")[1]));
        int y = (int)Math.round(Double.parseDouble( parts[2].split(":")[1]));

        g.setColor(Color.BLACK);
        g.drawString("longueur du chemin trouvé (en Km) = "+DistanceTotal,50,y);
    }


}

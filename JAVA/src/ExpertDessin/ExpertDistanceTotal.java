package ExpertDessin;

import VisitorDessin.DessinVisitor;

import java.awt.*;

/**
 * Expert dessin pour la Distance totale
 */
public class ExpertDistanceTotal extends ExpertFormeCOR {

    /**
     * Constructeur
     * @param suivant Expert Suivant de la chaine de responsabilitée
     */
    public ExpertDistanceTotal(ExpertFormeCOR suivant){
        super (suivant);
    }

    /**
     * Permet de dessiner la Distance totale
     * @param forme String contenant distance totale à dessiner ainsi que ces paramètres
     * @param g Graphics de la fenêtre
     * @param v DessinVisitor qui permet d'avoir la logique de dessin selon la bibliothèque utilisée
     * @return boolean qui indique si l'expert a réussi à expertiser
     */
    @Override
    public boolean expertiser1(String forme, Graphics g, DessinVisitor v) {
        boolean trouve=false;
        String str[]=forme.split(",");
        if (str[0].split(":")[0].equals("distance")){
            v.visitDessinDistance(forme,g);
            trouve=true;
        }
        System.out.println("fin Expertise Distance avec "+trouve);
        return trouve;
    }
}

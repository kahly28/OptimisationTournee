package ExpertDessin;

import VisitorDessin.DessinVisitor;

import java.awt.*;

/**
 * Expert dessin pour une Arête
 */
public class ExpertArete extends ExpertFormeCOR {
    /**
     * Constructeur
     * @param suivant Expert Suivant de la chaine de responsabilitée
     */
    public ExpertArete(ExpertFormeCOR suivant){
        super(suivant);
    }

    /**
     * Permet de dessiner une Arête
     * @param forme String contenant l'Arête à dessiner ainsi que ces paramètres
     * @param g Graphics de la fenêtre
     * @param v DessinVisitor qui permet d'avoir la logique de dessin selon la bibliothèque utilisée
     * @return boolean qui indique si l'expert a réussi à expertiser
     */
    @Override
    public boolean expertiser1(String forme, Graphics g, DessinVisitor v){
        boolean trouve=false;
        String str[]=forme.split(",");
        if (str[0].split(":")[0].equals("arete")){
            v.visitDessinArete(forme,g);
            trouve=true;
        }
        System.out.println("fin Expertise Arete avec "+trouve);
        return trouve;
    }
}

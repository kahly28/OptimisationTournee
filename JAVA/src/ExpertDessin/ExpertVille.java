package ExpertDessin;

import VisitorDessin.DessinVisitor;

import java.awt.*;

/**
 * Expert dessin pour une ville
 */
public class ExpertVille extends ExpertFormeCOR{
    /**
     * Constructeur
     * @param suivant Expert Suivant de la chaine de responsabilitée
    */
    public ExpertVille(ExpertFormeCOR suivant){
        super(suivant);
    }


    /**
     * Permet de dessiner une ville
     * @param forme String contenant la ville à dessiner ainsi que ces paramètres
     * @param g Graphics de la fenêtre
     * @param v DessinVisitor qui permet d'avoir la logique de dessin selon la bibliothèque utilisée
     * @return boolean qui indique si l'expert a réussi à expertiser
     */
    @Override
    public boolean expertiser1(String forme, Graphics g, DessinVisitor v){
        boolean trouve=false;
        String str[]=forme.split(",");
        String aux[]=str[0].split(":");
        if (aux[0].equals("ville")){
            v.visitDessinVille(forme,g);
            trouve=true;
        }
        System.out.println("fin Expertise Ville avec "+trouve);
        return trouve;
    }
}

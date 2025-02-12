package ExpertDessin;

import VisitorDessin.DessinVisitor;

import java.awt.*;

/**
 * Classe abstraite permettant le dessin d'une forme
 */
public abstract class ExpertFormeCOR implements ExpertForme{
    public ExpertFormeCOR _suivant;

    /**
     * Constructeur
     * @param suivant Expert Suivant de la chaine de responsabilitée
     */
    public ExpertFormeCOR(ExpertFormeCOR suivant){
        _suivant=suivant;
    }

    /**
     * Méthode abstraite pour dessiner
     * @param forme String contenant l'élément à dessiner ainsi que ces paramètres
     * @param g Graphics de la fenêtre
     * @param v DessinVisitor qui permet d'avoir la logique de dessin selon la bibliothèque utilisée
     * @return boolean qui indique si l'expert a réussi à expertiser
     */
    public abstract boolean expertiser1(String forme,Graphics g, DessinVisitor v);

    /**
     * Appelle l'expert suivant pour dessiner
     * @param forme String contenant l'élément à dessiner ainsi que ces paramètres
     * @param g Graphics de la fenêtre
     * @param v DessinVisitor qui permet d'avoir la logique de dessin selon la bibliothèque utilisée
     * @return boolean qui indique si un expert a réussi à dessiner
     */
    @Override
    public boolean expertiser(String forme, Graphics g, DessinVisitor v){
        boolean resultat=expertiser1(forme,g,v);
        if (resultat!=false) return true;
        else {
            if (_suivant!=null)
                return _suivant.expertiser(forme, g,v);
            else
                return false;
        }
    }
}

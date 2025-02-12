package ExpertDessin;

import VisitorDessin.DessinVisitor;

import java.awt.*;

/**
 * Interface de la chaine de responsabilité pour le dessin
 */
public interface ExpertForme {
    /**
     * Appelle l'expert suivant pour dessiner
     * @param forme String contenant l'élément à dessiner ainsi que ces paramètres
     * @param g Graphics de la fenêtre
     * @param v DessinVisitor qui permet d'avoir la logique de dessin selon la bibliothèque utilisée
     * @return boolean qui indique si l'élément à réussi à être dessinée
     */
    public boolean expertiser(String forme, Graphics g, DessinVisitor v);
}

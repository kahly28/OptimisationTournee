package ExpertDessin;

/**
 * Classe InitCOR (Initialisation de la Chaîne de Responsabilité - Chain of Responsibility).
 *
 * Cette classe est responsable d'initialiser et de configurer la chaîne de responsabilité (COR) pour
 * le traitement des formes. Elle relie les différents experts dans un ordre spécifique.
 */
public class InitCOR {


    /**
     * Méthode statique pour initialiser la chaîne de responsabilité.
     *
     * Cette méthode crée et configure les différents experts (handlers) de la chaîne de responsabilité.
     * Les experts sont reliés dans un ordre où chaque expert est capable de traiter un certain type de
     * forme, ou de déléguer la responsabilité à l'expert suivant si le traitement ne lui correspond pas.
     *
     * Ordre des experts dans la chaîne :
     * - ExpertDistanceTotal : traite les calculs de la distance totale.
     * - ExpertVille : traite les dessins des villes.
     * - ExpertArete : traite les dessins des arêtes (liaisons entre les villes).
     *
     * @return ExpertFormeCOR La tête de la chaîne de responsabilité (le premier expert).
     */
    public static ExpertFormeCOR InitFormeCOR(){
        // Déclaration des experts
        ExpertFormeCOR e1,e2,e3;
        e1= new ExpertArete(null);
        e2= new ExpertVille(e1);
        e3= new ExpertDistanceTotal(e2);
        return e3;
    }
}

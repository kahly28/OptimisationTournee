package clientServeur;

import ExpertDessin.*;
import VisitorDessin.AWTVisitor;
import VisitorDessin.DessinVisitor;

import java.awt.*;
import java.awt.image.BufferStrategy;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

import static ExpertDessin.InitCOR.InitFormeCOR;
import static java.lang.Integer.parseInt;

public class Interlocuteur extends Thread{
    BufferedReader fluxEntrant;
    PrintStream fluxSortant;
    int nbClient;
    Frame f;
    Graphics graphics;

    int longueur;
    int largeur;

    /**
     * Constructeur d'un interlocuteur et création de la fenêtre
     * @param socket socket server client crée pour l'interlocuteur
     * @param numeroConnexion numéro de connexion de l'utilisateur
     * @throws IOException
     */
    Interlocuteur(Socket socket, int numeroConnexion) throws IOException {
        try {
            this.fluxEntrant = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.fluxSortant = new PrintStream(socket.getOutputStream());
            this.nbClient = numeroConnexion;

            String requete = this.fluxEntrant.readLine();
            requete = requete.replace("\"", ""); // Supprimer les guillemets
            String[] aux = requete.split(",");
            f = new Frame(" Graphe des villes");
            longueur=parseInt(aux[2]);
            largeur=parseInt(aux[3]);

            f.setBounds(parseInt(aux[0]), parseInt(aux[1]), longueur,largeur);
            f.setVisible(true);              // rend le frame visible sur l'écran
            f.setIgnoreRepaint(true);

            int numBuffers = 2;
            f.createBufferStrategy(numBuffers);  // crée une stratégie de tampon d'image à 1 tampon vidéo
            Thread.sleep(150);             // au moins 150 ms !!!! pour laisser au système le temps de créer le buffer d'image



        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Attend les Informations communiquées par le client pour les dessiner sur la fenêtre
     */
    @Override
    public void run()
    {
        ExpertFormeCOR E=InitCOR.InitFormeCOR(); //On initialise la COR
        DessinVisitor v = new AWTVisitor(); //Visiteur pour la bibliothèque

        BufferStrategy strategie = f.getBufferStrategy();
        graphics = strategie.getDrawGraphics();

        graphics.drawLine(longueur/2,0,longueur/2,largeur);
        graphics.drawLine(0,largeur/2,longueur,largeur/2);

        System.out.println("Interlocuteur vers le client numero " + nbClient + " créer ! \n");
        while(!this.isInterrupted())
        {
            try {
                String requete = this.fluxEntrant.readLine();
                //System.out.println("Le client a envoyé : "+ requete);
                if(requete != null){
                    requete = requete.replace("\"", ""); // Supprimer les guillemets

                    System.out.println(requete+"\n");

                    E.expertiser(requete,graphics,v);

                    ((BufferStrategy) strategie).show();       // place le tampon sur l'écran : la technique utilisée dépend du type de stratégie utilisé : blitting, pointeur vidéo, etc.

                    //sleep(100);
                }
                //System.out.println("fin de la boucle avec interlocuteur : "+this.isInterrupted());
            } catch (Exception e) {
                throw new RuntimeException(e);
           }
        }
        graphics.dispose();
        System.out.println("fin du programme");
    }
}

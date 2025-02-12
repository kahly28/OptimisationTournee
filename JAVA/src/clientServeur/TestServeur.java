package clientServeur;


import java.net.ServerSocket;
import java.net.Socket;

/**
 * Classe Server Java
 */
public class TestServeur {
    public static void main(String[] args) {
        try {

            int portServeur = 789;
            ServerSocket serveur = new ServerSocket(portServeur);
            int numeroConnexion = 0;
            while(true)
            {
                System.out.println("Serveur en attente de la prochaine connexion \n");
                Socket socket = serveur.accept();

                numeroConnexion++;
                System.out.println("Connexion réussi pour le client : " + numeroConnexion);
                Interlocuteur interlocuteur = new Interlocuteur(socket,numeroConnexion);
                interlocuteur.start();
            }

        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }
}

cmake_minimum_required(VERSION 3.27)
project(projet_ACL)

set(CMAKE_CXX_STANDARD 14)

# Ajout des répertoires d'inclusion
include_directories(FICHIER)
include_directories(FICHIER/COR_FICHIER)
include_directories(FICHIER/COR_FIGURE_CHARGEMENT)
include_directories(FICHIER/VISITOR_FICHIER)
include_directories(OUTILS)

# Définition de l'exécutable
add_executable(projet_ACL
        FICHIER/COR_FICHIER/ExpertFichier.cpp
        FICHIER/COR_FICHIER/ExpertFichier.h
        FICHIER/COR_FICHIER/ExpertFichierCOR.cpp
        FICHIER/COR_FICHIER/ExpertFichierCOR.h
        FICHIER/VISITOR_FICHIER/Visitor_Fichier.cpp
        FICHIER/VISITOR_FICHIER/Visitor_Fichier.h
        FICHIER/Fichier.cpp
        FICHIER/Fichier.h
        FICHIER/COR_FICHIER/ExpertFichierJSON.cpp
        FICHIER/VISITOR_FICHIER/JSON.h
        ERREUR/Erreur.h
        ERREUR/Erreur.cpp
        CONNEXION/FENETRE/Fenetre.h
        CONNEXION/FENETRE/Fenetre.cpp
        CONNEXION/SINGLETON/SingJavaLib.cpp
        CONNEXION/SINGLETON/SingJavaLib.h
        CONNEXION/VISITOR_DESSIN/DessinVisitor.cpp
        CONNEXION/VISITOR_DESSIN/JavaVisitor.h
        CONNEXION/VISITOR_DESSIN/JavaVisitor.cpp
        OUTILS/Matrice.cpp
        OUTILS/Vecteur2D.cpp
        GRAPHE/AElement.h
        GRAPHE/AElement.cpp
        GRAPHE/Ville.h
        GRAPHE/Ville.cpp
        GRAPHE/UnionFind.h
        GRAPHE/UnionFind.cpp
        GRAPHE/Sommet.h
        GRAPHE/Sommet.cpp
        GRAPHE/Graphe.h
        GRAPHE/Graphe.cpp
        TEST/TestCommunication.cpp
        OUTILS/Camion.h
        OUTILS/Camion.cpp
        FICHIER/COR_FICHIER/InitCor.h
)

# Ajout des bibliothèques nécessaires
target_link_libraries(projet_ACL ws2_32)
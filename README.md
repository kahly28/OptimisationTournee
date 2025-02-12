Projet Commun ACL - Optimisation de tournées de livraison

📌 Description du Projet

Ce projet s'inscrit dans le cadre du module ACL (Algorithmique et Complexité) du Master 1 Informatique. Il vise à résoudre un problème d’ordonnancement en le transformant en un problème de logistique.

L'objectif est d'optimiser la tournée de livraison d’une flotte de camions devant approvisionner différentes villes, en minimisant la distance totale parcourue.

Objectifs : 

Modélisation du problème sous forme d’un graphe complet où :
  - Les sommets représentent les villes à livrer.
  - Les arêtes représentent les routes entre les villes (distance géodésique).

Implémentation d’algorithmes pour :
- Générer une liste d’affectation des camions aux villes.
- Calculer les tournées de livraison (problème du voyageur de commerce - TSP).
- Visualiser la carte et les trajets réalisés.

Contraintes à respecter :
- Chaque ville est desservie par un seul camion.
- Un camion ne doit pas livrer des villes trop éloignées les unes des autres.
- Le programme doit être écrit en C++ et suivre les principes de conception logicielle avancée (design patterns, templates, etc.).

Solution non optimale : Pour le moment les algorithmes implémentés ne garantissent pas la solution optimale au problème du voyageur de commerce.

Technologies Utilisées

Langage : C++
Format des données : JSON (listes de villes avec coordonnées GPS)
Bibliothèques : Qt ou Java pour la visualisation


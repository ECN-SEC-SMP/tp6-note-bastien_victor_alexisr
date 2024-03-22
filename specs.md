# OOP - Lab6

Pour concevoir un jeu de Monopoly en C++, vous pouvez diviser le projet en plusieurs classes pour représenter les différents éléments du jeu et leurs interactions. Voici une spécification de solution et une proposition de diagrammes de classes :

## Spécification de la solution :
Classe Joueur :

Attributs : Nom du joueur, argent (mono), position sur le plateau, propriétés possédées.
Méthodes : Déplacer le joueur, acheter une propriété, payer un loyer, etc.
Classe Propriété :

Attributs : Nom de la propriété, prix d achat, loyers, propriétaire.
Méthodes : Obtenir le loyer, vérifier si la propriété est disponible, etc.
Classe Plateau :

Attributs : Liste des cases du plateau (peut être représentée par un tableau).
Méthodes : Gérer le mouvement des joueurs, vérifier si un joueur est sur une propriété, etc.
Classe Carte :

Attributs : Type de carte (Chance ou Communauté), texte de la carte.
Méthodes : Appliquer l effet de la carte sur le joueur.
Classe Dé :

Méthode : Lancer le dé pour obtenir un nombre aléatoire.
Classe Monopoly :

Attributs : Liste des joueurs, liste des propriétés, liste des cartes, etc.
Méthodes : Initialiser le jeu, gérer les tours des joueurs, vérifier les conditions de victoire, etc.

+-------------------+          +-------------------+          +----------------------+
|       Joueur      |          |     Propriété     |          |       Plateau        |
+-------------------+          +-------------------+          +----------------------+
| - nom: string     |          | - nom: string     |          | - cases: Case[]      |
| - argent: int     |          | - prix: int       |          |                      |
| - position: int   |          | - loyers: int[]   |          |                      |
| - propriétés: []  |          | - propriétaire: J |          |                      |
+-------------------+          +-------------------+          +----------------------+
| + déplacer()      |          | + obtenirLoyer()  |          | + déplacerJoueur()   |
| + acheter()       |          | + estDisponible() |          | + vérifierPropriété()|
| + payerLoyer()    |          |                   |          |                      |
+-------------------+          +-------------------+          +----------------------+
           |                            |                              |
           |                            |                              |
           |                            |                              |
           |                            |                              |
           |                            |                              |
+-------------------+          +-------------------+          +---------------------+
|       Carte       |          |        Dé         |          |      Monopoly       |
+-------------------+          +-------------------+          +---------------------+
| - type: string    |          |                   |          | - joueurs: Joueur[] |
| - texte: string   |          |                   |          | - propriétés: Prop[]|
+-------------------+          +-------------------+          | - cartes: Carte[]   |
| + appliquerEffet()|                                         |                     |
+-------------------+                                         | + initialiserJeu()  |
                                                              | + gérerTour()       |
                                                              | + vérifierVictoire()|
                                                              +---------------------+

## Explications des choix de conception et algorithmiques :
Classe Joueur : Permet de gérer les actions et les informations liées à chaque joueur, telles que leur argent, leur position sur le plateau et les propriétés qu'ils possèdent.

Classe Propriété : Représente les propriétés du jeu, avec des informations telles que leur prix d'achat, les loyers à payer et leur propriétaire actuel.

Classe Plateau : Gère la disposition des cases du plateau et les déplacements des joueurs. Elle contient une méthode pour vérifier si un joueur est sur une propriété et une autre pour déplacer le joueur.

Classe Carte : Représente les cartes Chance et Communauté, avec des effets qui peuvent être appliqués aux joueurs.

Classe Dé : Permet de simuler le lancer de dés pour déplacer les joueurs.

Classe Monopoly : Coordonne l'ensemble du jeu, initialisant les joueurs, les propriétés, les cartes, et gérant le déroulement des tours.
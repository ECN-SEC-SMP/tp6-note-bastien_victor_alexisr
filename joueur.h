#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include "propriete.h" // Inclure le fichier d'en-tête de la classe Propriete si nécessaire

class Joueur {
private:
    std::string nom;            // Nom du joueur
    int argent;                 // Argent (mono) du joueur
    int position;               // Position du joueur sur le plateau
    std::vector<Propriete*> proprietes;  // Liste des propriétés possédées par le joueur

public:
    // Constructeur
    Joueur(std::string _nom, int _argent, int _position);

    // Méthodes pour accéder et modifier les attributs
    std::string getNom() const;
    int getArgent() const;
    int getPosition() const;
    void setArgent(int _argent);
    void setPosition(int _position);

    // Méthodes pour gérer les propriétés du joueur
    void ajouterPropriete(Propriete* propriete);
    void retirerPropriete(Propriete* propriete);

    // Méthode pour déplacer le joueur
    void deplacer(int nombreCases);

    // Méthode pour acheter une propriété
    bool acheter(Propriete* propriete);

    // Méthode pour payer un loyer
    void payerLoyer(int montant);

    // Méthode pour afficher les informations du joueur
    void afficherInfos() const;
};

#endif // JOUEUR_H

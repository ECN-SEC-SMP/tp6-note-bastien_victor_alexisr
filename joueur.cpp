#include <string>
#include <vector>
#include "joueur.h"

class Joueur {
private:
    std::string nom;            // Nom du joueur
    int argent;                 // Argent (mono) du joueur
    int position;               // Position du joueur sur le plateau
    std::vector<Propriete*> proprietes;  // Liste des propriétés possédées par le joueur

public:
    // Constructeur
    Joueur(std::string _nom, int _argent, int _position) : nom(_nom), argent(_argent), position(_position) {}

    // Méthodes pour accéder et modifier les attributs
    std::string getNom() const { return nom; }
    int getArgent() const { return argent; }
    int getPosition() const { return position; }
    void setArgent(int _argent) { argent = _argent; }
    void setPosition(int _position) { position = _position; }

    // Méthodes pour gérer les propriétés du joueur
    void ajouterPropriete(Propriete* propriete) { proprietes.push_back(propriete); }
    void retirerPropriete(Propriete* propriete) {
        // Retirer une propriété de la liste du joueur
        for (auto it = proprietes.begin(); it != proprietes.end(); ++it) {
            if (*it == propriete) {
                proprietes.erase(it);
                break;
            }
        }
    }

    // Méthode pour déplacer le joueur
    void deplacer(int nombreCases) {
        position = (position + nombreCases) % 40;
    }

    // Méthode pour acheter une propriété
    bool acheter(Propriete* propriete) {
        if (argent >= propriete->getPrix()) {
            argent -= propriete->getPrix();
            ajouterPropriete(propriete);
            propriete->setProprietaire(this);
            return true;
        }
        return false;
    }

    // Méthode pour payer un loyer
    void payerLoyer(int montant) {
        argent -= montant;
    }

    // Méthode pour afficher les informations du joueur
    void afficherInfos() const {
        std::cout << "Nom du joueur : " << nom << std::endl;
        std::cout << "Argent : " << argent << std::endl;
        std::cout << "Position sur le plateau : " << position << std::endl;
        std::cout << "Propriétés possédées :" << std::endl;
        for (const auto& propriete : proprietes) {
            std::cout << "   - " << propriete->getNom() << std::endl;
        }
    }
};

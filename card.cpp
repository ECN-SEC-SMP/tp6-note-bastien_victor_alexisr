#include "card.hpp"

// Constructor
Card::Card(std::string _text) : text(_text) {}

// Constructor
ChanceCard::ChanceCard(std::string _text) : Card(_text) {}

// How to apply the Chance card effect to the CommunityChestCard
void ChanceCard::appliedEffect(Player* player) {
    // Generate a random number to select an effect
    int effect = rand() % 3; // For example, 3 possible effects

    switch (effect) {
        case 0:
            // Effect 1: The player moves 3 squares forward
            //player->move(3);
            break;
        case 1:
            // Effect 2: The player receives 100 mono
            player->setMoney(player->getMoney() + 100);
            break;
        case 2:
            // Effect 3: The player returns to square one
            //player->setPosition(0);
            break;
        // Add other effects as required
    }
}

// Constructor
CommunityChestCard::CommunityChestCard(std::string _text) : Card(_text) {}

// How to apply the Community card effect to the CommunityChestCard
void CommunityChestCard::appliedEffect(Player* player) {
    // Generate a random number to select an effect
    int effect = rand() % 3; // For example, 3 possible effects

    switch (effect) {
        case 0:
            // Effect 1: The player moves 2 squares forward
            //player->move(2);
            break;
        case 1:
            // Effect 2: The player pay a bill of 100 mono
            player->payRent(50);
            break;
        case 2:
            // Effect 3: The player go to prison
            //player->setPosition(30);
            break;
        // Add other effects as required
    }
}
/**
 * @file gamecore.h
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the game core
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GAMECORE_H
#define GAMECORE_H

#include <vector>
#include "spaces.h"
#include <optional>
#include <random>


class PlayerManager
{
    private:
        std::vector<Player> players;
        int nbPlayers = 0; // Minimum 2 players and maximum 8 players
        Player* currentPlayer;
    public:
        PlayerManager();
        ~PlayerManager();
        void addPlayer(Player* player);
        void removePlayer(Player* player);
        void setCurrentPlayer(Player* player);
        Player* getPlayer(int index);
        Player* getCurrentPlayer();
        Player* getNextPlayer();
        void transferMoney(Player* sender, Player* receiver, int amount); // If sender or receiver is the bank, use nullptr
        void buyProperty(Property* property);
};

class PropertyManager
{
    private:
        std::vector<Property> properties;
        int nbHouses = 32;
        int nbHotels = 12;
    public:
        PropertyManager();
        ~PropertyManager();
        void addProperty(Property* property);
        void removeProperty(Property* property);
        void affectProperty(Player* player, Property* property);
        Property* getProperty(int index);
};

class Dice
{
    private:
        int value;
    public:
        Dice();
        ~Dice();
        int roll(std::mt19937& gen);
};

class GameCore
{
    private:
        PlayerManager playerManager;
        PropertyManager propertyManager;
        Dice dice1;
        Dice dice2;
        std::vector<Space*> board;
    public:
        GameCore(std::vector<Space*> _board);
        ~GameCore();
        void startGame();
        void playTurn();
        int rollDice(std::mt19937& gen, Dice dice, std::optional<Dice> dice2 = std::nullopt);
        void movePlayer(Player* player, int diceValue);
        void handleSpace(Player* player);

};

#endif // GAMECORE_H
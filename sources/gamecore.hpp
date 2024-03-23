/**
 * @file gamecore.hpp
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the game core
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GAMECORE_HPP
#define GAMECORE_HPP

#include <vector>
#include "spaces.hpp"


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
        Property* getProperty(int index);
};

class Dice
{
    private:
        int value;
    public:
        Dice();
        ~Dice();
        int roll();
};

class GameCore
{
    private:
        PlayerManager playerManager;
        PropertyManager propertyManager;
        std::vector<Space*> board;
    public:
        GameCore(std::vector<Space*> _board);
        ~GameCore();
        int rollDice();
        void movePlayer(Player* player, int diceValue);
        void handleSpace(Player* player);

};

#endif // GAMECORE_HPP
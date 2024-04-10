/**
 * @file managers.h
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the management of players and buyable spaces
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MANAGERS_H
#define MANAGERS_H

#include "spaces.h"
#include "player.h"
#include "cards.h"
#include <vector>
#include <optional>
#include <random>
#include <memory>

class Dice
{
    private:
        int value;
    public:
        Dice();
        ~Dice();
        int roll(std::mt19937& gen);
        int getValue() const;
};

class Space; // Forward declaration
class CommunityChestCard; // Forward declaration
class ChanceCard; // Forward declaration

class PlayerManager
{
    private:
        std::vector<std::shared_ptr<Player>> players;
        int nbPlayers = 0; // Minimum 2 players and maximum 8 players
        std::shared_ptr<Player> currentPlayer;
    public:
        PlayerManager();
        ~PlayerManager();
        void addPlayer(std::shared_ptr<Player> player); 
        void removePlayer(std::shared_ptr<Player> player);
        void setCurrentPlayer(std::shared_ptr<Player> player);
        std::shared_ptr<Player> getPlayer(int index);
        int getNbPlayers();
        std::shared_ptr<Player> getCurrentPlayer();
        void setNextPlayer();
        void transferMoneyFromTo(std::shared_ptr<Player>player1, std::shared_ptr<Player> player2, int amount); // If either player = nullptr, it's the bank
};

class BoardManager : public std::enable_shared_from_this<BoardManager>
{
    private:
        std::shared_ptr<BoardManager> self; // self attribute needed to pass itself as a shared pointer in methods
        int nbHouses = 32;
        int nbHotels = 12;
        std::vector<Space*> board;
        std::vector<std::unique_ptr<ChanceCard>> chanceDeck;
        std::vector<std::unique_ptr<CommunityChestCard>> communityChestDeck;
        PlayerManager playerManager;
        Dice dice1, dice2;
        std::pair<int, int> currentDicesValue;
    public:
        BoardManager(std::vector<Space*> _board, std::vector<std::unique_ptr<CommunityChestCard>> _communityChestDeck, std::vector<std::unique_ptr<ChanceCard>> _chanceDeck);
        ~BoardManager();
        PlayerManager* getPlayerManager();   
        std::vector<Space*> getBoard();
        std::pair<int, int> getCurrentDicesValue();
        void rollDice(std::mt19937& gen);
        void setBoard(std::vector<Space*> _board);
        void drawChanceCard();
        void drawCommunityChestCard();
        void movePlayer(int diceValue);
        void affectProperty(std::shared_ptr<Player> player, Space* space);
        void handleSpace();
};

#endif // MANAGERS_H
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

// Forward declaration
class Space; 
class CommunityChestCard; 
class ChanceCard; 

class Dice
{
    private:
        int value;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution;
    public:
        Dice();
        ~Dice();
        int roll();
};

class PlayerManager
{
    private:
        std::vector<std::shared_ptr<Player>> players;
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
        int nbHouses = 32;
        int nbHotels = 12;
        std::vector<std::shared_ptr<Space>> board;
        std::vector<std::unique_ptr<ChanceCard>> chanceDeck;
        std::vector<std::unique_ptr<CommunityChestCard>> communityChestDeck;
        std::shared_ptr<PlayerManager> playerManager;
        Dice dice1, dice2;
        std::pair<int, int> currentDicesValue;
    public:
        BoardManager(std::vector<std::shared_ptr<Space>> _board, std::vector<std::unique_ptr<CommunityChestCard>> _communityChestDeck, std::vector<std::unique_ptr<ChanceCard>> _chanceDeck);
        ~BoardManager();
        std::shared_ptr<PlayerManager> getPlayerManager();   
        std::vector<std::shared_ptr<Space>> getBoard();
        std::pair<int, int> getCurrentDicesValue();
        void rollDice();
        void drawChanceCard();
        void drawCommunityChestCard();
        void movePlayer(int diceValue);
        void affectProperty(std::shared_ptr<Player> player, std::shared_ptr<Space> space);
        void handleSpace();
};

#endif // MANAGERS_H
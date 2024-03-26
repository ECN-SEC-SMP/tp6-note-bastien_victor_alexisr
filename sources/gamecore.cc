/**
 * @file gamecore.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the game core
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "gamecore.h"
#include <iostream>


PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::addPlayer(Player* player)
{
    players.push_back(*player);
    nbPlayers++;
}

void PlayerManager::removePlayer(Player* player)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (&players[i] == player)
        {
            players.erase(players.begin() + i);
            nbPlayers--;
            break;
        }
    }
}

Player* PlayerManager::getPlayer(int index)
{
    return &players[index];
}

Player* PlayerManager::getCurrentPlayer()
{
    return currentPlayer;
}

Player* PlayerManager::getNextPlayer()
{
    int index = 0;
    for (int i = 0; i < players.size(); i++)
    {
        if (&players[i] == currentPlayer)
        {
            index = i;
            break;
        }
    }
    if (index == players.size() - 1)
    {
        return &players[0];
    }
    else
    {
        return &players[index + 1];
    }
}

void PlayerManager::setCurrentPlayer(Player* player)
{
    currentPlayer = player;
}

void PlayerManager::transferMoney(Player* sender, Player* receiver, int amount)
{
    // TODO
}

void PlayerManager::buyProperty(Property* property)
{
    // TODO
}

PropertyManager::PropertyManager()
{
}

PropertyManager::~PropertyManager()
{
}

void PropertyManager::addProperty(Property* property)
{
    properties.push_back(*property);
}

void PropertyManager::removeProperty(Property* property)
{
    for (int i = 0; i < properties.size(); i++)
    {
        if (&properties[i] == property)
        {
            properties.erase(properties.begin() + i);
            break;
        }
    }
}

Property* PropertyManager::getProperty(int index)
{
    return &properties[index];
}

Dice::Dice()
{
}

Dice::~Dice()
{
}

int Dice::roll(std::mt19937& gen)
{
    std::uniform_int_distribution<int> dist(1, 6);
    value = dist(gen);
    return value;
}

GameCore::GameCore(std::vector<Space*> _board) : board(_board)
{
}

GameCore::~GameCore()
{
}

void GameCore::startGame()
{
    std::cout << "MONOPOLY GAME" << std::endl;
    std::cout << "Welcome to the Monopoly game!" << std::endl;
    std::cout << "Please enter the number of players (2-8): ";
    int nbPlayers;
    std::cin >> nbPlayers;
    if (nbPlayers < 2 || nbPlayers > 8)
    {
        std::cout << "Invalid number of players. Please enter a number between 2 and 8." << std::endl;
        return;
    }
    for (int i = 0; i < nbPlayers; i++)
    {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        Player* player = new Player(name);
        playerManager.addPlayer(player);
    }
    playerManager.setCurrentPlayer(playerManager.getPlayer(0));
    dice1 = Dice();
    dice2 = Dice();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press any key to start the game." << std::endl;
    std::cin.get();
}

void GameCore::playTurn()
{
    std::cout << "It is " << playerManager.getCurrentPlayer()->getName() << "'s turn." << std::endl;
    std::cout << "Press any key to roll the dice." << std::endl;
    std::cin.get();
    std::mt19937 randomEngine(time(nullptr));
    int diceValue = rollDice(randomEngine, dice1, dice2);
    std::cout << "You rolled a " << diceValue << "." << std::endl;
    movePlayer(playerManager.getCurrentPlayer(), diceValue);
    handleSpace(playerManager.getCurrentPlayer());
    playerManager.setCurrentPlayer(playerManager.getNextPlayer());
}

int GameCore::rollDice(std::mt19937& gen, Dice dice1, std::optional<Dice> dice2)
{
    int value1 = dice1.roll(gen);
    if (dice2.has_value())
    {
        int value2 = dice2.value().roll(gen);
        return value1 + value2;
    }
    return value1;
}

void GameCore::movePlayer(Player* player, int diceValue)
{
    int numSpaces = board.size();
    int currentIndex = player->getPosition();
    int newIndex = (currentIndex + diceValue) % numSpaces;
    player->setPosition(newIndex);
}

void GameCore::handleSpace(Player* player)
{
    Space* space = board[player->getPosition()];
    // space->action(player);
    std::cout << player->getName() << " landed on " << space->getName() << "." << std::endl;
}




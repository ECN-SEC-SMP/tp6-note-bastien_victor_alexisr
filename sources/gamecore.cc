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

int Dice::roll()
{
    return rand() % 6 + 1;
}

GameCore::GameCore(std::vector<Space*> _board) : board(_board)
{
}

GameCore::~GameCore()
{
}

int GameCore::rollDice()
{
    // TODO
    return 0;
}

void GameCore::movePlayer(Player* player, int diceValue)
{
    // TODO
}

void GameCore::handleSpace(Player* player)
{
    // TODO
}




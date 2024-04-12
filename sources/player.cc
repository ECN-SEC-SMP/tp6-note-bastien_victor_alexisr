/**
 * @file player.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the player
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "player.h"

Player::Player(std::string _name) : name(_name)
{
}

Player::~Player()
{
}

int Player::getPosition() const
{
    return position;
}

void Player::setPosition(int _position)
{
    position = _position;
}

int Player::getMoney() const
{
    return money;
}

void Player::setMoney(int _money)
{
    money = _money;
}

int Player::getRemainingTurnsInJail() const
{
    return remainingTurnsInJail;
}

void Player::setRemainingTurnsInJail(int _remainingTurnsInJail)
{
    remainingTurnsInJail = _remainingTurnsInJail;
}

bool Player::getIsBankrupt() const
{
    return isBankrupt;
}

void Player::setIsBankrupt(bool _isBankrupt)
{
    isBankrupt = _isBankrupt;
}

int Player::getNbStationsOwned() const
{
    return nbStationsOwned;
}

void Player::setNbStationsOwned(int _nbStationsOwned)
{
    nbStationsOwned = _nbStationsOwned;
}

bool Player::getHasGetOutOfJailCard() const
{
    return hasGetOutOfJailCard;
}

void Player::setHasGetOutOfJailCard(bool _hasGetOutOfJailCard)
{
    hasGetOutOfJailCard = _hasGetOutOfJailCard;
}

int Player::getNbUtilitiesOwned() const
{
    return nbUtilitiesOwned;
}

void Player::setNbUtilitiesOwned(int _nbUtilitiesOwned)
{
    nbUtilitiesOwned = _nbUtilitiesOwned;
}

std::string Player::getName() const
{
    return name;
}


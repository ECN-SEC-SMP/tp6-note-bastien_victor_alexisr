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
#include <iostream>

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

int Player::getNbStationsOwned() const
{
    return nbStationsOwned;
}

void Player::setNbStationsOwned(int _nbStationsOwned)
{
    nbStationsOwned = _nbStationsOwned;
}

bool Player::getHasChanceGOJFC() const
{
    return hasChanceGOJFC;
}

void Player::setHasChanceGOJFC(bool _hasChanceGOJFC)
{
    hasChanceGOJFC = _hasChanceGOJFC;
}

bool Player::getHasCommunityChestGOJFC() const
{
    return hasCommunityChestGOJFC;
}

void Player::setHasCommunityChestGOJFC(bool _hasCommunityChestGOJFC)
{
    hasCommunityChestGOJFC = _hasCommunityChestGOJFC;
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


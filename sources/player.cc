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

std::string Player::getName() const
{
    return name;
}


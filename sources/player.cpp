/**
 * @file player.cpp
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the player
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "player.hpp"

Player::Player(std::string _name) : name(_name)
{
}

Player::~Player()
{
}

std::string Player::getName()
{
    return name;
}


/**
 * @file player.h
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the player
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;      
    int money = 1500;            
    int position = 0;            
    int nbStationsOwned = 0;
    int nbUtilitiesOwned = 0;
    int remainingTurnsInJail = 0;
    bool hasGetOutOfJailCard = false;
public:
    Player(std::string _name);
    ~Player();
    int getPosition() const;
    void setPosition(int _position);
    int getMoney() const;
    void setMoney(int _money);
    int getRemainingTurnsInJail() const;
    void setRemainingTurnsInJail(int _remainingTurnsInJail);
    bool getHasGetOutOfJailCard() const;
    void setHasGetOutOfJailCard(bool _hasGetOutOfJailCard);
    int getNbStationsOwned() const;
    void setNbStationsOwned(int _nbStationsOwned);
    int getNbUtilitiesOwned() const;
    void setNbUtilitiesOwned(int _nbUtilitiesOwned);
    std::string getName() const;
};

#endif // PLAYER_H

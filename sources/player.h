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
    bool hasChanceGOJFC = false; // GOJFC = Get Out of Jail Free Card
    bool hasCommunityChestGOJFC = false; // GOJFC = Get Out of Jail Free Card
public:
    Player(std::string _name);
    ~Player();
    int getPosition() const;
    void setPosition(int _position);
    int getMoney() const;
    void setMoney(int _money);
    int getRemainingTurnsInJail() const;
    void setRemainingTurnsInJail(int _remainingTurnsInJail);
    bool getHasChanceGOJFC() const;
    void setHasChanceGOJFC(bool _hasChanceGOJFC);
    bool getHasCommunityChestGOJFC() const;
    void setHasCommunityChestGOJFC(bool _hasCommunityChestGOJFC);
    int getNbStationsOwned() const;
    void setNbStationsOwned(int _nbStationsOwned);
    int getNbUtilitiesOwned() const;
    void setNbUtilitiesOwned(int _nbUtilitiesOwned);
    std::string getName() const;
};

#endif // PLAYER_H

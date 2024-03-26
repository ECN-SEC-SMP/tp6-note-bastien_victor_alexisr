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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "cards.h"

class Player {
private:
    std::string name;      
    int money;            
    int position;            
    int remainingTurnsInJail;
    Deck<ChanceCard*> chanceCards;
    Deck<CommunityChestCard*> communityChestCards;
public:
    Player(std::string _name);
    ~Player();
    int getPosition() const;
    void setPosition(int _position);
    int getMoney() const;
    void setMoney(int _money);
    int getRemainingTurnsInJail() const;
    void setRemainingTurnsInJail(int _remainingTurnsInJail);
    std::string getName() const;
};

#endif // PLAYER_H

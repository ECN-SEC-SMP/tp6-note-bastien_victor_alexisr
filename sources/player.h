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

class Player {
private:
    std::string name;      
    int money;            
    int position;            
    int remainingTurnsInJail;
public:
    Player(std::string _name);
    ~Player();
    std::string getName();
};

#endif // PLAYER_H

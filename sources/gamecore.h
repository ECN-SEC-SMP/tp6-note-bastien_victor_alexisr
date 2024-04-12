/**
 * @file gamecore.h
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the game core
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GAMECORE_H
#define GAMECORE_H


#include "managers.h"

class GameCore
{
    private:
        std::shared_ptr<BoardManager> boardManager;
        int consecutiveDoubles = 0;
    public:
        GameCore(std::vector<Space*> spaces, std::vector<std::unique_ptr<CommunityChestCard>> communityChestCards, std::vector<std::unique_ptr<ChanceCard>> chanceCards);
        ~GameCore();
        void startGame();
        void playTurn(std::mt19937& gen);
};

#endif // GAMECORE_H
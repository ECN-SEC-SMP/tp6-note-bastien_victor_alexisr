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
#include <iostream>
#include <memory>
// #include "spdlog/spdlog.h"
#include "../utils/input_manager.h"



GameCore::GameCore(std::vector<std::shared_ptr<Space>> spaces, std::vector<std::unique_ptr<CommunityChestCard>> communityChestCards, std::vector<std::unique_ptr<ChanceCard>> chanceCards)
    : boardManager(std::make_shared<BoardManager>(spaces, std::move(communityChestCards), std::move(chanceCards)))
{
    // spdlog::debug("GameCore created");
}

GameCore::~GameCore()
{
}


void GameCore::startGame()
{
    std::cout << "MONOPOLY GAME" << std::endl;
    std::cout << "Welcome to the Monopoly game!" << std::endl;
    int nbPlayers = getNumber("Enter the number of players (2-8): ", 2, 8);
    for (int i = 0; i < nbPlayers; i++)
    {
        std::string message = "Enter the name of player " + std::to_string(i + 1) + ": ";
        std::string name = getString(message);
        boardManager->getPlayerManager()->addPlayer(std::make_shared<Player>(name));
    }
    getEnter("Press Enter to start the game.");
    int turns = 0;
    while (boardManager->getPlayerManager()->getNbPlayers() > 1 && turns < 1000){
        playTurn();
        turns++;
    }
    std::cout << "Game over!" << std::endl;
    if (turns == 1000)
    {
        std::cout << "The game has reached the maximum number of turns (1000)." << std::endl;
        return;
    }
    std::cout << "The winner is " << boardManager->getPlayerManager()->getPlayer(0)->getName() << "!" << std::endl;

}

void GameCore::playTurn()
{
    if (boardManager->getPlayerManager()->getCurrentPlayer() == nullptr)
    {
        boardManager->getPlayerManager()->setNextPlayer();
        return;
    }
    std::cout << "\nIt is " << boardManager->getPlayerManager()->getCurrentPlayer()->getName() << "'s turn (" << boardManager->getPlayerManager()->getCurrentPlayer()->getMoney() << "€)." << std::endl;
    getEnter("Press Enter to roll the dice.");
    boardManager->rollDice();
    std::pair<int, int> dicesValue = boardManager->getCurrentDicesValue();
    std::cout << "You rolled a " << dicesValue.first << " and a " << dicesValue.second << "." << std::endl;
    boardManager->movePlayer(dicesValue.first + dicesValue.second);
    if (dicesValue.first == dicesValue.second)
    {
        consecutiveDoubles++;
        if (consecutiveDoubles == 3)
        {
            std::cout << "You rolled 3 doubles in a row! Go to jail." << std::endl;
            boardManager->getPlayerManager()->getCurrentPlayer()->setPosition(10);
            boardManager->handleSpace();
            boardManager->getPlayerManager()->setNextPlayer();
            consecutiveDoubles = 0;
            return;
        }
        std::cout << "You rolled a double! You get to play again." << std::endl;
        playTurn();
    }
    else
    {
        boardManager->getPlayerManager()->setNextPlayer();
        consecutiveDoubles = 0;
    }
}






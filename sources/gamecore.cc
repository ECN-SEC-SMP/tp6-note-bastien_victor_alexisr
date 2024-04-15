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



GameCore::GameCore(std::vector<std::shared_ptr<Space>> spaces, std::vector<std::unique_ptr<CommunityChestCard>> communityChestCards, std::vector<std::unique_ptr<ChanceCard>> chanceCards)
    : boardManager(std::make_shared<BoardManager>(spaces, std::move(communityChestCards), std::move(chanceCards)))
{
    // std::cout << "GameCore created." << std::endl;
}

GameCore::~GameCore()
{
}


void GameCore::startGame()
{
    std::cout << "MONOPOLY GAME" << std::endl;
    std::cout << "Welcome to the Monopoly game!" << std::endl;
    int nbPlayers;
    do
    {
        std::cout << "Please enter the number of players (2-8): ";
        while(!(std::cin >> nbPlayers)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cout << "Please enter the number of players (2-8): \n";
        }
        if (nbPlayers < 2 || nbPlayers > 8)
        {
            std::cout << "Invalid number of players. Please enter a number between 2 and 8.\n" << std::endl;
        }
    } while (nbPlayers < 2 || nbPlayers > 8);

    for (int i = 0; i < nbPlayers; i++)
    {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        boardManager->getPlayerManager()->addPlayer(std::make_shared<Player>(name));
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter to start the game." << std::endl;
    std::cin.get();
    while (boardManager->getPlayerManager()->getNbPlayers() > 1){
        playTurn();
    }
    std::cout << "Game over!" << std::endl;
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
    std::cout << "Press Enter to roll the dice." << std::endl;
    std::cin.get();
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






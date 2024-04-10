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


Dice::Dice()
{
}

Dice::~Dice()
{
}

int Dice::roll(std::mt19937& gen)
{
    std::uniform_int_distribution<int> dist(1, 6);
    value = dist(gen);
    return value;
}

int Dice::getValue() const
{
    return value;
}

GameCore::GameCore(std::vector<Space*> spaces, std::vector<std::unique_ptr<CommunityChestCard>> communityChestCards, std::vector<std::unique_ptr<ChanceCard>> chanceCards)
    : boardManager(std::make_shared<BoardManager>(spaces, std::move(communityChestCards), std::move(chanceCards)))
{

}

GameCore::~GameCore()
{
}

// BoardManager GameCore::getBoardManager()
// {
//     return boardManager;
// }

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
            std::cout << "Please enter the number of players (2-8): ";
        }
        if (nbPlayers < 2 || nbPlayers > 8)
        {
            std::cout << "Invalid number of players. Please enter a number between 2 and 8." << std::endl;
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
}

void GameCore::playTurn(std::mt19937& gen)
{
    if (boardManager->getPlayerManager()->getCurrentPlayer()->getIsBankrupt())
    {
        // TODO: Handle bankrupt player
        boardManager->getPlayerManager()->setNextPlayer();
        return;
    }
    std::cout << "It is " << boardManager->getPlayerManager()->getCurrentPlayer()->getName() << "'s turn." << std::endl;
    std::cout << "Press Enter to roll the dice." << std::endl;
    std::cin.get();
    boardManager->rollDice(gen);
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
        playTurn(gen);
    }
    else
    {
        boardManager->getPlayerManager()->setNextPlayer();
        consecutiveDoubles = 0;
    }
}






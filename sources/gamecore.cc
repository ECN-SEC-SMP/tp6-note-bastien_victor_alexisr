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
#include "../utils/iomanager.h"



GameCore::GameCore(std::vector<std::shared_ptr<Space>> spaces, std::vector<std::unique_ptr<CommunityChestCard>> communityChestCards, std::vector<std::unique_ptr<ChanceCard>> chanceCards)
    : boardManager(std::make_shared<BoardManager>(spaces, std::move(communityChestCards), std::move(chanceCards)))
{
    std::ostringstream addressStream;
    addressStream << "GameCore created at address: " << static_cast<const void*>(this);
    logObject<std::string>(addressStream.str(), spdlog::level::debug);
}

GameCore::~GameCore()
{
}


void GameCore::startGame()
{
    spdlog::info("MONOPOLY GAME");
    spdlog::info("Welcome to the Monopoly game!");
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
    spdlog::info("Game over!");
    if (turns == 1000)
    {
        spdlog::info("The game has reached the maximum number of turns (1000).");
        return;
    }
    spdlog::info("The winner is {0}!", boardManager->getPlayerManager()->getPlayer(0)->getName());
}

void GameCore::playTurn()
{
    if (boardManager->getPlayerManager()->getCurrentPlayer() == nullptr)
    {
        boardManager->getPlayerManager()->setNextPlayer();
        return;
    }
    spdlog::info("It is {0}'s turn ({1}€).", boardManager->getPlayerManager()->getCurrentPlayer()->getName(), boardManager->getPlayerManager()->getCurrentPlayer()->getMoney());
    if (boardManager->getPlayerManager()->getCurrentPlayer()->getRemainingTurnsInJail() > 0){
        boardManager->handleSpace();
        boardManager->getPlayerManager()->setNextPlayer();
        return;
    }
    getEnter("Press Enter to roll the dice.");
    boardManager->rollDice();
    std::pair<int, int> dicesValue = boardManager->getCurrentDicesValue();
    spdlog::info("You rolled a {0} and a {1}.", dicesValue.first, dicesValue.second);
    boardManager->movePlayer(dicesValue.first + dicesValue.second);
    if (dicesValue.first == dicesValue.second)
    {
        consecutiveDoubles++;
        if (consecutiveDoubles == 3)
        {
            spdlog::info("You rolled 3 doubles in a row! Go to jail.");
            boardManager->getPlayerManager()->getCurrentPlayer()->setPosition(10);
            boardManager->handleSpace();
            boardManager->getPlayerManager()->setNextPlayer();
            consecutiveDoubles = 0;
            return;
        }
        spdlog::info("You rolled a double! You get to play again.");
        playTurn();
    }
    else
    {
        std::vector<std::shared_ptr<Property>> owned_groups = boardManager->getOwnedGroups(boardManager->getPlayerManager()->getCurrentPlayer());
        if (owned_groups.size() > 0){
            std::map<std::string, std::vector<std::shared_ptr<Property>>> propertiesByColor;
            for (const auto& property : owned_groups) {
                propertiesByColor[property->getColorString()].push_back(property);
            }
            std::map<std::string, std::vector<std::shared_ptr<Property>>> propertiesByColorFiltered;
            for (const auto& [color, properties] : propertiesByColor) {
                bool allHaveHotel = true;
                for (const auto& property : properties) {
                    if (property->getNbBuildings() != PropertyRent::HOTEL) {
                        allHaveHotel = false;
                        break;
                    }
                }
                if (allHaveHotel) {
                    propertiesByColorFiltered[color] = properties;
                }
            }
            propertiesByColor = propertiesByColorFiltered;
            if (propertiesByColor.size() > 0) {
                std::vector<std::string> colors;
                spdlog::info("You can build on the following properties:");
                for (const auto& [color, properties] : propertiesByColor) {
                    spdlog::info("Color: {0}", color);
                    colors.push_back(color);
                    for (int i = 0; i < properties.size(); i++) {
                        spdlog::info("  {0}. {1}", i + 1, properties[i]->getName());
                        PropertyRent buildings = properties[i]->getNbBuildings();
                        switch (buildings) {
                            case PropertyRent::FULL_GROUP:
                                spdlog::info("     - Buildings: None (Price of a house: {0}€)", properties[i]->getHousePrice());
                                break;
                            case PropertyRent::ONE_HOUSE:
                            case PropertyRent::TWO_HOUSES:
                            case PropertyRent::THREE_HOUSES:
                                spdlog::info("     - Buildings: {0} house(s) (Price of another house: {1}€/house)", static_cast<int>(buildings), properties[i]->getHousePrice());
                                break;
                            case PropertyRent::FOUR_HOUSES:
                                spdlog::info("     - Buildings: {0} house(s) (Price of a hotel: {1}€)", static_cast<int>(buildings), properties[i]->getHousePrice());
                                break;
                            case PropertyRent::HOTEL:
                                spdlog::info("     - Buildings: Hotel");
                                break;
                            case PropertyRent::BASE_RENT:
                                spdlog::error("    This should not happen.");
                                break;
                            default:
                                break;
                        }
                    }
                }
                char build = getYesNo("Do you want to build on a property? (y/n)");
                if (build == 'y')
                {   
                    std::string color = getString("Enter the color of the property you want to build on: ", colors);
                    if(propertiesByColor.count(color) > 0){
                        boardManager->buildOnProperties(propertiesByColor[color]);
                    }else{
                        spdlog::error("{0} is an invalid color.", color);
                    }
                }
            }
        }
        boardManager->getPlayerManager()->setNextPlayer();
        consecutiveDoubles = 0;
    }
}






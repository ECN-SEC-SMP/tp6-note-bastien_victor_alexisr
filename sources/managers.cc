/**
 * @file managers.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the management of players and buyable spaces
 * @version 0.1
 * @date 2024-03-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "managers.h"
#include <memory>
#include "../utils/iomanager.h"

Dice::Dice() : generator(std::random_device()()), distribution(1, 6) 
{
}


Dice::~Dice()
{
}

int Dice::roll()
{
    return distribution(generator);
}


PlayerManager::PlayerManager()
{
    std::ostringstream addressStream;
    addressStream << "PlayerManager created at address: " << static_cast<const void*>(this);
    logObject<std::string>(addressStream.str(), spdlog::level::debug);
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::addPlayer(std::shared_ptr<Player> player)
{
    players.push_back(player);
    if (currentPlayer == nullptr)
    {
        currentPlayer = player;
    }
}

void PlayerManager::removePlayer(std::shared_ptr<Player> player)
{
    for (auto it = players.begin(); it != players.end(); ++it)
    {
        if (*it == player)
        {
            players.erase(it);
            break;
        }
    }
}

std::shared_ptr<Player> PlayerManager::getPlayer(int index)
{
    return players[index];
}

int PlayerManager::getNbPlayers()
{
    return players.size();
}

std::shared_ptr<Player> PlayerManager::getCurrentPlayer()
{
    if (currentPlayer == nullptr) {
        spdlog::error("Current player is null!");
        return nullptr;
    }
    return currentPlayer;
}


void PlayerManager::setNextPlayer()
{
    int currentPlayerIndex = std::distance(players.begin(), std::find(players.begin(), players.end(), currentPlayer));
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    currentPlayer = players[currentPlayerIndex];
}

void PlayerManager::setCurrentPlayer(std::shared_ptr<Player> player)
{
    currentPlayer = player;
}

void PlayerManager::transferMoneyFromTo(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, int amount)
{
    if (player1 != nullptr)
    {
        player1->setMoney(player1->getMoney() - amount);
        spdlog::info("{0} has been debited of {1}€.", player1->getName(), amount);
        if (player1->getMoney() < 0)
        {
            player1->setMoney(0);
            spdlog::info("{0} is bankrupt.", player1->getName());
            removePlayer(player1);
        }
    }
    if (player2 != nullptr)
    {
        player2->setMoney(player2->getMoney() + amount); // In case of a bankrupcy from player1, we assume that the bank can add the missing money to player2 so that it still has the right amount of money
        spdlog::info("{0} has been credited of {1}€.", player2->getName(), amount);
    }
}

BoardManager::~BoardManager()
{
}

BoardManager::BoardManager(std::vector<std::shared_ptr<Space>> _board, std::vector<std::unique_ptr<CommunityChestCard>> _communityChestDeck, std::vector<std::unique_ptr<ChanceCard>> _chanceDeck)
    : board(_board), chanceDeck(std::move(_chanceDeck)), communityChestDeck(std::move(_communityChestDeck)), playerManager(std::make_shared<PlayerManager>())
{
    for (auto space : board) {
        if (auto property = std::dynamic_pointer_cast<Property>(space)) {
            Color color = property->getColor();
            properties[color].push_back(property);
        }
    }
    std::ostringstream addressStream;
    addressStream << "BoardManager created at address: " << static_cast<const void*>(this);
    logObject<std::string>(addressStream.str(), spdlog::level::debug);
}

std::shared_ptr<PlayerManager> BoardManager::getPlayerManager()
{
    return playerManager;
}

void BoardManager::drawChanceCard()
{
    if (chanceDeck.empty())
    {
        spdlog::error("Chance deck is empty.");
        return;
    }
    std::shuffle(chanceDeck.begin(), chanceDeck.end(), std::default_random_engine(std::random_device()()));
    std::unique_ptr<ChanceCard>& card = chanceDeck[0];
    if ((card->getDescription().find("Get Out of Jail Free") != std::string::npos) && chanceGOJFCTaken)
    {
        drawChanceCard();
        return;
    }
    card->action(shared_from_this());
}

void BoardManager::setChanceGOJFCTaken(bool taken)
{
    chanceGOJFCTaken = taken;
}


void BoardManager::drawCommunityChestCard() //TODO: if a player has a get ouf of jail card, make it unobtainable in the deck until it is used and then put it back in the deck
{
    if (communityChestDeck.empty())
    {
        spdlog::error("Community Chest deck is empty.");
        return;
    }
    std::shuffle(communityChestDeck.begin(), communityChestDeck.end(), std::default_random_engine(std::random_device()()));
    std::unique_ptr<CommunityChestCard>& card = communityChestDeck[0];
    if ((card->getDescription().find("Get Out of Jail Free") != std::string::npos) && chanceGOJFCTaken)
    {
        drawCommunityChestCard();
        return;
    }
    card->action(shared_from_this());
}

void BoardManager::setCommunityChestGOJFCTaken(bool taken)
{
    communityChestGOJFCTaken = taken;
}

std::vector<std::shared_ptr<Space>> BoardManager::getBoard()
{
    return board;
}

std::vector<std::shared_ptr<Property>> BoardManager::getOwnedGroups(std::shared_ptr<Player>player){
  std::vector<std::shared_ptr<Property>> owned_properties;

  for (const auto& [color, propertyList] : properties) {
      std::shared_ptr<Player> owner = player;
      bool sameOwner = true;

      for (const auto& property : propertyList) {
          if (property->getOwner() != owner) {
              sameOwner = false;
              break;
          }
      }

      if (sameOwner) {
          for(auto property : propertyList) {
              if (property->getNbBuildings() == PropertyRent::BASE_RENT){
                 property->setNbBuildings(PropertyRent::FULL_GROUP);
              }
              owned_properties.push_back(property);
          }
      }
  }
  return owned_properties;
}

void BoardManager::rollDice()
{
    currentDicesValue.first = dice1.roll();
    currentDicesValue.second = dice2.roll();
}

void BoardManager::movePlayer(int distanceToGo)//TODO: handle bug when a player goes back 3 spaces with chanceCard
{
    std::shared_ptr<Player> player = playerManager->getCurrentPlayer();
    spdlog::debug("{0} is currently on {1}.", player->getName(), board[player->getPosition()]->getName());
    if (player == nullptr){
        spdlog::error("Player is null.");
        return;
    }
    int newPosition = (player->getPosition() + distanceToGo) % board.size();
    spdlog::debug("{0} moved to {1}.", player->getName(), board[newPosition]->getName());
    if ((newPosition < 0) || (newPosition >= static_cast<int>(board.size()))) {
        // Handle out-of-bounds position
        spdlog::error("New position is out of bounds.");
        return;
    }
    if(newPosition < player->getPosition() && player->getRemainingTurnsInJail() == 0 && distanceToGo > 0){
        spdlog::info("{0} passed by the Go space and earned 200.", player->getName());
        playerManager->transferMoneyFromTo(nullptr, player, 200);
    }
    spdlog::info("Moving player...");
    player->setPosition(newPosition);
    handleSpace();
}

void BoardManager::affectProperty(std::shared_ptr<Player> player, std::shared_ptr<Space> space)
{
    std::shared_ptr<BuyableSpace> buyableSpace = std::dynamic_pointer_cast<BuyableSpace>(space);
    if (buyableSpace != nullptr) {
        buyableSpace->setOwner(player);
    }
}

void BoardManager::buildOnProperties(std::vector<std::shared_ptr<Property>> properties, int attempts)
{
    if (attempts > 10) {
        spdlog::error("Too many attempts. Exiting.");
        return;
    }

    std::map<std::shared_ptr<Property>, int> buildingsPerProperty;
    int minBuildings = INT_MAX;
    int maxBuildings = INT_MIN;

    for (const auto& property : properties) {
        int currentBuildings = static_cast<int>(property->getNbBuildings());
        int newBuildings = getNumber("Enter the number of additional buildings you want to build on " + property->getName() + ": ", 0, 5 - currentBuildings);
        int totalBuildings = currentBuildings + newBuildings;
        spdlog::debug("Theoretical number of buildings: {0}.", totalBuildings);
        if (totalBuildings == 5) {
            spdlog::info("You have chosen to build a hotel on {0}.", property->getName());
        } else {
            spdlog::info("You have chosen to build {0} house(s) on {1}.", newBuildings, property->getName());
        }
        buildingsPerProperty[property] = totalBuildings;
        minBuildings = std::min(minBuildings, totalBuildings);
        maxBuildings = std::max(maxBuildings, totalBuildings);
    }

    if (maxBuildings - minBuildings > 1) {
        spdlog::error("There is a difference of more than 1 building between some properties.");
        return buildOnProperties(properties, attempts + 1);
    }

    for (const auto& [property, totalBuildings] : buildingsPerProperty) {
        property->setNbBuildings(static_cast<PropertyRent>(totalBuildings));
        spdlog::info("{0} now has {1} {2}.", property->getName(), totalBuildings == 5 ? 1 : totalBuildings, totalBuildings == 5 ? "hotel" : "house(s)");
    }
}

void BoardManager::handleSpace()
{
    std::shared_ptr<Player> player = playerManager->getCurrentPlayer();
    std::shared_ptr<Space> space = board[player->getPosition()];
    spdlog::info("{0} is now on {1} ({2}).", player->getName(), space->getName(), player->getPosition());
    space->action(shared_from_this());
}

std::pair<int, int> BoardManager::getCurrentDicesValue()
{
    return currentDicesValue;
}
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
    // std::cout << "PlayerManager created at address: " << this << std::endl;
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
        std::cout << "Current player is null!" << std::endl;
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
        std::cout << player1->getName() << " has been debited of " << amount << "€." << std::endl;
        if (player1->getMoney() < 0)
        {
            player1->setMoney(0);
            std::cout << player1->getName() << " is bankrupt." << std::endl;
            removePlayer(player1);
        }
    }
    if (player2 != nullptr)
    {
        player2->setMoney(player2->getMoney() + amount); // In case of a bankrupcy from player1, we assume that the bank can add the missing money to player2 so that it still has the right amount of money
        std::cout << player2->getName() << " has been credited of " << amount << "€." << std::endl;
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
}

std::shared_ptr<PlayerManager> BoardManager::getPlayerManager()
{
    return playerManager;
}

void BoardManager::drawChanceCard()
{
    if (chanceDeck.empty())
    {
        std::cerr << "Chance deck is empty." << std::endl;
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
        std::cerr << "Community Chest deck is empty." << std::endl;
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
              if (property->getNbBuildings() < PropertyRent::FULL_GROUP){
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
    // std::cout << "current position: " << player->getPosition() << std::endl;
    // std::cout << player->getName() << " is currently on " << board[player->getPosition()]->getName() << "." << std::endl;
    if (player == nullptr){
        std::cerr << "Player is null." << std::endl;
        return;
    }
    int newPosition = (player->getPosition() + distanceToGo) % board.size();
    // std::cout << player->getName() << " moved to " << board[newPosition]->getName() << "." << std::endl;
    if ((newPosition < 0) || (newPosition >= static_cast<int>(board.size()))) {
        // Handle out-of-bounds position
        std::cerr << "New position is out of bounds." << std::endl;
        return;
    }
    if(newPosition < player->getPosition() && player->getRemainingTurnsInJail() == 0 && distanceToGo > 0){
        std::cout << player->getName() << " passed by the Go space and earned 200." << std::endl;
        playerManager->transferMoneyFromTo(nullptr, player, 200);
    }
    std::cout << "Moving player... " << std::endl;
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

void BoardManager::handleSpace()
{
    std::shared_ptr<Player> player = playerManager->getCurrentPlayer();
    std::shared_ptr<Space> space = board[player->getPosition()];
    std::cout << player->getName() << " is now on " << space->getName() << " (" << player->getPosition() << ")." << std::endl;
    space->action(shared_from_this());
}

std::pair<int, int> BoardManager::getCurrentDicesValue()
{
    return currentDicesValue;
}
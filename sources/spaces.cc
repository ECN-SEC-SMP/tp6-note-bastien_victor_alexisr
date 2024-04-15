/**
 * @file spaces.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the spaces of the board. All types of spaces inherit from this class
 * @version 0.1
 * @date 2024-03-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "spaces.h"
#include <iostream>

Space::Space(std::string _name) : name(_name)
{
}

Space::~Space()
{
}

std::string Space::getName() const
{
    return name;
}

BuyableSpace::BuyableSpace(std::string _name, int _price, std::vector<int> _rent) : Space(_name), price(_price), rent(_rent), owner(nullptr)
{
}

BuyableSpace::~BuyableSpace()
{
}

int BuyableSpace::getPrice() const
{
    return price;
}

std::shared_ptr<Player> BuyableSpace::getOwner() const
{
    return owner;
}

void BuyableSpace::setOwner(std::shared_ptr<Player> _owner)
{
    owner = _owner;
}

std::vector<int> BuyableSpace::getRent() const
{
    return rent;
}

std::string colorToString(Color color){
    switch (color)
    {
    case Color::PURPLE:
        return "Purple";
        break;
    case Color::LIGHT_BLUE:
        return "Light Blue";
        break;
    case Color::PINK:
        return "Pink";
        break;
    case Color::ORANGE:
        return "Orange";
        break;
    case Color::RED:
        return "Red";
        break;
    case Color::YELLOW:
        return "Yellow";
        break;
    case Color::GREEN:
        return "Green";
        break;
    case Color::BLUE:
        return "Blue";
        break;
    default:
        return "Unknown";
        break;
    }
}

Property::Property(std::string _name, Color _color, int _price, int _housePrice, std::vector<int> _rent) : BuyableSpace(_name, _price, _rent), housePrice(_housePrice), color(_color), nbBuildings(PropertyRent::NO_HOUSE)
{
}

Property::~Property()
{
}

void Property::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    if (getOwner() != nullptr)
    {
        if (getOwner() == player){
            std::cout << "You own this property" << std::endl;
            return;
        }
        // Pay rent
        // TODO: Implement the reset of a property that was owned by a now bankrupt player
        std::cout << "This property is owned by " << getOwner()->getName() << std::endl;
        int rent = getRent()[static_cast<int>(nbBuildings)];
        std::cout << player->getName() << " needs to pay " << rent << " to " << getOwner()->getName() << std::endl;
        board->getPlayerManager()->transferMoneyFromTo(player, getOwner(), rent);

    }
    else
    {
        std::cout << "This property is not owned" << std::endl;
        std::cout << *this << std::endl;
        std::cout << "Do you want to buy it for " << getPrice() << " ? [y/n]" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'y')
        {
            if (player->getMoney() < getPrice())
            {
                std::cout << "You don't have enough money to buy this property" << std::endl;
            }
            else
            {
                board->getPlayerManager()->transferMoneyFromTo(player, nullptr, getPrice());
                board->affectProperty(player, shared_from_this());
                std::cout << "You now own this property" << std::endl;
            }
        }
        else
        {
            // Auction
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

PropertyRent Property::getNbBuildings() const
{
    return nbBuildings;
}

void Property::setNbBuildings(PropertyRent _nbBuildings)
{
    nbBuildings = _nbBuildings;
}

Color Property::getColor() const
{
    return color;
}

std::ostream& operator<<(std::ostream& os, const Property& property)
{
    os << "Space Type: Property" << std::endl;
    os << "Property Name: " << property.getName() << std::endl;
    os << "Property Color: " << colorToString(property.getColor()) << std::endl;
    os << "Property Price: " << property.getPrice() << std::endl;
    os << "Property Rent: " << std::endl;
    for (int i = 0; i < property.getRent().size() - 1; i++)
    {
        os << "     With ";
        if (i == 0)
        {
            os << "no house: ";
        }
        else if (i == 5)
        {
            os << "a hotel: ";
        }
        else
        {
            os << i << " house(s): ";
        }
        os << property.getRent()[i] << std::endl;
    }
    os << "Property House Price: " << property.housePrice << std::endl;
    return os;
}

Station::Station(std::string _name) : BuyableSpace(_name, 200, {25, 50, 100, 200})
{
}

Station::~Station()
{
}

void Station::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    if (getOwner() != nullptr)
    {
        if (getOwner() == player){
            std::cout << "You own this station" << std::endl;
            return;
        }
        // Pay rent
        // TODO: Implement the reset of a station that was owned by a now bankrupt player
        std::cout << "This station is owned by " << getOwner()->getName() << std::endl;
        int rent = getRent()[getOwner()->getNbStationsOwned() - 1];
        std::cout << getOwner()->getName() << " owns " << getOwner()->getNbStationsOwned() << " station(s)" << std::endl;
        std::cout << player->getName() << " needs to pay " << rent << " to " << getOwner()->getName() << std::endl;
        board->getPlayerManager()->transferMoneyFromTo(player, getOwner(), rent);
    }
    else
    {
        std::cout << "This station is not owned" << std::endl;
        std::cout << *this << std::endl;
        std::cout << "Do you want to buy it for " << getPrice() << " ? [y/n]" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'y')
        {
            if (player->getMoney() < getPrice())
            {
                std::cout << "You don't have enough money to buy this station" << std::endl;
            }
            else
            {
                board->getPlayerManager()->transferMoneyFromTo(player, nullptr, getPrice());
                board->affectProperty(player, shared_from_this());
                std::cout << "You now own this this station" << std::endl;
                player->setNbStationsOwned(player->getNbStationsOwned() + 1);
            }
        }
        else
        {
            // Auction
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::ostream& operator<<(std::ostream& os, const Station& station)
{
    os << "Space Type: Station" << std::endl;
    os << "Station Name: " << station.getName() << std::endl;
    os << "Station Price: " << station.getPrice() << std::endl;
    os << "Station Rent: " << std::endl;
    for (int i = 0; i < station.getRent().size(); i++)
    {
        os << "     With " << i << " station(s): ";
        if (i < station.getRent().size())
        {
            os << station.getRent()[i];
        }
        else
        {
            os << "N/A";
        }
        os << std::endl;
    }
    return os;
}

Utility::Utility(std::string _name) : BuyableSpace(_name, 150, {})
{
}

Utility::~Utility()
{
}

void Utility::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    if (getOwner() != nullptr)
    {
        if (getOwner() == player){
            std::cout << "You own this utility" << std::endl;
            return;
        }
        // Pay rent
        std::cout << "This utility is owned by " << getOwner()->getName() << std::endl;
        std::pair<int, int> dicesValue = board->getCurrentDicesValue();
        std::cout << "You rolled a " << dicesValue.first + dicesValue.second << std::endl;
        int rent = (dicesValue.first + dicesValue.second) * (getOwner()->getNbUtilitiesOwned() == 1 ? 4 : 10);
        std::cout << player->getName() << " needs to pay " << rent << " to " << getOwner()->getName() << std::endl;
        board->getPlayerManager()->transferMoneyFromTo(player, getOwner(), rent);
    }
    else
    {
        std::cout << "This utility is not owned" << std::endl;
        std::cout << *this << std::endl;
        std::cout << "Do you want to buy it for " << getPrice() << " ? [y/n]" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'y')
        {
            if (player->getMoney() < getPrice())
            {
                std::cout << "You don't have enough money to buy this utility" << std::endl;
            }
            else
            {
                board->getPlayerManager()->transferMoneyFromTo(player, nullptr, getPrice());
                board->affectProperty(player, shared_from_this());
                std::cout << "You now own this utility" << std::endl;
                player->setNbUtilitiesOwned(player->getNbUtilitiesOwned() + 1);
            }
        }
        else
        {
            // Auction
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

std::ostream& operator<<(std::ostream& os, const Utility& utility)
{
    os << "Space Type: Utility" << std::endl;
    os << "Utility Name: " << utility.getName() << std::endl;
    os << "Utility Price: " << utility.getPrice() << std::endl;
    os << "Utility Rent: "<< std::endl; 
    os << "     4x the dice roll if one utility is owned, or 10x the dice value if both are owned" << std::endl;
    return os;
}

Tax::Tax(std::string _name, int _amount) : Space(_name), amount(_amount)
{
}

Tax::~Tax()
{
}

int Tax::getAmount() const
{
    return amount;
}

void Tax::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    std::cout << player->getName() << " needs to pay " << amount << " to the bank" << std::endl;
    board->getPlayerManager()->transferMoneyFromTo(player, nullptr, amount);

}

std::ostream& operator<<(std::ostream& os, const Tax& tax)
{
    os << "Space Type: Tax" << std::endl;
    os << "Tax Name: " << tax.getName() << std::endl;
    os << "Tax Amount: " << tax.getAmount() << std::endl;
    return os;
}

Jail::Jail() : Space("Jail")
{
}

Jail::~Jail()
{
}

void Jail::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    if (player->getRemainingTurnsInJail() > 0)
    {
        std::cout << "You are stuck in jail for " << player->getRemainingTurnsInJail() << " turn(s)" << std::endl;
        if (player->getHasGetOutOfJailCard())
        {
            std::cout << "Do you want to use your Get Out of Jail Free card? [y/n]" << std::endl;
            char answer;
            std::cin >> answer;
            if (answer == 'y')
            {
                player->setRemainingTurnsInJail(0);
                player->setHasGetOutOfJailCard(false);
                std::cout << "You used your card and are free to go" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
        std::cout << "Do you want to pay 50 to get out of jail? [y/n]" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'y')
        {
            if (player->getMoney() < 50)
            {
                std::cout << "You don't have enough money to pay the fine" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                board->getPlayerManager()->transferMoneyFromTo(player, nullptr, 50);
                player->setRemainingTurnsInJail(0);
                std::cout << "You are free to go" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
        else
        {
            std::cout << "Roll the dice and get a double to get out of jail" << std::endl;
            board->rollDice();
            std::pair<int, int> dicesValue = board->getCurrentDicesValue();
            std::cout << "You rolled a " << dicesValue.first << " and a " << dicesValue.second << "." << std::endl;
            if (dicesValue.first == dicesValue.second)
            {
                player->setRemainingTurnsInJail(0);
                std::cout << "You rolled a double are free to go!" << std::endl;
                return;
            }else{
                std::cout << "You didn't get a double" << std::endl;
            }
        }
        player->setRemainingTurnsInJail(player->getRemainingTurnsInJail() - 1);
        std::cout << "You have " << player->getRemainingTurnsInJail() << " turn(s) left in jail" << std::endl;
    }
    else
    {
        std::cout << "You have served your sentence and are free to go!" << std::endl;
    }
} 

std::ostream& operator<<(std::ostream& os, const Jail& jail)
{
    os << "Space Type: Jail" << std::endl;
    return os;
}

GoToJail::GoToJail() : Space("Go To Jail")
{
}

GoToJail::~GoToJail()
{
}

void GoToJail::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    std::cout << "You are going to jail" << std::endl;
    player->setRemainingTurnsInJail(3); // TODO: Fix the fact that it seems like the counter is not working
    board->movePlayer(20);
}

std::ostream& operator<<(std::ostream& os, const GoToJail& goToJail)
{
    os << "Space Type: Go To Jail" << std::endl;
    return os;
}

FreeParking::FreeParking() : Space("Free Parking")
{
}

FreeParking::~FreeParking()
{
}

void FreeParking::action(std::shared_ptr<BoardManager> board)
{
    std::cout << "You landed on Free Parking" << std::endl;
    std::cout << "There is nothing to do here, enjoy your stay" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const FreeParking& freeParking)
{
    os << "Space Type: Free Parking" << std::endl;
    return os;
}

Go::Go() : Space("Go")
{
}

Go::~Go()
{
}

void Go::action(std::shared_ptr<BoardManager> board)
{
    std::shared_ptr<Player> player = board->getPlayerManager()->getCurrentPlayer();
    std::cout << player->getName() << " landed exactly on the Go space and earned an extra 200" << std::endl;
    board->getPlayerManager()->transferMoneyFromTo(nullptr, player, 200);
}

std::ostream& operator<<(std::ostream& os, const Go& go)
{
    os << "Space Type: Go" << std::endl;
    return os;
}

CommunityChest::CommunityChest() : Space("Community Chest")
{
}

CommunityChest::~CommunityChest()
{
}

void CommunityChest::action(std::shared_ptr<BoardManager> board)
{
    board->drawCommunityChestCard();
}

std::ostream& operator<<(std::ostream& os, const CommunityChest& communityChest)
{
    os << "Space Type: Community Chest" << std::endl;
    return os;
}

Chance::Chance() : Space("Chance")
{
}

Chance::~Chance()
{
}

void Chance::action(std::shared_ptr<BoardManager> board)
{
    board->drawChanceCard();
}


std::ostream& operator<<(std::ostream& os, const Chance& chance)
{
    os << "Space Type: Chance" << std::endl;
    return os;
}


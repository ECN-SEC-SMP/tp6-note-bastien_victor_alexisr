/**
 * @file spaces.cpp
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the spaces of the board. All types of spaces inherit from this class
 * @version 0.1
 * @date 2024-03-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "spaces.hpp"

Space::Space(std::string _name) : name(_name)
{
}

Space::~Space()
{
}

std::string Space::getName()
{
    return name;
}

BuyableSpace::BuyableSpace(std::string _name, int _price, std::vector<int> _rent) : Space(_name), price(_price), rent(_rent), owned(false)
{
}

BuyableSpace::~BuyableSpace()
{
}

int BuyableSpace::getPrice()
{
    return price;
}

bool BuyableSpace::isOwned()
{
    return owned;
}

Property::Property(std::string _name, Color _color, int _price, std::vector<int> _rent) : BuyableSpace(_name, _price, _rent), color(_color)
{
}

Property::~Property()
{
}

void Property::action(Player* player)
{
    if (isOwned())
    {
        // Pay rent
    }
    else
    {
        // Ask player if he wants to buy the property, if not, auction
    }
}

int Property::getRent()
{
    return rent[nbHouses];
}

int Property::getNbHouses()
{
    return nbHouses;
}

void Property::setNbHouses(int _nbHouses)
{
    if (_nbHouses >= 0 && _nbHouses <= 5)
    {
        nbHouses = static_cast<PropertyRent>(_nbHouses);
    }
}

Station::Station(std::string _name) : BuyableSpace(_name, 200, {25, 50, 100, 200})
{
}

Station::~Station()
{
}

void Station::action(Player* player)
{
    if (isOwned())
    {
        // Pay rent
    }
    else
    {
        // Ask player if he wants to buy the station, if not, auction
    }
}

int Station::getRent()
{
    // Rent is based on the number of stations owned by the player
    return rent[0];
}

Utility::Utility(std::string _name) : BuyableSpace(_name, 150, {0})
{
}

Utility::~Utility()
{
}

void Utility::action(Player* player)
{
    if (isOwned())
    {
        // Pay rent
    }
    else
    {
        // Ask player if he wants to buy the utility, if not, auction
    }
}

int Utility::getRent()
{
    // Rent is calculated based on the dice roll made by the player
    return rent;
}

Tax::Tax(std::string _name, int _amount) : Space(_name), amount(_amount)
{
}

Tax::~Tax()
{
}

int Tax::getAmount()
{
    return amount;
}

void Tax::action(Player* player)
{
    // Pay tax
}

Jail::Jail() : Space("Jail")
{
}

Jail::~Jail()
{
}

void Jail::action(Player* player)
{
    // TODO
}

GoToJail::GoToJail() : Space("Go To Jail")
{
}

GoToJail::~GoToJail()
{
}

void GoToJail::action(Player* player)
{
    // Go to jail
}

FreeParking::FreeParking() : Space("Free Parking")
{
}

FreeParking::~FreeParking()
{
}

void FreeParking::action(Player* player)
{
    // Do nothing
}

Go::Go() : Space("Go")
{
}

Go::~Go()
{
}

void Go::action(Player* player)
{
    // Get 200 if you pass by and 400 if you land on it
}

CommunityChest::CommunityChest() : Space("Community Chest")
{
}

CommunityChest::~CommunityChest()
{
}

void CommunityChest::action(Player* player)
{
    // Draw a card
}

Chance::Chance() : Space("Chance")
{
}

Chance::~Chance()
{
}

void Chance::action(Player* player)
{
    // Draw a card
}


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

Player* BuyableSpace::getOwner() const
{
    return owner;
}

void BuyableSpace::setOwner(Player* _owner)
{
    owner = _owner;
}

std::vector<int> BuyableSpace::getRent() const
{
    // Rent is calculated based on the dice roll made by the player
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

Property::Property(std::string _name, Color _color, int _price, std::vector<int> _rent) : BuyableSpace(_name, _price, _rent), color(_color), nbBuildings(PropertyRent::NO_HOUSE)
{
}

Property::~Property()
{
}

void Property::action(Player* player)
{
    if (getOwner() != nullptr && getOwner() != player)
    {
        // Pay rent
    }
    else
    {
        // Ask player if he wants to buy the property, if not, auction
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
    return os;
}

Station::Station(std::string _name) : BuyableSpace(_name, 200, {25, 50, 100, 200})
{
}

Station::~Station()
{
}

void Station::action(Player* player)
{
    if (getOwner() != nullptr && getOwner() != player)
    {
        // Pay rent
    }
    else
    {
        // Ask player if he wants to buy the station, if not, auction
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

Utility::Utility(std::string _name) : BuyableSpace(_name, 150, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12})
{
}

Utility::~Utility()
{
}

void Utility::action(Player* player)
{
    if (getOwner() != nullptr && getOwner() != player)
    {
        // Pay rent
    }
    else
    {
        // Ask player if he wants to buy the utility, if not, auction
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

void Tax::action(Player* player)
{
    // Pay tax
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

void Jail::action(Player* player)
{
    // TODO
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

void GoToJail::action(Player* player)
{
    // Go to jail
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

void FreeParking::action(Player* player)
{
    // Do nothing
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

void Go::action(Player* player)
{
    // Get 200 if you pass by and 400 if you land on it
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

void CommunityChest::action(Player* player)
{
    // Draw a card
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

void Chance::action(Player* player)
{
    // Draw a card
}

std::ostream& operator<<(std::ostream& os, const Chance& chance)
{
    os << "Space Type: Chance" << std::endl;
    return os;
}


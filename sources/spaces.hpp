/**
 * @file spaces.hpp
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the spaces of the board. All types of spaces inherit from this class
 * @version 0.1
 * @date 2024-03-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SPACES_HPP
#define SPACES_HPP

#include "player.hpp"
#include <vector>

class Space
{
    private:
        std::string name;
    public:
        Space(std::string _name);
        ~Space();
        std::string getName();
        virtual void action(Player* player) = 0;
};

class BuyableSpace : public Space
{
    private:
        int price;
        std::vector<int> rent;
        bool owned;
    public:
        BuyableSpace(std::string _name, int _price, std::vector<int> _rent);
        ~BuyableSpace();
        int getPrice();
        bool isOwned();
        virtual void action(Player* player) = 0;
        virtual int getRent() = 0;
};

enum Color
{
    PURPLE,
    LIGHT_BLUE,
    PINK,
    ORANGE,
    RED,
    YELLOW,
    GREEN,
    BLUE
};

enum PropertyRent
{
    NO_HOUSE,
    ONE_HOUSE,
    TWO_HOUSES,
    THREE_HOUSES,
    FOUR_HOUSES,
    HOTEL
};

class Property : public BuyableSpace
{
    private:
        PropertyRent nbHouses;
        Color color;
        std::vector<int> rent; // Price for a property with no house, 1 house, 2 houses, 3 houses, 4 houses, a hotel
    public:
        Property(std::string _name, Color _color, int _price, std::vector<int> _rent);
        ~Property();
        int getRent();
        int getNbHouses();
        void setNbHouses(int _nbHouses); 
        void action(Player* player);
};


class Station : public BuyableSpace
{
    private:
        std::vector<int> rent = {25, 50, 100, 200}; // Rent is based on the number of stations owned by the player
        int price = 200;
    public:
        Station(std::string _name); 
        ~Station();
        int getRent();
        void action(Player* player);
};

class Utility : public BuyableSpace
{
    private:
        int rent; // Rent is calculated based on the dice roll made by the player
        int price = 150;
        std::string name;
    public:
        Utility(std::string _name);
        ~Utility();
        int getRent();
        void action(Player* player);
};

class Tax : public Space
{
    private:
        std::string name;
        int amount;
    public:
        Tax(std::string _name, int _amount);
        ~Tax();
        int getAmount();
        void action(Player* player);
};

class Jail : public Space
{
    private:
        std::string name = "Jail";
    public:
        Jail();
        ~Jail();
        void action(Player* player);
};

class GoToJail : public Space
{
    private:
        std::string name = "Go To Jail";
    public:
        GoToJail();
        ~GoToJail();
        void action(Player* player);
};

class FreeParking : public Space
{
    private:
        std::string name = "Free Parking";
    public:
        FreeParking();
        ~FreeParking();
        void action(Player* player);
};

class Go : public Space
{
    private:
        std::string name = "Go";
    public:
        Go();
        ~Go();
        void action(Player* player);
};

class CommunityChest : public Space
{
    private:
        std::string name = "Community Chest";
    public:
        CommunityChest();
        ~CommunityChest();
        void action(Player* player);
};

class Chance : public Space
{
    private:
        std::string name = "Chance";
    public:
        Chance();
        ~Chance();
        void action(Player* player);
};




#endif // SPACES_HPP
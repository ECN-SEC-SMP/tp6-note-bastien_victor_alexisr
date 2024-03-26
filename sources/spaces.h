/**
 * @file spaces.h
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the spaces of the board. All types of spaces inherit from this class
 * @version 0.1
 * @date 2024-03-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SPACES_H
#define SPACES_H

#include "player.h"
#include <vector>



class Space
{
    private:
        std::string name;
    public:
        Space(std::string _name);
        ~Space();
        std::string getName() const;
        virtual void action(Player* player) = 0;
};

class BuyableSpace : public Space
{
    private:
        int price;
        std::vector<int> rent;
        Player* owner;
    public:
        BuyableSpace(std::string _name, int _price, std::vector<int> _rent);
        ~BuyableSpace();
        int getPrice() const;
        Player* getOwner() const;
        void setOwner(Player* _owner);
        std::vector<int> getRent() const;
        virtual void action(Player* player) = 0;
};

enum class Color
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



enum class PropertyRent
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
        PropertyRent nbBuildings;
        Color color;
    public:
        Property(std::string _name, Color _color, int _price, std::vector<int> _rent);
        ~Property();
        Color getColor() const;
        PropertyRent getNbBuildings() const;
        void setNbBuildings(PropertyRent _nbBuildings); 
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Property& property);
};


class Station : public BuyableSpace
{
    private:
        int price = 200;
    public:
        Station(std::string _name); 
        ~Station();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Station& station);
};

class Utility : public BuyableSpace
{
    private:
        int price = 150;
    public:
        Utility(std::string _name);
        ~Utility();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Utility& utility);
};

class Tax : public Space
{
    private:
        std::string name;
        int amount;
    public:
        Tax(std::string _name, int _amount);
        ~Tax();
        int getAmount() const;
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Tax& tax);
};

class Jail : public Space
{
    private:
        std::string name = "Jail";
    public:
        Jail();
        ~Jail();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Jail& jail);
};

class GoToJail : public Space
{
    private:
        std::string name = "Go To Jail";
    public:
        GoToJail();
        ~GoToJail();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const GoToJail& goToJail);
};

class FreeParking : public Space
{
    private:
        std::string name = "Free Parking";
    public:
        FreeParking();
        ~FreeParking();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const FreeParking& freeParking);
};

class Go : public Space
{
    private:
        std::string name = "Go";
    public:
        Go();
        ~Go();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Go& go);
};

class CommunityChest : public Space
{
    private:
        std::string name = "Community Chest";
    public:
        CommunityChest();
        ~CommunityChest();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const CommunityChest& communityChest);
};

class Chance : public Space
{
    private:
        std::string name = "Chance";
    public:
        Chance();
        ~Chance();
        void action(Player* player);
        friend std::ostream& operator<<(std::ostream& os, const Chance& chance);
};




#endif // SPACES_H
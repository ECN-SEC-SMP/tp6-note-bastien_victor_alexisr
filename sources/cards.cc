/**
 * @file cards.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the cards
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "cards.h"


Card::Card(std::string _description) : description(_description) {}

Card::~Card() {}

std::string Card::getDescription() const
{
    return description;
}



CommunityChestCard::CommunityChestCard(std::string _description, std::function<void(std::shared_ptr<BoardManager>)> _action) : Card(_description)  
{
    _actionFunction = _action;  
}
CommunityChestCard::~CommunityChestCard() {}

void CommunityChestCard::action(std::shared_ptr<BoardManager> board)
{
    if (_actionFunction)
    {
        std::cout << "Community Chest Card: " << getDescription() << std::endl;
        _actionFunction(board);
    }
}


std::ostream& operator<<(std::ostream& os, const CommunityChestCard& card)
{
    os << card.getDescription();
    return os;
}

ChanceCard::ChanceCard(std::string _description, std::function<void(std::shared_ptr<BoardManager> )> _action) : Card(_description) 
{
    _actionFunction = _action;
}

ChanceCard::~ChanceCard() {}

void ChanceCard::action(std::shared_ptr<BoardManager>  board)
{
    if (_actionFunction)
    {
        std::cout << "Chance Card: " << getDescription() << std::endl;
        _actionFunction(board);
    }
}

std::ostream& operator<<(std::ostream& os, const ChanceCard& card)
{
    os << card.getDescription();
    return os;
}
/**
 * @file cards.h
 * @author Bastien, Victor, AlexisR 
 * @brief Class handling the cards
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <memory>

class BoardManager; // Forward declaration
class Card
{
    private:
        std::string description;
    protected:
        std::function<void(std::shared_ptr<BoardManager> )> _actionFunction;
    public:
        Card(std::string _description);
        ~Card();
        std::string getDescription() const;
        virtual void action(std::shared_ptr<BoardManager> board) = 0;
};

class CommunityChestCard : public Card
{
    public:
        CommunityChestCard(std::string _description, std::function<void(std::shared_ptr<BoardManager> )> _actionFunction);
        ~CommunityChestCard();
        void action(std::shared_ptr<BoardManager> board) override;
        friend std::ostream& operator<<(std::ostream& os, const CommunityChestCard& card);
};

class ChanceCard : public Card
{
    public:
        ChanceCard(std::string _description, std::function<void(std::shared_ptr<BoardManager> )> _actionFunction);
        ~ChanceCard();
        void action(std::shared_ptr<BoardManager> board) override;
        friend std::ostream& operator<<(std::ostream& os, const ChanceCard& card);
};

#endif // CARDS_H
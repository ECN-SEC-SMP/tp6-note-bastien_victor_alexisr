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
        // virtual void setAction(std::function<void(std::shared_ptr<BoardManager> )> _action) = 0;
};

class CommunityChestCard : public Card
{
    public:
        CommunityChestCard(std::string _description, std::function<void(std::shared_ptr<BoardManager> )> _actionFunction);
        ~CommunityChestCard();
        void action(std::shared_ptr<BoardManager> board) override;
        // void setAction(std::function<void(std::shared_ptr<BoardManager> )> _action) override;
        friend std::ostream& operator<<(std::ostream& os, const CommunityChestCard& card);
};

class ChanceCard : public Card
{
    public:
        ChanceCard(std::string _description, std::function<void(std::shared_ptr<BoardManager> )> _actionFunction);
        ~ChanceCard();
        void action(std::shared_ptr<BoardManager> board) override;
        // void setAction(std::function<void(std::shared_ptr<BoardManager> )> _action) override;
        friend std::ostream& operator<<(std::ostream& os, const ChanceCard& card);
};

// template <typename T>
// class Deck
// {
//     private:
//         std::vector<std::shared_ptr<T>> cards;
//     public:
//         Deck();
//         ~Deck();
//         void addCard(const T& card);
//         void removeCard(T* card);
//         T* pickCard() const;
//         std::vector<T*> getCards() const;
//         void shuffle(std::mt19937& gen);
//         friend std::ostream& operator<<(std::ostream& os, const Deck<T>& deck);
// };

// template <typename T>
// Deck<T>::Deck() {}

// template <typename T>
// Deck<T>::~Deck() {}

// template <typename T>
// void Deck<T>::addCard(const T& card)
// {
//     cards.push_back(std::make_shared<T>(card));
// }

// template <typename T>
// void Deck<T>::removeCard(T* card) {
//     auto it = std::find(cards.begin(), cards.end(), card);
//     if (it != cards.end()) {
//         cards.erase(it);
//     } else {
//         throw std::runtime_error("Card not found in the deck");
//     }
// }

// template <typename T>
// T* Deck<T>::pickCard() const
// {
//     return cards[0];
// }

// template <typename T>
// std::vector<T*> Deck<T>::getCards() const
// {
//     return cards;
// }

// template <typename T>
// void Deck<T>::shuffle(std::mt19937& gen)
// {
//     std::shuffle(cards.begin(), cards.end(), gen);
// }

// template <typename T>
// std::ostream& operator<<(std::ostream& os, const Deck<T>& deck)
// {
//     for (T* card : deck.getCards())
//     {
//         os << *card << std::endl;
//     }
//     return os;
// }

#endif // CARDS_H
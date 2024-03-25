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


class Card
{
    private:
        std::string description;
    public:
        Card(std::string _description);
        ~Card();
        std::string getDescription() const;
        virtual void action() = 0;
};

class CommunityChestCard : public Card
{
    public:
        CommunityChestCard(std::string _description);
        ~CommunityChestCard();
        void action();
        friend std::ostream& operator<<(std::ostream& os, const CommunityChestCard& card);
};

class ChanceCard : public Card
{
    public:
        ChanceCard(std::string _description);
        ~ChanceCard();
        void action();
        friend std::ostream& operator<<(std::ostream& os, const ChanceCard& card);
};

template <typename T>
class Deck
{
    private:
        std::vector<T*> cards;
    public:
        Deck();
        ~Deck();
        void addCard(T* card);
        void removeCard(T* card);
        T* pickCard() const;
        std::vector<T*> getCards() const;
        void shuffle(std::mt19937& gen);
        friend std::ostream& operator<<(std::ostream& os, const Deck<T>& deck);
};

template <typename T>
Deck<T>::Deck() {}

template <typename T>
Deck<T>::~Deck() {}

template <typename T>
void Deck<T>::addCard(T* card)
{
    cards.push_back(card);
}

template <typename T>
void Deck<T>::removeCard(T* card) {
    auto it = std::find(cards.begin(), cards.end(), card);
    if (it != cards.end()) {
        cards.erase(it);
    } else {
        throw std::runtime_error("Card not found in the deck");
    }
}

template <typename T>
T* Deck<T>::pickCard() const
{
    return cards[0];
}

template <typename T>
std::vector<T*> Deck<T>::getCards() const
{
    return cards;
}

template <typename T>
void Deck<T>::shuffle(std::mt19937& gen)
{
    std::shuffle(cards.begin(), cards.end(), gen);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Deck<T>& deck)
{
    for (T* card : deck.getCards())
    {
        os << *card << std::endl;
    }
    return os;
}

#endif // CARDS_H
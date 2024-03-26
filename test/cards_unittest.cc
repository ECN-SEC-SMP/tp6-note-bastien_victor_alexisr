/**
 * @file cards_unittest.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Unit tests for the cards and deck classes
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>
#include "../sources/cards.h"

std::random_device rd;
std::mt19937 gen(rd());

TEST(CommunityChestCard, Constructor)
{
    CommunityChestCard card("Avancez jusqu'à la case départ");
    EXPECT_EQ(card.getDescription(), "Avancez jusqu'à la case départ");
}

TEST(ChanceCard, Constructor)
{
    ChanceCard card("La banque vous verse un dividende de 50€");
    EXPECT_EQ(card.getDescription(), "La banque vous verse un dividende de 50€");
}

TEST(Deck, Constructor)
{
    Deck<CommunityChestCard> deck;
    EXPECT_EQ(deck.getCards().size(), 0);
    Deck<ChanceCard> deck2;
    EXPECT_EQ(deck2.getCards().size(), 0);
}

TEST(Deck, AddCard)
{
    Deck<CommunityChestCard> deck;
    CommunityChestCard card1("Avancez jusqu'à la case départ");
    CommunityChestCard card2("Vous êtes libéré de prison (cette carte peut être conservée jusqu'à ce qu'elle soit utilisée, ou vendue)");
    deck.addCard(&card1);
    deck.addCard(&card2);
    EXPECT_EQ(deck.getCards().size(), 2);

    Deck<ChanceCard> deck2;
    ChanceCard card3("La banque vous verse un dividende de 50€");
    ChanceCard card4("Faites des réparations dans toutes vos maisons. Versez pour chaque maison 25€ et pour chaque hôtel 100€");
    deck2.addCard(&card3);
    deck2.addCard(&card4);
    EXPECT_EQ(deck2.getCards().size(), 2);

}

TEST(Deck, RemoveCard)
{
    Deck<CommunityChestCard> deck;
    CommunityChestCard card1("Avancez jusqu'à la case départ");
    CommunityChestCard card2("Vous êtes libéré de prison (cette carte peut être conservée jusqu'à ce qu'elle soit utilisée, ou vendue)");
    deck.addCard(&card1);
    deck.addCard(&card2);
    deck.removeCard(&card1);
    EXPECT_EQ(deck.getCards().size(), 1);
}

TEST(Deck, PickCard)
{
    Deck<CommunityChestCard> deck;
    CommunityChestCard card1("Avancez jusqu'à la case départ");
    CommunityChestCard card2("Vous êtes libéré de prison (cette carte peut être conservée jusqu'à ce qu'elle soit utilisée, ou vendue)");
    deck.addCard(&card1);
    deck.addCard(&card2);
    Card* pickedCard = deck.pickCard();
    EXPECT_EQ(pickedCard, &card1);
}

TEST(Deck, Shuffle)
{
    Deck<CommunityChestCard> deck;
    CommunityChestCard card1("Vous êtes libéré de prison (cette carte peut être conservée jusqu'à ce qu'elle soit utilisée, ou vendue)");
    CommunityChestCard card2("Avancez jusqu'à la case départ");
    CommunityChestCard card3("Recevez votre revenu annuel de 100€");
    CommunityChestCard card4("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€");
    CommunityChestCard card5("Vous avez gagné le deuxième prix de beauté. Recevez 10€");
    CommunityChestCard card6("Retournez à Belleville");
    CommunityChestCard card7("Payez une amende de 10€ ou tirez une carte Chance");
    CommunityChestCard card8("La vente de votre stock vous rapporte 50€");
    CommunityChestCard card9("Payez la note du médecin 50€");
    CommunityChestCard card10("Payez l'hôpital 100€");
    CommunityChestCard card11("Erreur de la banque en votre faveur. Recevez 200€");
    CommunityChestCard card12("Recevez votre intérêt sur l'emprunt à 7% : 25€");
    CommunityChestCard card13("Les contributions vous remboursent la somme de 20€");
    CommunityChestCard card14("Vous héritez 100€");
    CommunityChestCard card15("Payez votre Police d'Assurance s'élevant à 50€");
    CommunityChestCard card16("C'est votre anniversaire, chaque joueur doit vous donner 10€");

    deck.addCard(&card1);
    deck.addCard(&card2);
    deck.addCard(&card3);
    deck.addCard(&card4);
    deck.addCard(&card5);
    deck.addCard(&card6);
    deck.addCard(&card7);
    deck.addCard(&card8);
    deck.addCard(&card9);
    deck.addCard(&card10);
    deck.addCard(&card11);
    deck.addCard(&card12);
    deck.addCard(&card13);
    deck.addCard(&card14);
    deck.addCard(&card15);
    deck.addCard(&card16);

    CommunityChestCard card1Copy = card1;
    int fail = 0;
    // When the deck is shuffled, there is a chance that the first card is still the same (1 in 16 chance)
    // So we shuffle the deck 10 times to make sure that the first card is not the same as the original one
    // The probability that the first card is still the same after 10 shuffles is 1 in 1,099,511,627,776
    for (int i = 0; i < 10; i++)
    {
        try{
            deck.shuffle(gen);
            EXPECT_NE(deck.getCards().at(0)->getDescription(), card1Copy.getDescription());
            break; 
        } catch (...) {
            ++fail;
        } 
    }

    EXPECT_LT(fail, 10);

    Deck<ChanceCard> deck2;
    ChanceCard card17("Faites des réparations dans toutes vos maisons. Versez pour chaque maison 25€ et pour chaque hôtel 100€");
    ChanceCard card18("Vous avez gagné le prix de mots croisés. Recevez 100€");
    ChanceCard card19("Amande pour ivresse. 20€");
    ChanceCard card20("Rendez-vous à l'Avenue Henri-Martin. Si vous passez par la case départ, recevez 200€");
    ChanceCard card21("La Banque vous verse un dividende de 50€");
    ChanceCard card22("Allez à la gare de Lyon. Si vous passez par la case départ, recevez 200€");
    ChanceCard card23("Avancez au Boulevard de la Villette. Si vous passez par la case départ, recevez 200€");
    ChanceCard card24("Rendez-vous à la Rue de la Paix");
    ChanceCard card25("Vous êtes libéré de prison (cette carte peut être conservée jusqu'à ce qu'elle soit utilisée, ou vendue)");
    ChanceCard card26("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€");
    ChanceCard card27("Amande pour excès de vitesse. 15€");
    ChanceCard card28("Vous êtes imposé pour les réparations de voirie à raison de 40€ par maison et 115€ par hôtel");
    ChanceCard card29("Reculez de trois cases");
    ChanceCard card30("Votre immeuble et votre prêt rapportent. Vous devez toucher 150€");
    ChanceCard card31("Payez pour frais de scolarité 150€");
    ChanceCard card32("Avancez jusqu'à la case départ");

    deck2.addCard(&card17);
    deck2.addCard(&card18);
    deck2.addCard(&card19);
    deck2.addCard(&card20);
    deck2.addCard(&card21);
    deck2.addCard(&card22);
    deck2.addCard(&card23);
    deck2.addCard(&card24);
    deck2.addCard(&card25);
    deck2.addCard(&card26);
    deck2.addCard(&card27);
    deck2.addCard(&card28);
    deck2.addCard(&card29);
    deck2.addCard(&card30);
    deck2.addCard(&card31);
    deck2.addCard(&card32);

    ChanceCard card17Copy = card17;
    fail = 0;
    // When the deck is shuffled, there is a chance that the first card is still the same (1 in 16 chance)
    // So we shuffle the deck 10 times to make sure that the first card is not the same as the original one
    // The probability that the first card is still the same after 10 shuffles is 1 in 1,099,511,627,776
    for (int i = 0; i < 10; i++)
    {
        try{
            deck2.shuffle(gen);
            EXPECT_NE(deck2.getCards().at(0)->getDescription(), card17Copy.getDescription());
            break; 
        } catch (...) {
            ++fail;
        } 
    }

    EXPECT_LT(fail, 10);
}

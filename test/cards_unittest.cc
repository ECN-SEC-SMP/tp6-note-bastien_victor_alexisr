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


TEST(CommunityChestCard, Constructor)
{
    CommunityChestCard card("Avancez jusqu'à la case départ", nullptr);
    EXPECT_EQ(card.getDescription(), "Avancez jusqu'à la case départ");
}

TEST(ChanceCard, Constructor)
{
    ChanceCard card("La banque vous verse un dividende de 50€", nullptr);
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
    CommunityChestCard card1("Avancez jusqu'à la case départ", nullptr);
    CommunityChestCard card2("Vous êtes libéré de prison", nullptr);
    deck.addCard(&card1);
    deck.addCard(&card2);
    EXPECT_EQ(deck.getCards().size(), 2);

    Deck<ChanceCard> deck2;
    ChanceCard card3("La banque vous verse un dividende de 50€", nullptr);
    ChanceCard card4("Faites des réparations dans toutes vos maisons. Versez pour chaque maison 25€ et pour chaque hôtel 100€", nullptr);
    deck2.addCard(&card3);
    deck2.addCard(&card4);
    EXPECT_EQ(deck2.getCards().size(), 2);

}

TEST(Deck, RemoveCard)
{
    Deck<CommunityChestCard> deck;
    CommunityChestCard card1("Avancez jusqu'à la case départ", nullptr);
    CommunityChestCard card2("Vous êtes libéré de prison", nullptr);
    deck.addCard(&card1);
    deck.addCard(&card2);
    deck.removeCard(&card1);
    EXPECT_EQ(deck.getCards().size(), 1);
}

TEST(Deck, PickCard)
{
    Deck<CommunityChestCard> deck;
    CommunityChestCard card1("Avancez jusqu'à la case départ", nullptr);
    CommunityChestCard card2("Vous êtes libéré de prison", nullptr);
    deck.addCard(&card1);
    deck.addCard(&card2);
    Card* pickedCard = deck.pickCard();
    EXPECT_EQ(pickedCard, &card1);
}

TEST(Deck, Shuffle)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    Deck<CommunityChestCard> deck;

    CommunityChestCard card1("Vous êtes libéré de prison, cette carte peut être conservée en cas de besoin", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        currentPlayer->setHasGetOutOfJailCard(true);
    });

    CommunityChestCard card2("Avancez jusqu'à la case départ", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 0 - currentPlayer->getPosition()); // +0 because the case start is at index 0
    });

    CommunityChestCard card3("Recevez votre revenu annuel de 100€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 100);
    });

    CommunityChestCard card4("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        currentPlayer->setRemainingTurnsInJail(3);
        currentPlayer->setPosition(10);
        board->handleSpace();
    });

    CommunityChestCard card5("Vous avez gagné le deuxième prix de beauté. Recevez 10€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 10);
    });

    CommunityChestCard card6("Retournez à Belleville", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 1 - currentPlayer->getPosition()); // +1 because Belleville is at index 1
    });

    CommunityChestCard card7("Payez une amende de 10€ ou tirez une carte Chance", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        std::cout << "Do you want to draw a Chance card? (y/n)" << std::endl;
        std::string choice;
        std::cin >> choice;
        if (choice == "y")
        {
            // TODO: handle drawChanceCard
            // board->getPlayerManager().drawChanceCard();
        }
        else if (choice == "n")
        {
            board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 10);
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
        }
    });

    CommunityChestCard card8("La vente de votre stock vous rapporte 50€",
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 50);
    });

    CommunityChestCard card9("Payez la note du médecin 50€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 50);
    });

    CommunityChestCard card10("Payez l'hôpital 100€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 100);
    });

    CommunityChestCard card11("Erreur de la banque en votre faveur. Recevez 200€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 200);
    });

    CommunityChestCard card12("Recevez votre intérêt sur l'emprunt à 7% : 25€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 25);
    });

    CommunityChestCard card13("Les contributions vous remboursent la somme de 20€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 20);
    });

    CommunityChestCard card14("Vous héritez 100€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 100);
    });

    CommunityChestCard card15("Payez votre Police d'Assurance s'élevant à 50€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 50);
    });

    CommunityChestCard card16("C'est votre anniversaire, chaque joueur doit vous donner 10€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        for (int i = 0; i < board->getPlayerManager().getNbPlayers(); ++i)
        {
            Player* player = board->getPlayerManager().getPlayer(i);
            if (player != currentPlayer)
            {
                board->getPlayerManager().transferMoneyFromTo(player, currentPlayer, 10);
            }
        }
    });

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
    // When the deck is shuffled, there is a chance that the first card is still the same (1 in 16 chance)
    // So we shuffle the deck 10 times to make sure that the first card is not the same as the original one
    // The probability that the first card is still the same after 10 shuffles is 1 in 1,099,511,627,776
    int i = 0;
    while (deck.getCards().at(0)->getDescription() == card1Copy.getDescription() && i < 10) {
        deck.shuffle(gen);
        ++i;
    }
    EXPECT_NE(deck.getCards().at(0)->getDescription(), card1Copy.getDescription());

    Deck<ChanceCard> deck2;
    ChanceCard card17("Faites des réparations dans toutes vos maisons. Versez pour chaque maison 25€ et pour chaque hôtel 100€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        int nbHouses = 0;
        int nbHotels = 0;
        for (Space* space : board->getBoard())
        {
            if (dynamic_cast<Property*>(space))
            {
                Property* property = dynamic_cast<Property*>(space);
                if (property->getOwner() == currentPlayer)
                {
                    if ((PropertyRent::FULL_STREET > property->getNbBuildings()) && (property->getNbBuildings() < PropertyRent::HOTEL))
                    {
                        nbHouses += static_cast<int>(property->getNbBuildings()) - 1; // -1 because FULL_STREET is 1
                    }
                    else if (property->getNbBuildings() == PropertyRent::HOTEL)
                    {
                        nbHotels += 1;
                    }
                }
            }
        }
        std::cout << "You own " << nbHouses << " houses and " << nbHotels << " hotels." << std::endl;
        std::cout << "You have to pay " << nbHouses * 25 + nbHotels * 100 << "€." << std::endl;
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, nbHouses * 25 + nbHotels * 100);
    });

    ChanceCard card18("Vous avez gagné le prix de mots croisés. Recevez 100€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 100);
    });

    ChanceCard card19("Amande pour ivresse. 20€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 20);
    });

    ChanceCard card20("Rendez-vous à l'Avenue Henri-Martin. Si vous passez par la case départ, recevez 200€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 24 - currentPlayer->getPosition()); // +24 because Avenue Henri-Martin is at index 24
    });

    ChanceCard card21("La Banque vous verse un dividende de 50€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 50);
    });

    ChanceCard card22("Allez à la gare de Lyon. Si vous passez par la case départ, recevez 200€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 15 - currentPlayer->getPosition()); // +15 because Gare de Lyon is at index 15
    });

    ChanceCard card23("Avancez au Boulevard de la Villette. Si vous passez par la case départ, recevez 200€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 11 - currentPlayer->getPosition()); // +11 because Boulevard de la Villette is at index 11
    });

    ChanceCard card24("Rendez-vous à la Rue de la Paix", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 39 - currentPlayer->getPosition()); // +39 because Rue de la Paix is at index 39
    });

    ChanceCard card25("Vous êtes libéré de prison, cette carte peut être conservée en cas de besoin", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        currentPlayer->setHasGetOutOfJailCard(true);
    });

    ChanceCard card26("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        currentPlayer->setRemainingTurnsInJail(3);
        currentPlayer->setPosition(10); // setPosition instead of movePlayer because we don't want to pass by the Go space
        board->handleSpace();
    });

    ChanceCard card27("Amande pour excès de vitesse. 15€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 15);
    });

    ChanceCard card28("Vous êtes imposé pour les réparations de voirie à raison de 40€ par maison et 115€ par hôtel", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        int nbHouses = 0;
        int nbHotels = 0;
        for (Space* space : board->getBoard())
        {
            if (dynamic_cast<Property*>(space))
            {
                Property* property = dynamic_cast<Property*>(space);
                if (property->getOwner() == currentPlayer)
                {
                    if ((PropertyRent::FULL_STREET > property->getNbBuildings()) && (property->getNbBuildings() < PropertyRent::HOTEL))
                    {
                        nbHouses += static_cast<int>(property->getNbBuildings()) - 1; // -1 because FULL_STREET is 1
                    }
                    else if (property->getNbBuildings() == PropertyRent::HOTEL)
                    {
                        nbHotels += 1;
                    }
                }
            }
        }
        std::cout << "You own " << nbHouses << " houses and " << nbHotels << " hotels." << std::endl;
        std::cout << "You have to pay " << nbHouses * 40 + nbHotels * 115 << "€." << std::endl;
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, nbHouses * 40 + nbHotels * 115);
    });

    ChanceCard card29("Reculez de trois cases", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(-3);
    });

    ChanceCard card30("Votre immeuble et votre prêt rapportent. Vous devez toucher 150€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(nullptr, currentPlayer, 150);
    });

    ChanceCard card31("Payez pour frais de scolarité 150€", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->getPlayerManager().transferMoneyFromTo(currentPlayer, nullptr, 150);
    });
    
    ChanceCard card32("Avancez jusqu'à la case départ", 
    [](BoardManager* board){
        Player* currentPlayer = board->getPlayerManager().getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 0 - currentPlayer->getPosition()); // +0 because the case start is at index 0
    });

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
    // When the deck is shuffled, there is a chance that the first card is still the same (1 in 16 chance)
    // So we shuffle the deck 10 times to make sure that the first card is not the same as the original one
    // The probability that the first card is still the same after 10 shuffles is 1 in 1,099,511,627,776
    i = 0;
    while (deck2.getCards().at(0)->getDescription() == card17Copy.getDescription() && i < 10) {
        deck2.shuffle(gen);
        ++i;
    }
    EXPECT_NE(deck2.getCards().at(0)->getDescription(), card17Copy.getDescription());
}

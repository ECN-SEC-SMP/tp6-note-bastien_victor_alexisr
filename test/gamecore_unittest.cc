/**
 * @file gamecore_unittest.cc
 * @author Bastien, Victor, AlexisR 
 * @brief Unit tests for the gamecore
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>
#include "../sources/gamecore.h"
#include "../utils/input_manager.h"
#include "spdlog/spdlog.h"


TEST(Dice, Roll)
{
    Dice dice;
    int roll = dice.roll();
    EXPECT_GE(roll, 1);
    EXPECT_LE(roll, 6);
}

/**
 * @brief Test the distribution of the sum of two dice rolls
 * It rolls the dice a large number of times and checks if the distribution is close to the expected one
 */
TEST(Dice, RollDistribution)
{
    const int nbRolls = 100000;
    const double tolerance = 0.05;

    std::vector<int> frequencies(11, 0); // 2 to 12 possible outcomes

    Dice dice1;
    Dice dice2;

    for (int i = 0; i < nbRolls; i++)
    {
        frequencies[dice1.roll() + dice2.roll() - 2]++;
    }

    std::vector<double> expectedFrequencies = {1.0/36, 2.0/36, 3.0/36, 4.0/36, 5.0/36, 6.0/36, 
                                               5.0/36, 4.0/36, 3.0/36, 2.0/36, 1.0/36}; 

    for (int i = 0; i < 11; i++){
        double observed = static_cast<double>(frequencies[i]) / nbRolls;
        double expected = expectedFrequencies[i];
        ASSERT_NEAR(observed, expected, tolerance * expected) << "Outcome " << (i + 2) << " differs significantly";
    }

}

TEST(GameCore, StartGame)
{
    std::vector<std::shared_ptr<Space>> spaces;
    spaces.push_back(std::make_shared<Go>());
    spaces.push_back(std::make_shared<Property>("Boulevard de Belleville", Color::PURPLE, 60, 50, std::vector<int>({2, 4, 10, 30, 90, 160, 250})));
    spaces.push_back(std::make_shared<CommunityChest>());
    spaces.push_back(std::make_shared<Property>("Rue Lecourbe", Color::PURPLE, 60, 50, std::vector<int>({4, 8, 20, 60, 180, 320, 450})));
    spaces.push_back(std::make_shared<Tax>("Impôt sur le revenu", 200));
    spaces.push_back(std::make_shared<Station>("Gare Montparnasse"));
    spaces.push_back(std::make_shared<Property>("Avenue de Vaugirard", Color::LIGHT_BLUE, 100, 50, std::vector<int>({6, 12, 30, 90, 270, 400, 550})));
    spaces.push_back(std::make_shared<Chance>());
    spaces.push_back(std::make_shared<Property>("Rue de Courcelles", Color::LIGHT_BLUE, 100, 50, std::vector<int>({6, 12, 30, 90, 270, 400, 550})));
    spaces.push_back(std::make_shared<Property>("Avenue de la République", Color::LIGHT_BLUE, 120, 50, std::vector<int>({8, 16, 40, 100, 300, 450, 600})));
    spaces.push_back(std::make_shared<Jail>());
    spaces.push_back(std::make_shared<Property>("Boulevard de la Villette", Color::PINK, 140, 100, std::vector<int>({10, 20, 50, 150, 450, 625, 750})));
    spaces.push_back(std::make_shared<Utility>("Compagnie de distribution d'électricité"));
    spaces.push_back(std::make_shared<Property>("Avenue de Neuilly", Color::PINK, 140, 100, std::vector<int>({10, 20, 50, 150, 450, 625, 750})));
    spaces.push_back(std::make_shared<Property>("Rue de Paradis", Color::PINK, 160, 100, std::vector<int>({12, 24, 60, 180, 500, 700, 900})));
    spaces.push_back(std::make_shared<Station>("Gare de Lyon"));
    spaces.push_back(std::make_shared<Property>("Avenue Mozart", Color::ORANGE, 180, 100, std::vector<int>({14, 28, 70, 200, 550, 750, 950})));
    spaces.push_back(std::make_shared<CommunityChest>());
    spaces.push_back(std::make_shared<Property>("Boulevard Saint-Michel", Color::ORANGE, 180, 100, std::vector<int>({14, 28, 70, 200, 550, 750, 950})));
    spaces.push_back(std::make_shared<Property>("Place Pigalle", Color::ORANGE, 200, 100, std::vector<int>({16, 32, 80, 220, 600, 800, 1000})));
    spaces.push_back(std::make_shared<FreeParking>());
    spaces.push_back(std::make_shared<Property>("Avenue Matignon", Color::RED, 220, 150, std::vector<int>({18, 36, 90, 250, 700, 875, 1050})));
    spaces.push_back(std::make_shared<Chance>());
    spaces.push_back(std::make_shared<Property>("Boulevard Malesherbes", Color::RED, 220, 150, std::vector<int>({18, 36, 90, 250, 700, 875, 1050})));
    spaces.push_back(std::make_shared<Property>("Avenue Henri-Martin", Color::RED, 240, 150, std::vector<int>({20, 40, 100, 300, 750, 925, 1100})));
    spaces.push_back(std::make_shared<Station>("Gare du Nord"));
    spaces.push_back(std::make_shared<Property>("Faubourg Saint-Honoré", Color::YELLOW, 260, 150, std::vector<int>({22, 44, 110, 330, 800, 975, 1150})));
    spaces.push_back(std::make_shared<Property>("Place de la Bourse", Color::YELLOW, 260,  150, std::vector<int>({22, 44, 110, 330, 800, 975, 1150})));
    spaces.push_back(std::make_shared<Utility>("Compagnie des eaux"));
    spaces.push_back(std::make_shared<Property>("Rue La Fayette", Color::YELLOW, 280, 150, std::vector<int>({24, 48, 120, 360, 850, 1025, 1200})));
    spaces.push_back(std::make_shared<GoToJail>());
    spaces.push_back(std::make_shared<Property>("Avenue de Breteuil", Color::GREEN, 300, 200, std::vector<int>({26, 52, 130, 390, 900, 1100, 1275})));
    spaces.push_back(std::make_shared<Property>("Avenue Foch", Color::GREEN, 300, 200, std::vector<int>({26, 52, 130, 390, 900, 1100, 1275})));
    spaces.push_back(std::make_shared<CommunityChest>());
    spaces.push_back(std::make_shared<Property>("Boulevard des Capucines", Color::GREEN, 320, 200, std::vector<int>({28, 56, 150, 450, 1000, 1200, 1400})));
    spaces.push_back(std::make_shared<Station>("Gare Saint-Lazare"));
    spaces.push_back(std::make_shared<Chance>());  
    spaces.push_back(std::make_shared<Property>("Avenue des Champs-Élysées", Color::BLUE, 350, 200, std::vector<int>({35, 70, 175, 500, 1100, 1300, 1500})));
    spaces.push_back(std::make_shared<Tax>("Taxe de luxe", 100));
    spaces.push_back(std::make_shared<Property>("Rue de la Paix", Color::BLUE, 400, 200, std::vector<int>({50, 100, 200, 600, 1400, 1700, 2000})));

    std::vector<std::unique_ptr<CommunityChestCard>> communityChestCards;
    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Vous êtes libéré de prison, cette carte peut être conservée en cas de besoin", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setHasGetOutOfJailCard(true);
    }));
    

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Avancez jusqu'à la case départ", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 0 - currentPlayer->getPosition()); // +0 because the case start is at index 0
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Recevez votre revenu annuel de 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 100);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setRemainingTurnsInJail(3);
        currentPlayer->setPosition(10);
        board->handleSpace();
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Vous avez gagné le deuxième prix de beauté. Recevez 10€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 10);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Retournez à Belleville", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 1 - currentPlayer->getPosition()); // +1 because Belleville is at index 1
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Payez une amende de 10€ ou tirez une carte Chance", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        char choice = getYesNo("Do you want to draw a Chance card? (y/n)");
        if (choice == 'y')
        {
            board->drawChanceCard();
        }
        else if (choice == 'n')
        {
            board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 10);
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
        }
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("La vente de votre stock vous rapporte 50€",
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 50);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Payez la note du médecin 50€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 50);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Payez l'hôpital 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 100);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Erreur de la banque en votre faveur. Recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 200);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Recevez votre intérêt sur l'emprunt à 7% : 25€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 25);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Les contributions vous remboursent la somme de 20€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 20);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Vous héritez 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 100);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("Payez votre Police d'Assurance s'élevant à 50€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 50);
    }));

    communityChestCards.push_back(std::make_unique<CommunityChestCard> ("C'est votre anniversaire, chaque joueur doit vous donner 10€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        for (int i = 0; i < board->getPlayerManager()->getNbPlayers(); ++i)
        {
            std::shared_ptr<Player> player = board->getPlayerManager()->getPlayer(i);
            if (player != currentPlayer)
            {
                board->getPlayerManager()->transferMoneyFromTo(player, currentPlayer, 10);
            }
        }
    }));

    std::vector<std::unique_ptr<ChanceCard>> chanceCards;
    chanceCards.push_back(std::make_unique<ChanceCard>("Faites des réparations dans toutes vos maisons. Versez pour chaque maison 25€ et pour chaque hôtel 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        int nbHouses = 0;
        int nbHotels = 0;
        for (std::shared_ptr<Space> space : board->getBoard())
        {
            if (dynamic_cast<Property*>(space.get()))
            {
                Property* property = dynamic_cast<Property*>(space.get());
                if (property->getOwner() == currentPlayer)
                {
                    if ((PropertyRent::FULL_STREET > property->getNbBuildings()) & (property->getNbBuildings() < PropertyRent::HOTEL))
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
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, nbHouses * 25 + nbHotels * 100);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Vous avez gagné le prix de mots croisés. Recevez 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 100);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Amande pour ivresse. 20€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 20);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Rendez-vous à l'Avenue Henri-Martin. Si vous passez par la case départ, recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 24 - currentPlayer->getPosition()); // +24 because Avenue Henri-Martin is at index 24
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("La Banque vous verse un dividende de 50€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 50);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Allez à la gare de Lyon. Si vous passez par la case départ, recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 15 - currentPlayer->getPosition()); // +15 because Gare de Lyon is at index 15
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Avancez au Boulevard de la Villette. Si vous passez par la case départ, recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 11 - currentPlayer->getPosition()); // +11 because Boulevard de la Villette is at index 11
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Rendez-vous à la Rue de la Paix", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 39 - currentPlayer->getPosition()); // +39 because Rue de la Paix is at index 39
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Vous êtes libéré de prison, cette carte peut être conservée en cas de besoin", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setHasGetOutOfJailCard(true);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setRemainingTurnsInJail(3);
        currentPlayer->setPosition(10); // setPosition instead of movePlayer because we don't want to pass by the Go space
        board->handleSpace();
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Amande pour excès de vitesse. 15€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 15);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Vous êtes imposé pour les réparations de voirie à raison de 40€ par maison et 115€ par hôtel", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        int nbHouses = 0;
        int nbHotels = 0;
        for (std::shared_ptr<Space> space : board->getBoard())
        {
            if (dynamic_cast<Property*>(space.get()))
            {
                Property* property = dynamic_cast<Property*>(space.get());
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
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, nbHouses * 40 + nbHotels * 115);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Reculez de trois cases", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(-3);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Votre immeuble et votre prêt rapportent. Vous devez toucher 150€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 150);
    }));

    chanceCards.push_back(std::make_unique<ChanceCard>("Payez pour frais de scolarité 150€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 150);
    }));
    
    chanceCards.push_back(std::make_unique<ChanceCard>("Avancez jusqu'à la case départ", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 0 - currentPlayer->getPosition()); // +0 because the case start is at index 0
    }));

    GameCore gameCore(spaces, std::move(communityChestCards), std::move(chanceCards));
    gameCore.startGame();
}
/**
 * @file main.cpp
 * @author Bastien, Victor, AlexisR 
 * @brief Main file for the project
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "sources/gamecore.h"
#include <iostream>
#include "utils/input_manager.h"
// #include "spdlog/spdlog.h"
// #include "spdlog/sinks/basic_file_sink.h" 
// #include "spdlog/sinks/stdout_color_sinks.h"

std::vector<std::shared_ptr<Space>> createBoard()
{
    std::vector<std::shared_ptr<Space>> board;
    board.push_back(std::make_shared<Go>());
    board.push_back(std::make_shared<Property>("Boulevard de Belleville", Color::PURPLE, 60, 50, std::vector<int>({2, 4, 10, 30, 90, 160, 250})));
    board.push_back(std::make_shared<CommunityChest>());
    board.push_back(std::make_shared<Property>("Rue Lecourbe", Color::PURPLE, 60, 50, std::vector<int>({4, 8, 20, 60, 180, 320, 450})));
    board.push_back(std::make_shared<Tax>("Impôt sur le revenu", 200));
    board.push_back(std::make_shared<Station>("Gare Montparnasse"));
    board.push_back(std::make_shared<Property>("Avenue de Vaugirard", Color::LIGHT_BLUE, 100, 50, std::vector<int>({6, 12, 30, 90, 270, 400, 550})));
    board.push_back(std::make_shared<Chance>());
    board.push_back(std::make_shared<Property>("Rue de Courcelles", Color::LIGHT_BLUE, 100, 50, std::vector<int>({6, 12, 30, 90, 270, 400, 550})));
    board.push_back(std::make_shared<Property>("Avenue de la République", Color::LIGHT_BLUE, 120, 50, std::vector<int>({8, 16, 40, 100, 300, 450, 600})));
    board.push_back(std::make_shared<Jail>());
    board.push_back(std::make_shared<Property>("Boulevard de la Villette", Color::PINK, 140, 100, std::vector<int>({10, 20, 50, 150, 450, 625, 750})));
    board.push_back(std::make_shared<Utility>("Compagnie de distribution d'électricité"));
    board.push_back(std::make_shared<Property>("Avenue de Neuilly", Color::PINK, 140, 100, std::vector<int>({10, 20, 50, 150, 450, 625, 750})));
    board.push_back(std::make_shared<Property>("Rue de Paradis", Color::PINK, 160, 100, std::vector<int>({12, 24, 60, 180, 500, 700, 900})));
    board.push_back(std::make_shared<Station>("Gare de Lyon"));
    board.push_back(std::make_shared<Property>("Avenue Mozart", Color::ORANGE, 180, 100, std::vector<int>({14, 28, 70, 200, 550, 750, 950})));
    board.push_back(std::make_shared<CommunityChest>());
    board.push_back(std::make_shared<Property>("Boulevard Saint-Michel", Color::ORANGE, 180, 100, std::vector<int>({14, 28, 70, 200, 550, 750, 950})));
    board.push_back(std::make_shared<Property>("Place Pigalle", Color::ORANGE, 200, 100, std::vector<int>({16, 32, 80, 220, 600, 800, 1000})));
    board.push_back(std::make_shared<FreeParking>());
    board.push_back(std::make_shared<Property>("Avenue Matignon", Color::RED, 220, 150, std::vector<int>({18, 36, 90, 250, 700, 875, 1050})));
    board.push_back(std::make_shared<Chance>());
    board.push_back(std::make_shared<Property>("Boulevard Malesherbes", Color::RED, 220, 150, std::vector<int>({18, 36, 90, 250, 700, 875, 1050})));
    board.push_back(std::make_shared<Property>("Avenue Henri-Martin", Color::RED, 240, 150, std::vector<int>({20, 40, 100, 300, 750, 925, 1100})));
    board.push_back(std::make_shared<Station>("Gare du Nord"));
    board.push_back(std::make_shared<Property>("Faubourg Saint-Honoré", Color::YELLOW, 260, 150, std::vector<int>({22, 44, 110, 330, 800, 975, 1150})));
    board.push_back(std::make_shared<Property>("Place de la Bourse", Color::YELLOW, 260,  150, std::vector<int>({22, 44, 110, 330, 800, 975, 1150})));
    board.push_back(std::make_shared<Utility>("Compagnie des eaux"));
    board.push_back(std::make_shared<Property>("Rue La Fayette", Color::YELLOW, 280, 150, std::vector<int>({24, 48, 120, 360, 850, 1025, 1200})));
    board.push_back(std::make_shared<GoToJail>());
    board.push_back(std::make_shared<Property>("Avenue de Breteuil", Color::GREEN, 300, 200, std::vector<int>({26, 52, 130, 390, 900, 1100, 1275})));
    board.push_back(std::make_shared<Property>("Avenue Foch", Color::GREEN, 300, 200, std::vector<int>({26, 52, 130, 390, 900, 1100, 1275})));
    board.push_back(std::make_shared<CommunityChest>());
    board.push_back(std::make_shared<Property>("Boulevard des Capucines", Color::GREEN, 320, 200, std::vector<int>({28, 56, 150, 450, 1000, 1200, 1400})));
    board.push_back(std::make_shared<Station>("Gare Saint-Lazare"));
    board.push_back(std::make_shared<Chance>());  
    board.push_back(std::make_shared<Property>("Avenue des Champs-Élysées", Color::BLUE, 350, 200, std::vector<int>({35, 70, 175, 500, 1100, 1300, 1500})));
    board.push_back(std::make_shared<Tax>("Taxe de luxe", 100));
    board.push_back(std::make_shared<Property>("Rue de la Paix", Color::BLUE, 400, 200, std::vector<int>({50, 100, 200, 600, 1400, 1700, 2000})));
    return board;
}

std::vector<std::unique_ptr<CommunityChestCard>> createCommunityChestDeck() {
    std::vector<std::unique_ptr<CommunityChestCard>> deck;

    deck.push_back(std::make_unique<CommunityChestCard> ("Vous êtes libéré de prison, cette carte peut être conservée en cas de besoin", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setHasGetOutOfJailCard(true);
    }));
    

    deck.push_back(std::make_unique<CommunityChestCard> ("Avancez jusqu'à la case départ", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 0 - currentPlayer->getPosition()); // +0 because the case start is at index 0
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Recevez votre revenu annuel de 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 100);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setRemainingTurnsInJail(3);
        currentPlayer->setPosition(10);
        board->handleSpace();
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Vous avez gagné le deuxième prix de beauté. Recevez 10€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 10);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Retournez à Belleville", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 1 - currentPlayer->getPosition()); // +1 because Belleville is at index 1
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Payez une amende de 10€ ou tirez une carte Chance", 
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

    deck.push_back(std::make_unique<CommunityChestCard> ("La vente de votre stock vous rapporte 50€",
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 50);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Payez la note du médecin 50€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 50);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Payez l'hôpital 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 100);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Erreur de la banque en votre faveur. Recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 200);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Recevez votre intérêt sur l'emprunt à 7% : 25€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 25);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Les contributions vous remboursent la somme de 20€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 20);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Vous héritez 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 100);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("Payez votre Police d'Assurance s'élevant à 50€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 50);
    }));

    deck.push_back(std::make_unique<CommunityChestCard> ("C'est votre anniversaire, chaque joueur doit vous donner 10€", 
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

    return deck;
}

std::vector<std::unique_ptr<ChanceCard>> createChanceDeck()
{
    std::vector<std::unique_ptr<ChanceCard>> deck;
    deck.push_back(std::make_unique<ChanceCard>("Faites des réparations dans toutes vos maisons. Versez pour chaque maison 25€ et pour chaque hôtel 100€", 
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

    deck.push_back(std::make_unique<ChanceCard>("Vous avez gagné le prix de mots croisés. Recevez 100€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 100);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Amande pour ivresse. 20€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 20);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Rendez-vous à l'Avenue Henri-Martin. Si vous passez par la case départ, recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 24 - currentPlayer->getPosition()); // +24 because Avenue Henri-Martin is at index 24
    }));

    deck.push_back(std::make_unique<ChanceCard>("La Banque vous verse un dividende de 50€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 50);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Allez à la gare de Lyon. Si vous passez par la case départ, recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 15 - currentPlayer->getPosition()); // +15 because Gare de Lyon is at index 15
    }));

    deck.push_back(std::make_unique<ChanceCard>("Avancez au Boulevard de la Villette. Si vous passez par la case départ, recevez 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 11 - currentPlayer->getPosition()); // +11 because Boulevard de la Villette is at index 11
    }));

    deck.push_back(std::make_unique<ChanceCard>("Rendez-vous à la Rue de la Paix", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 39 - currentPlayer->getPosition()); // +39 because Rue de la Paix is at index 39
    }));

    deck.push_back(std::make_unique<ChanceCard>("Vous êtes libéré de prison, cette carte peut être conservée en cas de besoin", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setHasGetOutOfJailCard(true);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Allez en prison. Avancez tout droit en prison. Ne passez pas par la case départ. Ne recevez pas 200€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        currentPlayer->setRemainingTurnsInJail(3);
        currentPlayer->setPosition(10); // setPosition instead of movePlayer because we don't want to pass by the Go space
        board->handleSpace();
    }));

    deck.push_back(std::make_unique<ChanceCard>("Amande pour excès de vitesse. 15€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 15);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Vous êtes imposé pour les réparations de voirie à raison de 40€ par maison et 115€ par hôtel", 
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

    deck.push_back(std::make_unique<ChanceCard>("Reculez de trois cases", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(-3);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Votre immeuble et votre prêt rapportent. Vous devez toucher 150€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(nullptr, currentPlayer, 150);
    }));

    deck.push_back(std::make_unique<ChanceCard>("Payez pour frais de scolarité 150€", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->getPlayerManager()->transferMoneyFromTo(currentPlayer, nullptr, 150);
    }));
    
    deck.push_back(std::make_unique<ChanceCard>("Avancez jusqu'à la case départ", 
    [](std::shared_ptr<BoardManager> board){
        std::shared_ptr<Player> currentPlayer = board->getPlayerManager()->getCurrentPlayer();
        board->movePlayer(board->getBoard().size() + 0 - currentPlayer->getPosition()); // +0 because the case start is at index 0
    }));

    return deck;
}


int main()
{
    // try 
    // {       
    //     auto console_logger = spdlog::stdout_color_mt("console");
    //     spdlog::set_default_logger(console_logger);
    //     spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    //     #ifdef DEBUG
    //         spdlog::set_level(spdlog::level::debug);
    //     #else
    //         spdlog::set_level(spdlog::level::info);
    //     #endif
    // }
    // catch (const spdlog::spdlog_ex& ex)
    // {
    //     std::cout << "Log initialization failed: " << ex.what() << std::endl;
    // }
    std::vector<std::shared_ptr<Space>> board = createBoard();
    std::vector<std::unique_ptr<CommunityChestCard>> communityChestDeck = createCommunityChestDeck();
    std::vector<std::unique_ptr<ChanceCard>> chanceDeck = createChanceDeck();
    GameCore game(board, std::move(communityChestDeck), std::move(chanceDeck));
    game.startGame();
    return 0;
}
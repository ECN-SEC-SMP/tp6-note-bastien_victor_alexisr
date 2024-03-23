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

#include "sources/gamecore.hpp"

std::vector<Space*> createClasssicBoard()
{
    std::vector<Space*> board;
    std::vector<int> propertyRent = {0, 0, 0, 0, 0, 0};
    board.push_back(new Go());
    board.push_back(new Property("Boulevard de Belleville", Color::PURPLE, 60, propertyRent));
    board.push_back(new CommunityChest());
    board.push_back(new Property("Rue Lecourbe", Color::PURPLE, 60, propertyRent));
    board.push_back(new Tax("Impôt sur le revenu", 200));
    board.push_back(new Station("Gare Montparnasse"));
    board.push_back(new Property("Avenue de Vaugirard", Color::LIGHT_BLUE, 100, propertyRent));
    board.push_back(new Chance());
    board.push_back(new Property("Rue de Courcelles", Color::LIGHT_BLUE, 100, propertyRent));
    board.push_back(new Property("Avenue de la République", Color::LIGHT_BLUE, 120, propertyRent));
    board.push_back(new Jail());
    board.push_back(new Property("Boulevard de la Villette", Color::PINK, 140, propertyRent));
    board.push_back(new Utility("Compagnie de distribution d'électricité"));
    board.push_back(new Property("Avenue de Neuilly", Color::PINK, 140, propertyRent));
    board.push_back(new Property("Rue de Paradis", Color::PINK, 160, propertyRent));
    board.push_back(new Station("Gare de Lyon"));
    board.push_back(new Property("Avenue Mozart", Color::ORANGE, 180, propertyRent));
    board.push_back(new CommunityChest());
    board.push_back(new Property("Boulevard Saint-Michel", Color::ORANGE, 180, propertyRent));
    board.push_back(new Property("Place Pigalle", Color::ORANGE, 200, propertyRent));
    board.push_back(new FreeParking());
    board.push_back(new Property("Avenue Matignon", Color::RED, 220, propertyRent));
    board.push_back(new Chance());
    board.push_back(new Property("Boulevard Malesherbes", Color::RED, 220, propertyRent));
    board.push_back(new Property("Avenue Henri-Martin", Color::RED, 240, propertyRent));
    board.push_back(new Station("Gare du Nord"));
    board.push_back(new Property("Faubourg Saint-Honoré", Color::YELLOW, 260, propertyRent));
    board.push_back(new Property("Place de la Bourse", Color::YELLOW, 260, propertyRent));
    board.push_back(new Utility("Compagnie des eaux"));
    board.push_back(new Property("Rue La Fayette", Color::YELLOW, 280, propertyRent));
    board.push_back(new GoToJail());
    board.push_back(new Property("Avenue de Breteuil", Color::GREEN, 300, propertyRent));
    board.push_back(new Property("Avenue Foch", Color::GREEN, 300, propertyRent));
    board.push_back(new CommunityChest());
    board.push_back(new Property("Boulevard des Capucines", Color::GREEN, 320, propertyRent));
    board.push_back(new Station("Gare Saint-Lazare"));
    board.push_back(new Chance());  
    board.push_back(new Property("Avenue des Champs-Élysées", Color::BLUE, 350, propertyRent));
    board.push_back(new Tax("Taxe de luxe", 100));
    board.push_back(new Property("Rue de la Paix", Color::BLUE, 400, propertyRent));
    return board;
}



int main()
{
    std::vector<Space*> board = createClasssicBoard();
    GameCore game(board);
    return 0;
}
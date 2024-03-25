/**
 * @file test_spaces.cpp
 * @author Bastien, Victor, AlexisR 
 * @brief  Test file for the spaces classes
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>
#include "../sources/spaces.h" 

// Test the creation of each type of space
TEST(SpaceTest, Creation) {
    std::vector<int> propertyRent = {0, 0, 0, 0, 0, 0};
    Property property1 = Property("Boulevard de Belleville", Color::PURPLE, 60, propertyRent);
    Station station1 = Station("Gare Montparnasse");
    Utility utility1 = Utility("Compagnie de distribution d'électricité");
    Tax tax1 = Tax("Impôt sur le revenu", 200);
    Jail jail1 = Jail();
    GoToJail goToJail1 = GoToJail();
    FreeParking freeParking1 = FreeParking();
    Go go1 = Go();
    CommunityChest communityChest1 = CommunityChest();
    Chance chance1 = Chance();

    // Check if the objects are created
    EXPECT_NE(&property1, nullptr);
    EXPECT_NE(&station1, nullptr);
    EXPECT_NE(&utility1, nullptr);
    EXPECT_NE(&tax1, nullptr);
    EXPECT_NE(&jail1, nullptr);
    EXPECT_NE(&goToJail1, nullptr);
    EXPECT_NE(&freeParking1, nullptr);
    EXPECT_NE(&go1, nullptr);
    EXPECT_NE(&communityChest1, nullptr);
    EXPECT_NE(&chance1, nullptr);
}

// Test the printing of each type of space
TEST(SpaceTest, Printing) {
    std::vector<int> propertyRent = {0, 0, 0, 0, 0, 0};
    Property property1 = Property("Boulevard de Belleville", Color::PURPLE, 60, propertyRent);
    Station station1 = Station("Gare Montparnasse");
    Utility utility1 = Utility("Compagnie de distribution d'électricité");
    Tax tax1 = Tax("Impôt sur le revenu", 200);
    Jail jail1 = Jail();
    GoToJail goToJail1 = GoToJail();
    FreeParking freeParking1 = FreeParking();
    Go go1 = Go();
    CommunityChest communityChest1 = CommunityChest();
    Chance chance1 = Chance();

    // Check if the objects are created
    EXPECT_EQ(property1.getName(), "Boulevard de Belleville");
    EXPECT_EQ(station1.getName(), "Gare Montparnasse");
    EXPECT_EQ(utility1.getName(), "Compagnie de distribution d'électricité");
    EXPECT_EQ(tax1.getName(), "Impôt sur le revenu");
    EXPECT_EQ(jail1.getName(), "Jail");
    EXPECT_EQ(goToJail1.getName(), "Go To Jail");
    EXPECT_EQ(freeParking1.getName(), "Free Parking");
    EXPECT_EQ(go1.getName(), "Go");
    EXPECT_EQ(communityChest1.getName(), "Community Chest");
    EXPECT_EQ(chance1.getName(), "Chance");

    // Check if the rent vectors are not null
    EXPECT_NE(property1.getRent().size(), 0);
    EXPECT_NE(station1.getRent().size(), 0);

    // Check if the objects are printed correctly
    std::cout << "Spaces created :" << std::endl;
    std::cout << property1 << std::endl;
    std::cout << station1 << std::endl;
    std::cout << utility1 << std::endl;
    std::cout << tax1 << std::endl;
    std::cout << jail1 << std::endl;
    std::cout << goToJail1 << std::endl;
    std::cout << freeParking1 << std::endl;
    std::cout << go1 << std::endl;
    std::cout << communityChest1 << std::endl;
    std::cout << chance1 << std::endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
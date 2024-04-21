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



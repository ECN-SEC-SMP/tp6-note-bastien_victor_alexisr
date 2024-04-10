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


TEST(Dice, Roll)
{
    Dice dice;
    std::random_device rd;
    std::mt19937 gen(rd());
    int roll = dice.roll(gen);
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

    std::random_device rd;
    std::mt19937 gen(rd());

    Dice dice1;
    Dice dice2;

    for (int i = 0; i < nbRolls; i++)
    {
        frequencies[dice1.roll(gen) + dice2.roll(gen) - 2]++;
    }

    std::vector<double> expectedFrequencies = {1.0/36, 2.0/36, 3.0/36, 4.0/36, 5.0/36, 6.0/36, 
                                               5.0/36, 4.0/36, 3.0/36, 2.0/36, 1.0/36}; 

    for (int i = 0; i < 11; i++){
        double observed = static_cast<double>(frequencies[i]) / nbRolls;
        double expected = expectedFrequencies[i];
        ASSERT_NEAR(observed, expected, tolerance * expected) << "Outcome " << (i + 2) << " differs significantly";
    }

}
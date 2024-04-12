#include <gtest/gtest.h>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::GTEST_FLAG(filter) = "Deck.Shuffle";
    ::testing::GTEST_FLAG(break_on_failure) = true;
    //::testing::GTEST_FLAG(repeat) = 100; 
    return RUN_ALL_TESTS();
}
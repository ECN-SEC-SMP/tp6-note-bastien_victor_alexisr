#include "dice.hpp"
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Dice::Dice() {
    // Seed the random number generator
    srand(time(nullptr));
}

// Method to roll the dice
int Dice::roll() {
    // Generate a random number between 1 and 6
    return (rand() % 6) + 1;
}

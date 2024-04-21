/**
 * @file input_manager.h
 * @author Bastien, Victor, AlexisR 
 * @brief File for managing user inputs (getting manual inputs, and simulating inputs)
 * @version 0.1
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H


#include <iostream>
#include <limits>

void getEnter(std::string message);

int getNumber(std::string message, int min, int max);

std::string getString(std::string message);

char getYesNo(std::string message);

#endif // INPUT_MANAGER_H
 
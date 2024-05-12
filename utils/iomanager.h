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
#include <sstream>
#include "spdlog/spdlog.h"

void getEnter(std::string message);

int getNumber(std::string message, int min, int max);

std::string getString(std::string message, const std::vector<std::string>& validStrings = {});

char getYesNo(std::string message);

template <typename T>
void logObject(const T& object, spdlog::level::level_enum level = spdlog::level::info)
{
    std::ostringstream oss;
    oss << object;
    std::istringstream iss(oss.str());
    std::string line;
    while (std::getline(iss, line))
    {
        spdlog::log(level, line);
    }
}

#endif // INPUT_MANAGER_H
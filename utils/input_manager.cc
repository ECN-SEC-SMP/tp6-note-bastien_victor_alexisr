/**
 * @file input_manager.cc
 * @author Bastien, Victor, AlexisR 
 * @brief File for managing user inputs (getting manual inputs, and simulating inputs)
 * @version 0.1
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "input_manager.h"

#ifdef TEST
    void getEnter(std::string message){
        std::cout << message << std::endl;
    }

    int getNumber(std::string message, int min, int max){
        std::uniform_int_distribution<int> distribution(min, max);
        std::default_random_engine generator = std::default_random_engine(std::random_device()());
        return distribution(generator);
    }

    std::string getString(std::string message){
        if (message.find("name") != std::string::npos) {
            static std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry"};
            static int index = 0;
            return names[index++ % names.size()];
        }
        return "test";
    }

    char getYesNo(std::string message){
        std::uniform_int_distribution<int> distribution(0, 1);
        std::default_random_engine generator = std::default_random_engine(std::random_device()());
        int randomNum = distribution(generator);
        return randomNum == 0 ? 'y' : 'n';
    }
#else
    void getEnter(std::string message){
        std::cout << message << std::endl;
        std::cin.get();
    }

    int getNumber(std::string message, int min, int max){
        int number;
        std::string input;
        do
        {
            std::cout << message;
            std::getline(std::cin, input);
            try {
                number = std::stoi(input);
                if (number < min || number > max)
                {
                    std::cout << "Invalid number. Please enter a number between " << min << " and " << max << "." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid input. Please enter a number." << std::endl;
            }
        } while (number < min || number > max);
        return number;
    }

    std::string getString(std::string message) {
        std::string str;
        std::cout << message;
        do {
            std::getline(std::cin, str);
            if (str.empty()) {
                std::cout << "Invalid input. Please enter a non-empty string." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << message;
            }
        } while (str.empty());
        return str;
    }

    char getYesNo(std::string message){
        std::string input;
        char answer;
        do {
            std::cout << message;
            std::getline(std::cin, input);
            if (!input.empty()) {
                answer = input[0];
            }
            if (answer != 'y' && answer != 'n') {
                std::cout << "Invalid input. Please enter y or n.\n";
            }
        } while (answer != 'y' && answer != 'n');
        return answer;
    }
#endif
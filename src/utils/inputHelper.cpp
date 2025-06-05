#include "../../include/utils/inputHelper.h"
#include <iostream>
#include <limits>

int InputHelper::getInt(int main, int max, const std::string& message){
    int value;
    std::cout << message;
    while (!(std::cin>>value) || value < min || value > max) {
        std::cout << "Invalid input. Please enter a value between " << min << " and "<< max<< ":";
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize::max(),'\n');
    }
    return value;
}

double InputHelper::getDouble(int main, int max, const std::string& message){
    double value;
    std::cout << message;
    while (!(std::cin>>value) || value < min || value > max) {
        std::cout << "Invalid input. Please enter a value between " << min << " and "<< max<< ":";
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize::max(),'\n');
    }
    return value;
}

std::string InputHelper::getString (const std::string& message, bool allowEmpty) {
    std::string value;
    while (true) {
        std::cout << message;
        std::getline(std::cin, value);
        if (!allowEmpty && value.empty()) {
            std::cout << "Input cannot be empty." << std::endl;
        } else {
            return value;
        }
    }
}

bool InputHelper::getConfirmation(const std::string& message) {
    std::string answer;
    while (true) {
        std::cout << message << " (y/n): ";
        std::getline(std::cin, answer);
        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;
        std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
    }
}
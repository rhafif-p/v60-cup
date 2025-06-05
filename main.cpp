// File: main.cpp
#include "./include/coffeeApp.h" 
#include <iostream>

int main() {
    CoffeeApp appManager;

    try {
        appManager.start();
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1; // Indicate an error
    } catch (...) {
        std::cerr << "An unknown unexpected error occurred." << std::endl;
        return 1; // Indicate an error
    }
    
    return 0; // Indicate successful execution
}

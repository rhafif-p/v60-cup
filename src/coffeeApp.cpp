#include "../include/coffeeApp.h"
#include <iostream>

CoffeeApp::CoffeeApp() {
    std::cout << "Application Starting..." << std::endl;
    // loadAllData();
}

CoffeeApp::~CoffeeApp() {
    std::cout << "Guided Coffee Brewer App Shutting Down. Saving data..." << std::endl;
    // saveAllData();
}

void CoffeeApp::start() {
    bool running = true;
    while (running) {
        displayMainMenu();
        running = false;  
    }
}

void CoffeeApp::displayMainMenu() {
    std::cout << "Hello Good People" << std::endl;
}

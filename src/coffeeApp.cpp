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
        int choice = getInt(1, 4, "Input your choice");
        switch(choice){
            case 1:
                manageRecipesSubMenu();
                break;
            case 2:
                performGuidedBrewSubMenu();
                break;
            case 3:
                viewBrewHistorySubMenu();
                break;
            casea 4:
                ~coffeeApp();

        }
        running = false;  
    }
}

void CoffeeApp::displayMainMenu() {
    std::cout << "\n---------Guided V60 Brewing App---------"<<std::endl;
    std::cout << "1. Manage your recipes"<<std::endl;
    std::cout << "2. Let's start brewing!"<<std::endl;
    std::cout << "3. View your brewing logs"<<std::endl;
    std::cout << "4. Exit"<<std::endl;
}

void CoffeeApp::manageRecipesSubMenu(){
    bool inSubMenu = true;
    while(inSubMenu){
        std::cout << "\n---------Manage your Recipes---------" <<std::endl;
        std::cout << "1. Create New Recipe"<<std::endl;
        std::cout << "2. View Your Recipe"<<std::endl;
        std::cout << "3. Delete recipe"<<std::endl;
        std::cout << "4. Back"<<std::endl;

        int recipeChoice  = getInt(1,4, "Input your choice");
        switch(recipeChoice){
            case 1:
                createNewRecipe();
                break:
            case 2:
                viewExistingRecipes();
                break:
            case 3:
                deleteRecipe();
                break:
            case 4:
                inSubMenu = false   ;

                break:  
        }

    }
}

void CoffeeApp::createNewRecipe(){
    
}
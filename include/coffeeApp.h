#ifndef COFFEEAPP_H
#define COFFEEAPP_H

#include <string>
#include <vector>
#include "recipe.h"
#include "json.hpp" 


class CoffeeApp{
    private:
    std::vector<Recipe> recipes;
    // std::vector<BrewLog> brewLogs;
    const std::string RECIPE_FILENAME = "recipes_guided.json";
    const std::string LOG_FILENAME = "brewlogs_guided.txt";

    // Menu display methods
    void displayMainMenu();
    void manageRecipesSubMenu();
    void performGuidedBrewSubMenu();
    void viewBrewHistorySubMenu();

    // Recipe management methods
    void createNewRecipe();
    void viewExistingRecipes();
    void deleteRecipe();

    // Guided brewing methods
    void selectAndStartBrew();
    void recordFeedback(const std::string& recipeName, double coffeeG, double waterML, int totalTime);
    
    // Brew history methods
    void listAllBrewLogs();
    void viewSpecificBrewLog();

    // Data loading
    void loadAllData();
    void saveAllData() const; 
    
    public:
    CoffeeApp();
    ~CoffeeApp(); 
    void start(); 
};

#endif
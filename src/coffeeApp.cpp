#include "coffeeApp.h"
#include "utils/inputHelper.h" 
#include "pourStage.h" 
#include "json.hpp"
#include "brewSession.h" 
#include <iostream>
#include <fstream>
#include <limits>    
#include <algorithm> 
#include <ios>

using json = nlohmann::json;

CoffeeApp::CoffeeApp() {
    std::cout << "Application Starting..." << std::endl;
    loadAllData();
}

void CoffeeApp::loadAllData() {
    std::cout << "Loading recipes from " << RECIPE_FILENAME << "..." << std::endl;
    std::ifstream recipeFile(RECIPE_FILENAME);
    if (recipeFile.is_open()) {
        try {
            json recipesJsonArray;
            recipeFile >> recipesJsonArray; 
            if (recipesJsonArray.is_array()) {
                recipes.clear(); 
                recipes = recipesJsonArray.get<std::vector<Recipe>>();
            } else if (recipesJsonArray.is_null()) {

                std::cout << "File Empty" << std::endl;
            } else {
                 std::cerr << "File type is not array" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "An error occured loading data from" << RECIPE_FILENAME << ": " << e.what() << std::endl;
        }
        recipeFile.close();
    } else {
        std::cout << "Recipe file (" << RECIPE_FILENAME << ") not found." << std::endl;
    }
    std::cout << recipes.size() << " recipes loaded." << std::endl;

    std::cout << "Loading brew logs from " << LOG_FILENAME << "..." << std::endl;
    std::ifstream logFile(LOG_FILENAME);
    if (logFile.is_open()) {
        try {
            json logsJsonArray;
            logFile >> logsJsonArray;
             if (logsJsonArray.is_array()) {
                brewLogs.clear(); // Clear existing logs
                brewLogs = logsJsonArray.get<std::vector<BrewLog>>();
            } else if (logsJsonArray.is_null()) {
                std::cout << "Brew log file is empty or contains null. No logs loaded." << std::endl;
            }
            else {
                 std::cerr << "Error: Brew log file does not contain a valid JSON array." << std::endl;
            }
        } catch (const json::parse_error& e) {
            std::cerr << "Error parsing brew log file " << LOG_FILENAME << ": " << e.what() << std::endl;
        } catch (const json::type_error& e) {
            std::cerr << "Type error during brew log deserialization (file: " << LOG_FILENAME << "): " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "An unexpected error occurred loading brew logs from " << LOG_FILENAME << ": " << e.what() << std::endl;
        }
        logFile.close();
    } else {
        std::cout << "Brew log file (" << LOG_FILENAME << ") not found. Starting with no logs." << std::endl;
    }
    std::cout << brewLogs.size() << " brew logs loaded." << std::endl;
}

CoffeeApp::~CoffeeApp() {
    std::cout << "Guided Coffee Brewer App Shutting Down. Saving data..." << std::endl;
    saveAllData();
}

void CoffeeApp::saveAllData() const {
    std::cout << "Saving recipes to " << RECIPE_FILENAME << "..." << std::endl;
    std::ofstream recipeFile(RECIPE_FILENAME);
    if (recipeFile.is_open()) {

        json recipesJson = recipes; 
        recipeFile << recipesJson.dump(4); // .dump(4) for pretty printing with 4 spaces indent
        recipeFile.close();
    } else {
        std::cerr << "Error: Could not open recipe file (" << RECIPE_FILENAME << ") for saving." << std::endl;
    }
    std::cout << recipes.size() << " recipes saved." << std::endl;

    std::cout << "Saving brew logs to " << LOG_FILENAME << "..." << std::endl;
    std::ofstream logFile(LOG_FILENAME);
    if (logFile.is_open()) {
        json logsJson = brewLogs; 
        logFile << logsJson.dump(4); 
        logFile.close();
    } else {
        std::cerr << "Error: Could not open brew log file (" << LOG_FILENAME << ") for saving." << std::endl;
    }
    std::cout << brewLogs.size() << " brew logs saved." << std::endl;
}


void CoffeeApp::start() {
    bool running = true;
    while (running) {
        displayMainMenu();
        int choice = InputHelper::getInt(1, 4, "input your choce : ");
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
            case 4:
                saveAllData(); 
                running = false;
                break;

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

        int recipeChoice  = InputHelper::getInt( 1, 4, "input your choice : ");
        switch(recipeChoice){
            case 1:
                createNewRecipe();
                break;
            case 2:
                viewExistingRecipes();
                break;
            case 3:
                deleteRecipe();
                break;
            case 4:
                inSubMenu = false  ;
                break;  
        }

    }
}

void CoffeeApp::createNewRecipe(){
    std::cout << "\n---create new recipe---"<<std::endl;
    std::string name = InputHelper::getString("Recipe Name : ");
    std::string bean = InputHelper::getString("Bean Name : ");
    std::string grind = InputHelper::getString("grind size : ");
    double coffeAmount = InputHelper::getDouble(1.0, 20.0, "Coffe Amount (grams) : ");
    int waterTemp = InputHelper::getInt(70, 100,"Water Temperature (C) : ");
    std::string notes = InputHelper::getString("General taste note from the recipe : ", true);

    Recipe newRecipe(name, bean, grind, coffeAmount, waterTemp, notes);

    std::cout << "\n ---adding pour stages---" <<std::endl;
    bool addMoreStages = true; 
    int stageNum = 1;
    while (addMoreStages){
        std::cout << "\n pour stage "<<stageNum<<std::endl;
        std::string stageName = InputHelper::getString("Stage name : ");
        double waterMl = InputHelper::getDouble(1.0,500.0,"Total Water amoun on this stage : ");
        int second = InputHelper::getInt(1,500, "Duratin of the stage (second before the next stage) : ");
        std::string instruction = InputHelper::getString("Instruction for this stage (swirling, higher pouring, etc..) : ");

        newRecipe.addPourStage(PourStage(stageName, waterMl, second, instruction));
        stageNum++;
        std::cout<<"Add another stage? (y/n) ";
        char ans;
        std::cin >> ans;
        if (ans == 'n' || ans == 'N')
            break;
    }
    recipes.push_back(newRecipe); 
    std::cout << "Recipe '" << name << "' created successfully with " << newRecipe.getPourStages().size() << " pour stage(s)." << std::endl;

}

void CoffeeApp::viewExistingRecipes() {
    std::cout << "\n---Existing Recipes---" << std::endl;
    if (recipes.empty()) {
        std::cout << "No recipes available." << std::endl;
        return;
    }
    for (size_t i = 0; i < recipes.size(); ++i) { //size_t is used for the type consistency when recipes.size returned
        std::cout << (i + 1) << ". ";
        recipes[i].displayRecipeSummary(); 
    }
    if (InputHelper::getConfirmation("\nView full details of a recipe?")) {
        if (recipes.empty()) { 
             std::cout << "No recipes to view details for." << std::endl;
             return;
        }
        int choice = InputHelper::getInt( 1, recipes.size(), "Enter recipe number to view details: ");
        recipes[choice - 1].displayFullRecipeDetails(); 
    }
}

void CoffeeApp::deleteRecipe() {
    std::cout << "\n--- Delete Recipe ---" << std::endl;
    if (recipes.empty()) {
        std::cout << "No recipes to delete." << std::endl;
        return;
    }
    std::cout << "Select a recipe to delete:" << std::endl;
    for (size_t i = 0; i < recipes.size(); ++i) {
        std::cout << (i + 1) << ". " << recipes[i].recipeName << std::endl; 
    }
    int choice = InputHelper::getInt( 1, recipes.size(), "Enter recipe number to delete: ");
    if (InputHelper::getConfirmation("Are you sure you want to delete '" + recipes[choice - 1].recipeName + "'? This cannot be undone.")) {
        std::cout << "Recipe '" << recipes[choice - 1].recipeName << "' deleted." << std::endl;
        recipes.erase(recipes.begin() + (choice - 1)); 
    } else {
        std::cout << "Deletion cancelled." << std::endl;
    }
}

void CoffeeApp::performGuidedBrewSubMenu() {
    std::cout << "\n--- Perform Guided Brew ---" << std::endl;
    if (recipes.empty()) {
        std::cout << "No recipes available to start a brew. Please create a recipe first." << std::endl;
        return;
    }
    std::cout << "Select a recipe to brew:" << std::endl;
    for (size_t i = 0; i < recipes.size(); ++i) {
        std::cout << (i + 1) << ". ";
        recipes[i].displayRecipeSummary(); 
    }
    int recipeChoice = InputHelper::getInt( 1, recipes.size(), "Enter recipe number: ");
    const Recipe& selectedRecipe = recipes[recipeChoice - 1]; 
    
    std::cout << "\nPreparing to brew with: ";
    selectedRecipe.displayRecipeSummary();
    selectedRecipe.displayFullRecipeDetails(); 
    
    if (!InputHelper::getConfirmation("Start brewing with this recipe?")) {
        std::cout << "Brewing cancelled." << std::endl;
        return;
    }

    BrewSession session(selectedRecipe); 
    int totalBrewTimeSecondsFromStages = 0;

    while(session.startNextStage()) { 
        session.displayCurrentStageInstructions(); 
        std::cout << "Press Enter to start this stage, or type 'c' then Enter to cancel brew: ";
        std::string userInput;
        std::getline(std::cin, userInput);
        if (userInput == "c" || userInput == "C") {
            std::cout << "Brewing cancelled mid-session." << std::endl;
            return;
        }
        
        session.runStageTimer(); 
        totalBrewTimeSecondsFromStages += session.getCurrentPourStage().duration; 
    }

    std::cout << "\nBrewing complete!" << std::endl;
    std::cout << "Total estimated brew time from recipe stages: " << totalBrewTimeSecondsFromStages << " seconds." << std::endl;
    
    recordFeedback(selectedRecipe.recipeName, selectedRecipe.coffeAmount, selectedRecipe.totalWaterAmount, totalBrewTimeSecondsFromStages);
}

void CoffeeApp::recordFeedback(const std::string& recipeName, double coffeeG, double waterML, int totalTimeSeconds) {
    std::cout << "\n--- Record Post-Brew Feedback ---" << std::endl;
    std::string dateTime = InputHelper::getString("Enter Brew Date/Time : ", true); 
    std::string notes = InputHelper::getString("Tasting Notes (optional): ", true);
    std::string acidity = InputHelper::getString("Acidity Rating : ", true);
    std::string body = InputHelper::getString("Body Rating : ", true);
    std::string overall = InputHelper::getString("Overall Rating : ", true);

    brewLogs.emplace_back(dateTime.empty() ? "N/A" : dateTime, 
                          recipeName, coffeeG, waterML, totalTimeSeconds,
                          notes.empty() ? "N/A" : notes, 
                          acidity.empty() ? "N/A" : acidity, 
                          body.empty() ? "N/A" : body, 
                          overall.empty() ? "N/A" : overall);
    std::cout << "Brew log and feedback recorded." << std::endl;
}

void CoffeeApp::viewBrewHistorySubMenu() {
     bool inSubMenu = true;
    while(inSubMenu) {
        std::cout << "\n--- View Brew History ---" << std::endl;
        std::cout << "1. List All Brew Logs" << std::endl;
        std::cout << "2. View Specific Brew Log Detail" << std::endl;
        std::cout << "3. Back to Main Menu" << std::endl;

        int choice = InputHelper::getInt( 1, 3, "History Menu Choice: ");
        switch (choice) {
            case 1: 
                listAllBrewLogs(); 
                break;
            case 2: 
                viewSpecificBrewLog(); 
                break;
            case 3:
                inSubMenu = false;
                break; 
            default: std::cout << "Invalid choice." << std::endl;
        }
         if(inSubMenu) {
            std::cout << "\nPress Enter to return to history menu...";
            std::cin.get();
        }
    }
}

void CoffeeApp::listAllBrewLogs() {
    std::cout << "\n--- All Brew Logs ---" << std::endl;
    if (brewLogs.empty()) {
        std::cout << "No brew logs available." << std::endl;
        return;
    }
    for (size_t i = 0; i < brewLogs.size(); ++i) {
        std::cout << (i + 1) << ". Date: " << brewLogs[i].logDateTime 
                  << ", Recipe: " << brewLogs[i].recipeUsed << std::endl;
    }
}

void CoffeeApp::viewSpecificBrewLog() {
    std::cout << "\n--- View Detailed Brew Log ---" << std::endl;
    if (brewLogs.empty()) {
        std::cout << "No brew logs to view." << std::endl;
        return;
    }
    listAllBrewLogs(); 
    if (brewLogs.empty()) return; 

    int choice = InputHelper::getInt( 1, brewLogs.size(), "Enter log number to view details: ");
    brewLogs[choice - 1].displayLogDetails(); 
}
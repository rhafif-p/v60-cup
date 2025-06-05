#include "coffeeApp.h"
#include "utils/inputHelper.h" 
#include "pourStage.h" 
#include "json.hpp" 
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
        recipeFile << recipesJson.dump(2); //create space between logs
        recipeFile.close();
    } else {
        std::cerr << "Error: Could not open recipe file (" << RECIPE_FILENAME << ") for saving." << std::endl;
    }
    std::cout << recipes.size() << " recipes saved." << std::endl;
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
                // performGuidedBrewSubMenu();
                break;
            case 3:
                // viewBrewHistorySubMenu();
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

        int recipeChoice  = InputHelper::getInt( 1, 4, "input your choice");
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
                inSubMenu = false   ;

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
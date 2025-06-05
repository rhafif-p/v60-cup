#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "pourStage.h" 
#include "json.hpp" 

class Recipe;
void to_json(nlohmann::json& j, const Recipe& r);
void from_json(const nlohmann::json& j, Recipe& r);

class Recipe{
    public:
    std::string recipeName;
    std::string coffeBeanName;
    std::string grindSize;
    double coffeAmount;
    double totalWaterAmount;
    int waterTemp;
    vector<PourStage> pourStages;
    std::string notes;
    

    Recipe(const std::string& name, const std::string& bean, const std::string& grind, double coffeeG, int waterTemp, const std::string& notes);
    
    void addPourStage(const PourStage& stage);
    void displayRecipeSummary() const;
    void displayFullRecipeDetails() const;
    void recalculateTotalWater(); 

    friend void to_json(nlohmann::json& j, const Recipe& r);
    friend void from_json(const nlohmann::json& j, Recipe& r);
    
    const std::vector<PourStage>& getPourStages() const { return pourStages; }
}

#endif
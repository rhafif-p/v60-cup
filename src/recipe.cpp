#include "../include/recipe.h"
#include <iostream>  
#include <numeric> 

using json = nlohmann::json;


Recipe::Recipe(const std::string& name, const std::string& bean, const std::string& grind, double coffeeG, int waterTemp, const std::string& notes)
    :recipeName(name), coffeBeanName(bean), grindSize(grind), coffeAmount(coffeeG), waterTemp(waterTemp), notes(notes), totalWaterAmount(0.0)
    {}

void Recipe::addPourStage(const PourStage& stage) {
    pourStages.push_back(stage);
    recalculateTotalWater();
}

void Recipe::displayRecipeSummary() const {
    std::cout << recipeName << " (" << coffeBeanName << ") - " << coffeAmount << "g coffee, " << totalWaterAmount << "ml total water." << std::endl;
}

void Recipe::recalculateTotalWater() {
    totalWaterAmount = 0;
    for(const auto& s : pourStages) {
        totalWaterAmount += s.waterAmount;
    }
}



void Recipe::displayFullRecipeDetails() const {
    std::cout << "\n--- Recipe: " << recipeName << " ---" << std::endl;
    std::cout << "Bean: " << coffeBeanName << ", Grind: " << grindSize << std::endl;
    std::cout << "Coffee: " << coffeAmount << "g, Water Temp: " << waterTemp << "C" << std::endl;
    std::cout << "Total Water: " << totalWaterAmount << "ml" << std::endl;
    std::cout << "Pour Stages (" << pourStages.size() << "):" << std::endl;
    if (pourStages.empty()) {
        std::cout << "  No pour stages defined." << std::endl;
    } else {
        for(size_t i = 0; i < pourStages.size(); ++i) {
            std::cout << "  " << (i+1) << ". ";
            pourStages[i].displayStageInfo(); 
        }
    }
    std::cout << "General Notes: " << (notes.empty() ? "  " : notes) << std::endl;
}

//JSON Function

void to_json(json& j, const Recipe& r) {
    j = json{
        {"recipeName", r.recipeName},
        {"coffeeBeanOrigin", r.coffeBeanName},
        {"grindSizeDescription", r.grindSize},
        {"coffeeAmountGrams", r.coffeAmount},
        {"waterTemperatureCelsius", r.waterTemp},
        {"generalNotes", r.notes},
        {"pourStages", r.pourStages} 
    };
}

void from_json(const json& j, Recipe& r) {
    r.recipeName = j.value("recipeName", "Unnamed Recipe");
    r.coffeBeanName = j.value("coffeeBeanOrigin", "Unknown Origin");
    r.grindSize = j.value("grindSizeDescription", "N/A");
    r.coffeAmount = j.value("coffeeAmountGrams", 0.0);
    r.waterTemp = j.value("waterTemperatureCelsius", 90);
    r.notes = j.value("generalNotes", "");
    
    if (j.contains("pourStages") && j.at("pourStages").is_array()) {
        r.pourStages.clear();
        j.at("pourStages").get_to(r.pourStages); 
    }
    r.recalculateTotalWater();
}
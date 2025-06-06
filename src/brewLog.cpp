#include "brewLog.h"
#include <iostream>

using json = nlohmann::json;

BrewLog::BrewLog(const std::string& dateTime, const std::string& recipeName, double coffeeG, double waterML, 
                 int timeS, const std::string& notes, const std::string& acidity, 
                 const std::string& body, const std::string& overall)
    : logDateTime(dateTime), recipeUsed(recipeName), coffeGrams(coffeeG), totalWaterAmount(waterML),
      brewTime(timeS), tastingNotes(notes), acidityRating(acidity), bodyRating(body), finalRating(overall) {}


void BrewLog::displayLogDetails() const {
    std::cout << "\n--- Brew Log ---" << std::endl;
    std::cout << "Date/Time: " << logDateTime << std::endl;
    std::cout << "Recipe Used: " << recipeUsed << std::endl;
    std::cout << "Amount of Coffe used: " << coffeGrams << "g" << std::endl;
    std::cout << "Total Water: " << totalWaterAmount << "ml" << std::endl;
    std::cout << "Total brewing Time: " << brewTime << "s" << std::endl;
    std::cout << "Tasting Notes: " << (tastingNotes.empty() ? "N/A" : tastingNotes) << std::endl;
    std::cout << "Acidity: " << (acidityRating.empty() ? "N/A" : acidityRating) << std::endl;
    std::cout << "Body: " << (bodyRating.empty() ? "N/A" : bodyRating) << std::endl;
    std::cout << "Overall Rating: " << (overallRating.empty() ? "N/A" : overallRating) << std::endl;
    std::cout << "-------------------------" << std::endl;
}

//Json Function

void to_json(json& j, const BrewLog& bl) {
    j = json{
        {"logDateTime", bl.logDateTime},
        {"recipeUsedName", bl.recipeUsed},
        {"actualCoffeeGrams", bl.coffeGrams},
        {"actualWaterML", bl.totalWaterAmount},
        {"actualTotalTimeSeconds", bl.brewTime},
        {"tastingNotes", bl.tastingNotes},
        {"acidityRating", bl.acidityRating},
        {"bodyRating", bl.bodyRating},
        {"overallRating", bl.overallRating}
    };
}

void from_json(const json& j, BrewLog& bl) {
    bl.logDateTime = j.value("logDateTime", "N/A");
    bl.recipeUsed = j.value("recipeUsedName", "N/A");
    bl.coffeGrams = j.value("actualCoffeeGrams", 0.0);
    bl.totalWaterAmount = j.value("actualWaterML", 0.0);
    bl.brewTime = j.value("actualTotalTimeSeconds", 0);
    bl.tastingNotes = j.value("tastingNotes", "");
    bl.acidityRating = j.value("acidityRating", "");
    bl.bodyRating = j.value("bodyRating", "");
    bl.overallRating = j.value("overallRating", "");
}
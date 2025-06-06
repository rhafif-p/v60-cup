#ifndef BREWLOG_H
#define BREWLOG_H

#include <string>
#include "json.hpp" 

class BrewLog;
void to_json(nlohmann::json& j, const BrewLog& bl);
void from_json(const nlohmann::json& j, BrewLog& bl);

class BrewLog{
    public:
    std::string logDateTime;
    std::string recipeUsed;
    double coffeGrams;
    double totalWaterAmount;
    int brewTime;
    std::string tastingNotes;
    std::string acidityRating; 
    std::string bodyRating;    
    std::string finalRating; 

    //constructor
    BrewLog(const std::string& dateTime = "N/A", const std::string& recipeName = "N/A", 
        double coffeeG = 0.0, double waterML = 0.0, int timeS = 0, 
        const std::string& notes = "", const std::string& acidity = "", 
        const std::string& body = "", const std::string& overall = "");

    void displayLogDetails() const;
    
    friend void to_json(nlohmann::json& j, const BrewLog& bl);
    friend void from_json(const nlohmann::json& j, BrewLog& bl);
};

#endif

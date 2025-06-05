#ifndef POURSTAGE_H
#define POURSTAGE_H

#include <string>
#include "json.hpp" 

class PourStage;
void to_json(nlohmann::json& j, const PourStage& p);
void from_json(const nlohmann::json& j, PourStage& p);

class PourStage {
public:
    std::string stageName;
    double waterAmount;
    int duration;
    std::string instruction;


    //Cponstructor
    PourStage(const std::string& name = "", double water = 0.0, int duration = 0, const std::string& instr = "");
    void displayStageInfo() const;

    friend void to_json(nlohmann::json& j, const PourStage& p);
    friend void from_json(const nlohmann::json& j, PourStage& p);
};

#endif
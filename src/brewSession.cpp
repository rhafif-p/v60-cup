#include "brewSession.h"
#include <iostream> 


using json = nlohmann::json;



BrewSession::BrewSession(const Recipe& recipeToBrew) 
    : currentRecipe(recipeToBrew), currentStageIndex(-1) {}

bool BrewSession::startNextStage() {
    currentStageIndex++; 
    return currentStageIndex < currentRecipe.getPourStages().size(); 
}

void BrewSession::displayCurrentStageInstructions() const {
    if (currentStageIndex >= 0 && currentStageIndex < currentRecipe.getPourStages().size()) {
        std::cout << "\n---Current Brew Stage (" << currentStageIndex + 1 << "/" << currentRecipe.getPourStages().size() << ") ---" << std::endl;
        currentRecipe.getPourStages()[currentStageIndex].displayStageInfo();
    } else {
        std::cout << "No current brew stage or brew is complete." << std::endl; 
    }
}

PourStage BrewSession::getCurrentPourStage() const {
    if (currentStageIndex >= 0 && currentStageIndex < currentRecipe.getPourStages().size()) {
        return currentRecipe.getPourStages()[currentStageIndex];
    }
    return PourStage("Error", 0, 0, "Error: No current stage available"); 
}

//yes this function is made using the help of AI
void BrewSession::runStageTimer() {
    if (currentStageIndex >= 0 && currentStageIndex < currentRecipe.getPourStages().size()) {
        const auto& stage = currentRecipe.getPourStages()[currentStageIndex];
        std::string timerMessage = stage.stageName + ": " + stage.instruction;
        brewTimer.countdown(stage.duration, timerMessage);
    }
}

bool BrewSession::isBrewingComplete() const {
    return currentStageIndex >= static_cast<int>(currentRecipe.getPourStages().size() -1);
}
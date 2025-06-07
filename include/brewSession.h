#ifndef BREWSESSION_H
#define BREWSESSION_H

#include "recipe.h"    
#include "utils/timerHelper.h" 
#include <string>      
#include <vector>     

class BrewSession {
private:
    Recipe currentRecipe; 
    int currentStageIndex;
    TimerHelper brewTimer; 

public:
    BrewSession(const Recipe& recipeToBrew); 
    
    bool startNextStage(); 
    void displayCurrentStageInstructions() const; 
    void runStageTimer();
    PourStage getCurrentPourStage() const; 
    bool isBrewingComplete() const;
};

#endif
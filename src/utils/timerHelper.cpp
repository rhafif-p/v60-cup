#include "utils/timerHelper.h"
#include <iostream>
#include <thread>   
#include <chrono>

void TimerHelper::countdown(int seconds, const std::string& message) {
    if (!message.empty()) {
        std::cout << message << std::endl;
    }
    for (int i = seconds; i > 0; --i) {
        std::cout << i << "... " << std::flush; 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (i > 1) { 
             for(int k=0; k < std::to_string(i).length() + 4; ++k) { 
                std::cout << "\b \b";
             }
        } else {
             for(int k=0; k < std::to_string(i).length() + 3; ++k) { 
                std::cout << "\b \b";
             }
        }

    }
    std::cout << "Time's up!" << std::endl;
}
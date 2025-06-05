#include "../../include/utils/timerHelper.h"
#include <iostream>

void TimerHelper::countdown(int seconds, const std::string& message) {
    std::cout << "Timer: " << message << " for " << seconds << " seconds." << std::endl;
    for (int i = seconds; i > 0; --i) {
        std::cout << i << "... " << std::flush;
    }
    std::cout << "Time's up!" << std::endl;
}
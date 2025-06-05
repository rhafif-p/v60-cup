#ifndef TIMERHELPER_H
#define TIMERHELPER_H

#include <string>

class TimerHelper{
    public:
    void countdown(int seconds, const std::string& message);
};

#endif
#ifndef iNPUTHELPER_H
#define INPUTHELPER_H

#include <string>
#include <vector>

class InputHelper {
    public:
    static int getInt(int min, int max, const std::string& message);
    static double getDouble(int min, int max, const std::string& message);
    static float getFloat(int min, int max, const std::string& message);
    static std::string getString(const std::string& message, bool allowEmpty = false);
    static bool getConfirmation(const std::string& message);
    
};

#endif
#ifndef iNPUTHELPER_H
#define INPUTHELPER_H

#include <string>
#include <vector>

class InputHelper {
    public:
    static int getInt(int main, int max, const std::string& message);
    static double getDouble(int main, int max, const std::string& message);
    static float getFloat(int main, int max, const std::string& message);
    static std::string getString(const std::string& message, bool allowEmpty = FALSE);
    static bool getConfirmation(const std::string& message);
};

#endif
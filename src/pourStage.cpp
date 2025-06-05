#include "../include/pourStage.h"
#include <iostream> 

using json = nlohmann::json;


PourStage::PourStage(const std::string& name, double water, int duration, const std::string& instr)
    : stageName(name), waterAmountML(water), durationSeconds(duration), instruction(instr) {}

void PourStage::displayStageInfo() const {
    std::cout << "  Stage: " << stageName  << " (" << durationSeconds << "s) - "  << waterAmountML << "ml water. Instruction: " << instruction << std::endl;
}

void to_json(json& j, const PourStage& p) {
    j = json{
        {"stageName", p.stageName},
        {"waterAmountML", p.waterAmountML},
        {"durationSeconds", p.durationSeconds},
        {"instruction", p.instruction}
    };
}

void from_json(const json& j, PourStage& p) {
    p.stageName = j.value("stageName", "Unknown Stage");
    p.waterAmountML = j.value("waterAmountML", 0.0);
    p.durationSeconds = j.value("durationSeconds", 0);
    p.instruction = j.value("instruction", "");

}
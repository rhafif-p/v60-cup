#include "../include/pourStage.h"
#include <iostream> 

using json = nlohmann::json;


PourStage::PourStage(const std::string& name, double water, int duration, const std::string& instr)
    : stageName(name), waterAmount(water), duration(duration), instruction(instr) {}

void PourStage::displayStageInfo() const {
    std::cout << "  Stage: " << stageName  << " (" << duration << "s) - "  << waterAmount << "ml water. Instruction: " << instruction << std::endl;
}

void to_json(json& j, const PourStage& p) {
    j = json{
        {"stageName", p.stageName},
        {"waterAmountML", p.waterAmount},
        {"durationSeconds", p.duration},
        {"instruction", p.instruction}
    };
}

void from_json(const json& j, PourStage& p) {
    p.stageName = j.value("stageName", "Unknown Stage");
    p.waterAmount = j.value("waterAmountML", 0.0);
    p.duration = j.value("durationSeconds", 0);
    p.instruction = j.value("instruction", "");

}
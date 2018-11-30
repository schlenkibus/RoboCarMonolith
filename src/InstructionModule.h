#pragma once

#include <vector>
#include "RoboPosition.h"
#include "data/MazeGraph.h"

class InstructionModule {
public:
    enum class Instruction : char {
        Forward = 'F', ForwardStop = 'S', Left90 = 'L', Right90 = 'R', Turn180 = 'T', Beep = 'B', End = 'E', NoOp = 99
    };

    InstructionModule(const RoboPosition& pos, const MazeGraph& maze);

    void setInstructions(std::vector<Instruction>&& newInstructions);
    std::vector<int> getListOfPathNodes(const RoboPosition &p, const MazeGraph &graph);
protected:
    Instruction getNextInstruction();
    std::vector<Instruction>::iterator currentInstruction;
    std::vector<Instruction> m_currentPath;
    std::vector<Instruction> &&
    parseNodeListToInstructions(std::vector<int> nodesToDriveTo, const RoboPosition &pos, const MazeGraph &graph);
};
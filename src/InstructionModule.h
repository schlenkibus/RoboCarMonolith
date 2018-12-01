#pragma once

#include <vector>
#include "RoboPosition.h"
#include "data/MazeGraph.h"
#include <memory>

class InstructionModule {
public:
    enum class Instruction : char {
        Forward = 'F', ForwardStop = 'S', Left90 = 'L', Right90 = 'R', Turn180 = 'T', Beep = 'B', End = 'E', NoOp = 'N'
    };
    InstructionModule(RoboPosition &pos, const MazeGraph &maze);

    void initialize(RoboPosition &pos, const MazeGraph &maze);
    Instruction getNextInstruction();
    void setInstructions(std::vector<Instruction> newInstructions);
    std::vector<int> getListOfPathNodes(const RoboPosition &p, const MazeGraph &graph);
    void onHitNode(RoboPosition& r);
    int getCurrentTargetID();

protected:
    std::vector<Instruction>::iterator currentInstruction;
    std::vector<int>::iterator m_currentTarget;
    std::vector<Instruction> m_currentPath;
    std::vector<int> m_targetsForPath;
    std::vector<Instruction>
    parseNodeListToInstructions(std::vector<int> nodesToDriveTo, RoboPosition &pos, const MazeGraph &graph);
};
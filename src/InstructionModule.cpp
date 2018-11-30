#include <utility>

#include "InstructionModule.h"
#include "RoboPosition.h"

InstructionModule::InstructionModule(const RoboPosition& pos, const MazeGraph& maze) {
    setInstructions(parseNodeListToInstructions(getListOfPathNodes(pos, maze), pos, maze));
}


InstructionModule::Instruction InstructionModule::getNextInstruction() {
    auto ret = *currentInstruction;
    std::advance(currentInstruction, 1);
    return ret;
}

std::vector<int>
InstructionModule::getListOfPathNodes(const RoboPosition &p, const MazeGraph &graph) {
    auto node = p.currentNode;
    auto graphText = graph.toString(node);

    //call with graphtext get list of ints <- nodes

    return {};
}

void InstructionModule::setInstructions(std::vector<InstructionModule::Instruction>&& newInstructions) {
    m_currentPath = std::move(newInstructions);
    currentInstruction = m_currentPath.begin();
}

InstructionModule::Instruction getTurnInstructionForNextNode(int diff)
{
    if(std::abs(diff) == 2)
        return InstructionModule::Instruction::Turn180;
    else if(diff > 0)
        return InstructionModule::Instruction::Right90;
    else if(diff < 0)
        return InstructionModule::Instruction::Left90;

    return InstructionModule::Instruction::NoOp;
}
std::vector<InstructionModule::Instruction> &&
InstructionModule::parseNodeListToInstructions(std::vector<int> nodesToDriveTo, const RoboPosition &pos, const MazeGraph &graph) {
    std::vector<Instruction> ret;
    if(nodesToDriveTo.front() == pos.currentNode)
        nodesToDriveTo.erase(nodesToDriveTo.begin(), nodesToDriveTo.begin());

    auto rotation = pos.relativeRotationFromStart.rot;
    auto targetDirection = graph.directionOfNodeFromPos(nodesToDriveTo.front(), pos);
    auto diff = targetDirection - rotation;
    ret.emplace_back(getTurnInstructionForNextNode(diff));

    int lastNode = nodesToDriveTo.front();
    for(auto id: nodesToDriveTo) {
        diff = graph.directionOfNodeFromNode(lastNode, id);
        ret.emplace_back(getTurnInstructionForNextNode(diff));
        ret.emplace_back(Instruction::Forward);
        lastNode = id;
    }

    ret.erase(std::remove(ret.begin(), ret.end(), [](auto instruction) {
        return instruction == Instruction::NoOp;
    }), ret.end());

    return std::move(ret);
}
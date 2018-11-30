#include <utility>

#include <utility>

#include <utility>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <cstring>
#include <zconf.h>
#include <sstream>
#include <arpa/inet.h>
#include "InstructionModule.h"
#include "RoboPosition.h"
#include "net/Client.h"
#include <curl/curl.h>
#include <assert.h>

InstructionModule::InstructionModule(const RoboPosition& pos, const MazeGraph& maze) {
    initialize(pos, maze);
}



InstructionModule::Instruction InstructionModule::getNextInstruction() {
    auto ret = *currentInstruction;
    if(currentInstruction + 1 > m_currentPath.end())
        return InstructionModule::Instruction::End;
    std::advance(currentInstruction, 1);
    return ret;
}

std::vector<int> parseAnswer(const std::string &sv) {
    std::vector<int> strings;
    std::string token;
    std::istringstream tokenStream(sv);
    while(std::getline(tokenStream, token, ','))
    {
        strings.push_back(std::stoi(token));
    }
    return strings;
}

std::vector<int>
InstructionModule::getListOfPathNodes(const RoboPosition &p, const MazeGraph &graph) {
    //call with graphtext get list of ints <- nodes
    auto node = p.currentNode;
    auto graphText = graph.toString(node);
    auto result = Client::performRequest("http://192.168.60.118:4447/request?graph=" + graphText);
    std::cout << "Got Back from Server: " << result << std::endl;
    return parseAnswer(result);
}

void InstructionModule::setInstructions(std::vector<InstructionModule::Instruction> newInstructions) {
    m_currentPath = newInstructions;
    currentInstruction = m_currentPath.begin();
    m_currentTarget = m_targetsForPath.begin();
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
std::vector<InstructionModule::Instruction>
InstructionModule::parseNodeListToInstructions(std::vector<int> nodesToDriveTo, const RoboPosition &pos, const MazeGraph &graph) {
    std::vector<Instruction> ret;
    m_targetsForPath = nodesToDriveTo;

    auto nodesSanitized = std::vector<int>(nodesToDriveTo.begin() + 1, nodesToDriveTo.end());

    auto rotation = pos.relativeRotationFromStart.rot;
    auto targetDirection = graph.directionOfNodeFromPos(nodesSanitized.front(), pos);
    auto diff = targetDirection - rotation;
    ret.emplace_back(getTurnInstructionForNextNode(diff));

    int lastNode = pos.currentNode;
    for(auto id: nodesSanitized) {
        diff = graph.directionOfNodeFromNode(lastNode, id);
        if(diff == 0)
            ret.emplace_back(getTurnInstructionForNextNode(diff));
        ret.emplace_back(Instruction::Forward);
        lastNode = id;
    }

    /*ret.erase(std::remove(ret.begin(), ret.end(), [](Instruction instruction) {
        return instruction == Instruction::NoOp;
    }), ret.end());*/

    return std::move(ret);
}

void InstructionModule::initialize(const RoboPosition &pos, const MazeGraph &maze) {
    auto pathNodes = getListOfPathNodes(pos, maze);
    auto instructions = parseNodeListToInstructions(pathNodes, pos, maze);
    setInstructions(instructions);
}

int InstructionModule::getCurrentTargetID() {
    return *m_currentTarget;
}

void InstructionModule::onHitNode() {
    std::advance(m_currentTarget, 1);
}

#include <iostream>
#include "Uart.h"
#include "data/MazeGraph.h"
#include "MazeGrapherModule.h"
#include "InstructionModule.h"
#include "SignDetectionModule.h"
#include "RoboBaseProxy.h"
#include <thread>
#include <chrono>


int main(int argc, char** argv) {
    /*using namespace std::chrono_literals;
    MazeGrapherModule module("/tmp/maze.txt");
    MazeGraph mazeRepresenation{module.getText()};
    RoboPosition position{mazeRepresenation.startId, RoboPosition::Direction()};
    InstructionModule instructionModule{position, mazeRepresenation};
    SignDetectionModule signModule;*/

    RoboBaseProxy roboBaseProxy;

    bool done = false;
    std::string line;
    while(!done) {
        std::getline(std::cin, line);
        InstructionModule::Instruction i;
        switch(line[0]) {
        case 'F':
          i = InstructionModule::Instruction::Forward;
          break;
        case 'L':
          i = InstructionModule::Instruction::Left90;
          break;
        case 'R':
          i = InstructionModule::Instruction::Right90;
          break;
        case 'T':
          i = InstructionModule::Instruction::Turn180;
          break;;
        case 'I':
          exit(2);
        default:
          i = InstructionModule::Instruction::Beep;
          break;
        }
        roboBaseProxy.sendInstructionAndWaitForReturn(i);

    }

/*
    auto updateRobotRotation = [&](InstructionModule::Instruction i) {
        if(i == InstructionModule::Instruction::Right90)
            position.relativeRotationFromStart.right();
        if(i == InstructionModule::Instruction::Left90)
            position.relativeRotationFromStart.left();
        if(i == InstructionModule::Instruction::Turn180)
            position.relativeRotationFromStart.turn();
    };

    auto removeCurrentEdgeWeAreLookingAt = [&](){
        mazeRepresenation.removeEdge(position.currentNode, instructionModule.getCurrentTargetID());
        instructionModule.initialize(position, mazeRepresenation);
    };

    InstructionModule::Instruction lastInstruction = InstructionModule::Instruction::NoOp;

    auto loopBody = [&]() {
        if(lastInstruction == InstructionModule::Instruction::ForwardStop ||
           lastInstruction == InstructionModule::Instruction::Forward) {
            instructionModule.onHitNode(position);
        }

        auto instruction = instructionModule.getNextInstruction();
        lastInstruction = instruction;

        if(instruction == InstructionModule::Instruction::Forward) {
            auto prediction = signModule.getPrediction();

            if(prediction == SignDetectionModule::Object::Stop) {
                instruction = InstructionModule::Instruction::ForwardStop;
            } else if(prediction == SignDetectionModule::Object::Block) {
                return false;
            }
        }

        if(instruction != InstructionModule::Instruction::NoOp) {
            switch(instruction) {
                case InstructionModule::Instruction::Turn180:
                case InstructionModule::Instruction::Left90:
                case InstructionModule::Instruction::Right90:
                    updateRobotRotation(instruction);
            }
            roboBaseProxy.sendInstructionAndWaitForReturn(instruction);
            std::this_thread::sleep_for(1s);
            std::cout << "Robot doing: " << static_cast<char>(instruction) << std::endl;
        }
        if(instruction == InstructionModule::Instruction::End) {
            done = true;
        }
        return true;
    };


    instructionModule.onHitNode(position);
    do {
        if(!loopBody()) {
            removeCurrentEdgeWeAreLookingAt();
        }
    } while(!done);

    return 0;

/*
    recalcRoute();
    while(true) {
        auto response = blockingWaitForBase();
        auto nextInstruction = getNextInstruction();

        if(nextInstruction == Instruction::Forward) {
            auto objectsDetected = getImagePrediction();
            if(objectsDetected == Obstacle::StopSign) {
                nextInstruction = Instruction::ForwardStop;
            } else if(objectsDetected == Obstacle::RoadBlock) {
                removeNextEdgeFromPath();
                recalcRoute();
            }
        } else if(nextInstruction == Instruction::End) {
            break;
        }

        sendInstructionToBase(nextInstruction);
    }*/
}

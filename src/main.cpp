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
    MazeGrapherModule module("/tmp/maze.txt");
    MazeGraph mazeRepresenation{module.mockGraph()}; //later getText();
    RoboPosition position{mazeRepresenation.startId, RoboPosition::Direction()};
    InstructionModule instructionModule{position, mazeRepresenation};
    SignDetectionModule signModule;
    RoboBaseProxy roboBaseProxy;

    bool done = false;

    auto removeCurrentEdgeWeAreLookingAt = [&](){
        mazeRepresenation.removeEdge(position.currentNode, instructionModule.getCurrentTargetID());
        instructionModule.initialize(position, mazeRepresenation);
    };

    InstructionModule::Instruction lastInstruction = InstructionModule::Instruction::NoOp;

    auto loopBody = [&]() {
        if(lastInstruction == InstructionModule::Instruction::ForwardStop ||
           lastInstruction == InstructionModule::Instruction::Forward) {
            instructionModule.onHitNode();
        }

        auto instruction = instructionModule.getNextInstruction();
        lastInstruction = instruction;
        if(instruction == InstructionModule::Instruction::Forward) {
            auto prediction = signModule.getPrediction();
            std::cout << "Predicting!\n";

            if(prediction == SignDetectionModule::Object::Stop) {
                instruction = InstructionModule::Instruction::ForwardStop;
            } else if(prediction == SignDetectionModule::Object::Block) {
                return false;
            }
        }

        if(instruction != InstructionModule::Instruction::NoOp) {
            //roboBaseProxy.sendInstructionAndWaitForReturn(instruction);
            std::cout << "Robot doing: " << static_cast<char>(instruction) << std::endl;
        }
        if(instruction == InstructionModule::Instruction::End) {
            done = true;
        }
        return true;
    };


    instructionModule.onHitNode();
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

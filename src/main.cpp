#include <iostream>
#include "Uart.h"
#include "data/MazeGraph.h"
#include "MazeGrapherModule.h"
#include "InstructionModule.h"
#include <thread>
#include <chrono>



int main(int argc, char** argv) {
    MazeGrapherModule module("/tmp/maze.png");
    MazeGraph mazeRepresenation{module.createGraphFromImage()};
    RoboPosition position{mazeRepresenation.startId, RoboPosition::Direction()};
    InstructionModule instructionModule{position, mazeRepresenation};

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

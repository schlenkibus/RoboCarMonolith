#include <iostream>
#include "Uart.h"

enum class Instruction : char {
    Forward = 'F', ForwardStop = 'S', Left90 = 'L', Right90 = 'R', Turn180 = 'T', Beep = 'B', End = 'E', NoOp = 99
};

enum class Obstacle : short {
    StopSign = 1, RoadBlock = 2, None = 0
};

Instruction getNextInstruction();
char blockingWaitForBase();
Obstacle getImagePrediction() {return Obstacle::None;};
void removeNextEdgeFromPath() {};
void recalcRoute();
void sendInstructionToBase(Instruction i);

Uart uart("/dev/ttyS0");

int main() {
    for(auto x = 0; x < std::numeric_limits<decltype(2)>::max(); x++) {
        uart.send('F');
    }

    return 0;
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
    }
}

void sendInstructionToBase(Instruction i) {
    uart.send(static_cast<char>(i));
}

char blockingWaitForBase() {
    return uart.receive();
}

Instruction getNextInstruction() {
    return Instruction::NoOp;
}

void recalcRoute() {

}
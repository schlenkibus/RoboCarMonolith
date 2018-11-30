#include <thread>
#include "RoboBaseProxy.h"
#include "InstructionModule.h"

RoboBaseProxy::RoboBaseProxy() : uart("/dev/ttyS0") {

}

void RoboBaseProxy::sendInstructionAndWaitForReturn(InstructionModule::Instruction i) {
    using namespace std::chrono_literals;
    uart.send(static_cast<char>(i));
    char got = 'N';
    while(got == 'N')
    {
        got = uart.receive();
        std::this_thread::sleep_for(0.01s);
    }
    // Success we got at least a byte back! -> Robo Waiting for Instructions
}

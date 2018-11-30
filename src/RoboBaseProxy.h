#pragma once
#include "Uart.h"
#include "InstructionModule.h"

class RoboBaseProxy {
    public:
        RoboBaseProxy();
        void sendInstructionAndWaitForReturn(InstructionModule::Instruction i);
    protected:
        Uart uart;
};
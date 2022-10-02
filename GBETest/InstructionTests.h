#pragma once
#include "../GBE/cpu.h"
#include "../GBE/cart.h"

class InstructionTests : public ::testing::Test {
protected:

    void SetUp() override {
        Cart = new cart("../tetris.gb");
        CPU = new cpu(Cart->getRom(), Cart->getRomSize());
    }

    cart* Cart;
    cpu* CPU;

};



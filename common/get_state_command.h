#pragma once
#include <iostream>
#include "command.h"
#include "led.h"


class GetStateCommand final : public ICommand
{
public:
    GetStateCommand(Led& i_led) : ICommand(i_led)
    {
    }

    std::string doCommand(const std::string& i_argument) override
    {
        auto result = led.getState();
        return result ? "OK on" : "OK off";
    }
};

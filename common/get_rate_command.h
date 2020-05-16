#pragma once
#include <iostream>
#include "command.h"
#include "led.h"


class GetRateCommand final : public ICommand
{
public:
    GetRateCommand(Led& i_led) : ICommand(i_led)
    {
    }

    std::string doCommand(const std::string& i_argument) override
    {
        auto result = led.getFrequency();
        return std::string("OK ") + std::to_string(result);
    }
};

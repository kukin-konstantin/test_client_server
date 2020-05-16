#pragma once
#include <iostream>
#include "command.h"


class GetColorCommand final : public ICommand
{
public:
    GetColorCommand(Led& i_led) : ICommand(i_led)
    {
    }

    std::string doCommand(const std::string& i_argument) override
    {
        auto result = led.getColor();
        if (RGB::RED == result)
        {
            return "OK red";
        }
        else if (RGB::GREEN == result)
        {
            return "OK green";
        }
        else if (RGB::BLUE == result)
        {
            return "OK blue";
        }
        return "FAILED";
    }
};


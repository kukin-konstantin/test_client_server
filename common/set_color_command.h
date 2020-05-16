#pragma once
#include <iostream>
#include <boost/optional.hpp>
#include "command.h"


class SetColorCommand final : public ICommand
{
public:
    SetColorCommand(Led& i_led) : ICommand(i_led)
    {
    }

    std::string doCommand(const std::string& i_argument) override
    {
        const auto color_res = parseColor(i_argument);
        return color_res && *color_res ? "OK" : "FAILED";
    }

private:
    boost::optional<bool> parseColor(const std::string& i_argument)
    {
        if (i_argument == "red")
        {
            return led.setColor(RGB::RED);
        }
        else if (i_argument == "green")
        {
            return led.setColor(RGB::GREEN);
        }
        else if (i_argument == "blue")
        {
            return led.setColor(RGB::BLUE);
        }
        return {};
    }
};

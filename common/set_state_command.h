#pragma once
#include <iostream>
#include <boost/optional.hpp>
#include "command.h"
#include "led.h"


class SetStateCommand final : public ICommand
{
public:
    SetStateCommand(Led& i_led) : ICommand(i_led)
    {
    }

    std::string doCommand(const std::string& i_argument) override
    {
        const auto state_res = parseState(i_argument);
        return state_res && *state_res ? "OK" : "FAILED";
    }

private:
    boost::optional<bool> parseState(const std::string& i_argument)
    {
        if (i_argument == "on")
        {
            return led.setState(true);
        }
        else if (i_argument == "off")
        {
            return led.setState(false);
        }
        return {};
    }
};

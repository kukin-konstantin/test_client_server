#pragma once
#include <iostream>
#include <boost/optional.hpp>
#include "command.h"
#include "led.h"


class SetRateCommand final : public ICommand
{
public:
    SetRateCommand(Led& i_led) : ICommand(i_led)
    {
    }

    std::string doCommand(const std::string& i_argument) override
    {
        const auto rate_res = parseRate(i_argument);
        return rate_res && *rate_res ? "OK" : "FAILED";
    }

private:
    boost::optional<int> parseRate(const std::string& i_argument)
    {
        try
        {
            int rate = std::stoi(i_argument);
            return led.setFrequency(rate);
        }
        catch (...)
        {
            return {};
        }
    }
};

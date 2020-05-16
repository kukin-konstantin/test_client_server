#pragma once

enum class RGB
{
    RED,
    GREEN,
    BLUE
};

class Led
{
public:
    Led():
        state(true),
        color(RGB::RED),
        frequency(0)
    {
    }

    bool setState(bool i_state)
    {
        state = i_state;
        return true;
    }

    bool setColor(RGB i_color)
    {
        color = i_color;
        return true;
    }

    bool setFrequency(int i_frequency)
    {
        if (i_frequency>=0 && i_frequency<=5)
        {
            frequency = i_frequency;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool getState() const
    {
        return state;
    }
    
    RGB getColor() const
    {
        return color;
    }
    
    int getFrequency() const
    {
        return frequency;
    }

private:
    bool state;
    RGB color;
    int frequency;
};


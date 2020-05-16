#include <iostream>
#include "server.h"
#include "common/led.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: port\n";
            return 1;
        }

        Led led;
        Server s(std::atoi(argv[1]), led);
        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}
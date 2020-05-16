
#include <iostream>
#include "common/command.h"
#include "client.h"
#include <boost/asio.hpp>


int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: host port\n";
            return 1;
        }

        std::string host = argv[1];
        std::string port = argv[2];

        Client client(std::move(host), std::move(port));
        bool ok = client.connect();

        if (ok)
        {
            std::cout << client.doCommand("get-led-color\n");;
            std::cout << client.doCommand("set-led-color blue\n");
            std::cout << client.doCommand("get-led-color\n");
            std::cout << client.doCommand("set-led-color green\n");
            std::cout << client.doCommand("get-led-color\n");

            std::cout << client.doCommand("set-led-color black\n");
             
            std::cout << client.doCommand("get-led-state\n");
            std::cout << client.doCommand("set-led-state off\n");
            std::cout << client.doCommand("get-led-state\n");
            std::cout << client.doCommand("set-led-state on\n");
            std::cout << client.doCommand("get-led-state\n");

            std::cout << client.doCommand("set-led-state o\n");

            std::cout << client.doCommand("get-led-rate\n");
            std::cout << client.doCommand("set-led-rate 2\n");
            std::cout << client.doCommand("get-led-rate\n");
            std::cout << client.doCommand("set-led-rate 1\n");
            std::cout << client.doCommand("get-led-rate\n");

            std::cout << client.doCommand("set-led-rate -1\n");
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

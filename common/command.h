#pragma once
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include "led.h"

class ICommand
{
public:
    ICommand(Led& i_led):
        led(i_led)
    {}

    virtual std::string doCommand(const std::string& i_argument) = 0;
    virtual ~ICommand() = default;

protected:
    Led& led;
};

using CommandMaker = std::function<std::unique_ptr<ICommand>(Led& i_led)>;

class CommandsFactory
{
public:
    static CommandsFactory& get()
    {
        return instance;
    }

    std::unique_ptr<ICommand> makeCommand(const std::string& i_name, Led& i_led)
    {
        return makers.at(i_name)(i_led);
    }

    bool checkCommand(const std::string& i_name)
    {
        return makers.find(i_name) != makers.end();
    }

    CommandsFactory(const CommandsFactory&) = delete;
    CommandsFactory(CommandsFactory&&) = delete;
    CommandsFactory& operator=(const CommandsFactory&) = delete;
    CommandsFactory& operator=(CommandsFactory&&) = delete;

private:
    friend class CommandMakerRegistar;

    CommandsFactory() = default;

    std::unordered_map<std::string, CommandMaker> makers;
    static CommandsFactory instance;
};

class CommandMakerRegistar
{
public:
    CommandMakerRegistar(const std::string& i_name, CommandMaker i_maker)
    {
        CommandsFactory::get().makers.emplace(i_name, std::move(i_maker));
    }
};

std::string parse(const std::string& i_name_command, Led& i_led);

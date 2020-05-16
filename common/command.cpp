#include <algorithm>
#include "common/command.h"
#include "common/set_color_command.h"
#include "common/get_color_command.h"
#include "common/set_state_command.h"
#include "common/get_state_command.h"
#include "common/set_rate_command.h"
#include "common/get_rate_command.h"


CommandsFactory CommandsFactory::instance;

CommandMakerRegistar s_registrar1("set-led-color", [](Led& i_l) {return std::make_unique<SetColorCommand>(i_l); });
CommandMakerRegistar s_registrar2("get-led-color", [](Led& i_l) {return std::make_unique<GetColorCommand>(i_l); });

CommandMakerRegistar s_registrar3("set-led-state", [](Led& i_l) {return std::make_unique<SetStateCommand>(i_l); });
CommandMakerRegistar s_registrar4("get-led-state", [](Led& i_l) {return std::make_unique<GetStateCommand>(i_l); });

CommandMakerRegistar s_registrar5("set-led-rate", [](Led& i_l) {return std::make_unique<SetRateCommand>(i_l); });
CommandMakerRegistar s_registrar6("get-led-rate", [](Led& i_l) {return std::make_unique<GetRateCommand>(i_l); });

std::string parse(const std::string& i_name_command, Led& i_led)
{
    auto pos_end = i_name_command.find('\n');
    auto pos_blank = i_name_command.find(' ');

    auto name_command = (pos_blank != std::string::npos) ?
        std::string(i_name_command.begin(), i_name_command.begin() + pos_blank) :
        std::string(i_name_command.begin(), i_name_command.begin() + pos_end);

    if (CommandsFactory::get().checkCommand(name_command))
    {
        std::string arguments = std::string(i_name_command.begin() + name_command.size(), i_name_command.begin() + pos_end);
        arguments.erase(std::remove_if(arguments.begin(), arguments.end(),
            [](char x) { return x == ' ' || x == '\n' || x == '\t'; }), arguments.end());
        return CommandsFactory::get().makeCommand(name_command, i_led)->doCommand(arguments)+"\n";
    }
    else
    {
        return "FAILED (parse name command)\n";
    }
}
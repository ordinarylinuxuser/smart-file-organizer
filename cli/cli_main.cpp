//
// Created by ken on 7/10/25.
//

#include "cli_main.h"
#include "../lib/common_lib.h"

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    std::cout << "CLI Utility Running!\n";
    const std::string rule_dir_path = "$HOME/Documents/gits/smart-file-organizer/samples/rules";

    auto rules = loadSmartRules(rule_dir_path);


    return 0;
}

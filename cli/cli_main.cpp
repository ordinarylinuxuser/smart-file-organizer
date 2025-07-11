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
    std::string dir_path = "/home/ken";
    std::string rule_file_path = "/data/Docs/gits/smart-file-organizer/samples/rules.json";

    auto rules = loadSmartRulesFromFile(rule_file_path);


    // for (const auto &entry: getDirectoryEntries(dir_path, false)) {
    //     std::cout << "File: " << entry.path() << "\n";
    // }

    return 0;
}

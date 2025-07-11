//
// Created by ken on 7/10/25.
//

#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "smart_rule.h"
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> getDirectoryEntries(const std::string& dir_path, const bool recursive = false);

std::vector<SmartRule> loadSmartRulesFromFile(const std::string& file_path);

#endif //COMMON_LIB_H


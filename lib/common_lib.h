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

std::string expand_env_vars(const std::string& input);

bool isFileExtensionMatched(const std::string& file_path, const std::vector<std::string>& extensions);

std::vector<fs::directory_entry> getDirectoryEntries(const std::string& dir_path, const bool recursive = false,
                                                     const std::vector<std::string>& filterExtensions = {});

std::vector<SmartRule> loadSmartRules(const std::string& rules_dir_path);


#endif //COMMON_LIB_H


//
// Created by ken on 7/10/25.

#include "common_lib.h"


/**
 * Gets all regular file entries in a directory.
 * @param dir_path directory path to search
 * @param recursive if true, will search recursively in subdirectories
 * @return returns directory entries that are regular files
 */
std::vector<fs::directory_entry> getDirectoryEntries(const std::string& dir_path, const bool recursive)
{
    std::vector<fs::directory_entry> entries;
    try
    {
        if (!fs::exists(dir_path))
        {
            spdlog::error("Directory does not exists : {}", dir_path);
            return {};
        }
        for (auto iterator = fs::recursive_directory_iterator(dir_path, fs::directory_options::skip_permission_denied);
             const auto& entry : iterator)
        {
            if (!recursive && iterator.depth() > 0)
            {
                continue; // Skip subdirectories if not recursive
            }
            if (entry.is_regular_file())
            {
                entries.push_back(entry);
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        spdlog::error("Filesystem error: {}", e.what());
    }
    return entries;
}

std::vector<SmartRule> loadSmartRulesFromFile(const std::string& file_path)
{
    //read json file
    std::ifstream file(file_path);

    if (!file.is_open())
    {
        spdlog::error("Error: Could not open file: {}", file_path);
        return {};
    }

    nlohmann::json json_data = nlohmann::json::parse(file);

    std::vector<SmartRule> rules;
    for (nlohmann::json& rule_json : json_data)
    {
        auto rule = SmartRule();
        rule.load_json(rule_json);
        rules.push_back(rule);
    }
    return rules;
}

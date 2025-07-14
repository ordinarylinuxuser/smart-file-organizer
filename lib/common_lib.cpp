//
// Created by ken on 7/10/25.

#include "common_lib.h"

/// Expands environment variables in a string.
/// @param input The input string that may contain environment variables in the form of $VAR or ${VAR}.
/// @return  A new string with environment variables expanded to their values.
std::string expand_env_vars(const std::string& input)
{
    std::string result;
    for (size_t i = 0; i < input.size();)
    {
        if (input[i] == '$')
        {
            // Handle ${VAR} syntax
            if (i + 1 < input.size() && input[i + 1] == '{')
            {
                size_t end = input.find('}', i + 2);
                if (end != std::string::npos)
                {
                    std::string var_name = input.substr(i + 2, end - i - 2);
                    if (!var_name.empty())
                    {
                        if (const char* value = std::getenv(var_name.c_str()))
                        {
                            result += value;
                        }
                    }
                    i = end + 1;
                    continue;
                }
            }
            // Handle $VAR syntax
            else if (i + 1 < input.size())
            {
                size_t j = i + 1;
                // Check if valid variable name start (letter or underscore)
                if (std::isalpha(input[j]) || input[j] == '_')
                {
                    while (j < input.size() && (std::isalnum(input[j]) || input[j] == '_'))
                    {
                        j++;
                    }
                    std::string var_name = input.substr(i + 1, j - i - 1);
                    if (const char* value = std::getenv(var_name.c_str()))
                    {
                        result += value;
                    }
                    i = j;
                    continue;
                }
            }
        }
        // Add non-variable characters
        result += input[i];
        i++;
    }
    return result;
}

bool isFileExtensionMatched(const std::string& file_path, const std::vector<std::string>& extensions)
{
    if (extensions.empty()) return true;

    std::string extension = fs::path(file_path).extension().string();

    if (!extension.empty() && extension[0] == '.')
    {
        extension = extension.substr(1); // Remove leading dot
    }

    const auto iterator = std::ranges::find(extensions, extension);

    return iterator != extensions.end();
}

/**
 * Gets all regular file entries in a directory.
 * @param dir_path directory path to search
 * @param recursive if true, will search recursively in subdirectories
 * @param filterExtensions extensions to filter files by (if empty, all files are returned)
 * @return returns directory entries that are regular files
 */
std::vector<fs::directory_entry> getDirectoryEntries(const std::string& dir_path,
                                                     const bool recursive,
                                                     const std::vector<std::string>& filterExtensions)
{
    std::vector<fs::directory_entry> entries;
    try
    {
        //expand the environment variables in the directory path
        std::string expanded_path = expand_env_vars(dir_path);

        if (!fs::exists(expanded_path))
        {
            spdlog::error("Directory does not exists : {}", expanded_path);
            return {};
        }
        for (auto iterator = fs::recursive_directory_iterator(expanded_path,
                                                              fs::directory_options::skip_permission_denied);
             const auto& entry : iterator)
        {
            if (!recursive && iterator.depth() > 0)
            {
                continue; // Skip subdirectories if not recursive
            }
            if (entry.is_regular_file() &&
                isFileExtensionMatched(entry.path().string(), filterExtensions))
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

std::vector<SmartRule> loadSmartRules(const std::string& rules_dir_path)
{
    std::vector<fs::directory_entry> rule_files = getDirectoryEntries(rules_dir_path,
                                                                      false,
                                                                      {"json"});
    std::vector<SmartRule> rules;
    for (const auto& rule_file : rule_files)
    {
        //read json file
        std::ifstream file(rule_file.path());

        if (!file.is_open())
        {
            spdlog::error("Error: Could not open file: {}", rule_file.path().string());
            continue;
        }
        nlohmann::json json_data = nlohmann::json::parse(file);

        auto rule = SmartRule();
        rule.load_json(json_data);
        rules.push_back(rule);
    }

    return rules;
}

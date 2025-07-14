//
// Created by ken on 7/10/25.
//

#ifndef SMARTRULE_H
#define SMARTRULE_H

#include <filesystem>
#include <nlohmann/json.hpp>
#include <regex>
#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

enum ConditionType
{
    EXTENSION_TYPE,
    REGEX_TYPE
};

class RuleCondition
{
public:
    virtual ~RuleCondition() {};

    ConditionType condition_type;

    virtual bool isConditionMatched(const std::string& file_path)
    {
        return false; // Default implementation, should be overridden
    };
};

class ExtensionRuleCondition final : public RuleCondition
{
public:
    std::vector<std::string> extensions; // List of file extensions to match
    ExtensionRuleCondition()
    {
        condition_type = EXTENSION_TYPE;
    }

    bool isConditionMatched(const std::string& file_path) override;
};

class RegexRuleCondition final : public RuleCondition
{
public:
    std::string regex;

    RegexRuleCondition()
    {
        condition_type = REGEX_TYPE;
    }

    bool isConditionMatched(const std::string& file_path) override;
};

class SmartRuleTarget
{
public:
    bool match_any_condition = true; // If true, matches if any condition is met
    std::string target_path; // Path to the file or directory to apply the rule
    std::vector<RuleCondition*> conditions;

    [[nodiscard]] bool isConditionsMatched(const std::string& file_path) const;

    SmartRuleTarget() = default;
};


class SmartRule
{
public:
    std::string rule_name;
    std::string rule_description;
    std::string directory_path;
    bool is_recursive_search = false; // If true, searches subdirectories
    std::vector<SmartRuleTarget> targets;

    void load_json(nlohmann::json& j);

    SmartRule() = default;
};

#endif //SMARTRULE_H

//
// Created by ken on 7/10/25.

#include "smart_rule.h"

/**
 * check if the rule conditions are matched against a file path.
 * @param file_path the path of the file to check against the rule
 * @return true if the rule is matched, false otherwise
 */
bool SmartRuleTarget::isConditionsMatched(const std::string& file_path) const
{
    if (match_any_condition)
    {
        for (const auto& condition : conditions)
        {
            if (condition->isConditionMatched(file_path)) { return true; }
        }
        return false;
    }

    for (const auto& condition : conditions)
    {
        // All conditions must match
        if (!condition->isConditionMatched(file_path)) { return false; }
    }
    return true;
}

void SmartRule::load_json(nlohmann::json& j)
{
    j.at("rule_name").get_to(rule_name);
    j.at("rule_description").get_to(rule_description);
    j.at("directory_path").get_to(directory_path);
    j.at("is_recursive_search").get_to(is_recursive_search);

    // initialize targets
    targets = std::vector<SmartRuleTarget>();
    auto targetIterator = j.at("targets").begin();
    while (targetIterator != j.at("targets").end())
    {
        SmartRuleTarget target;
        targetIterator->at("target_path").get_to(target.target_path);
        targetIterator->at("match_any_condition").get_to(target.match_any_condition);

        auto conditionIterator = targetIterator->at("conditions").begin();
        while (conditionIterator != targetIterator->at("conditions").end())
        {
            if (conditionIterator->at("condition_type") == "EXTENSION_TYPE")
            {
                auto condition = new ExtensionRuleCondition();
                conditionIterator->at("extensions").get_to(condition->extensions);
                target.conditions.push_back(condition);
            }
            ++conditionIterator;
        }
        targets.push_back(target);
        ++targetIterator;
    }
}


/**
 *  Check if the file path matches any of the specified extensions.
 * @param file_path the path of the file to check
 * @return true if the file's extension matches any in the list, false otherwise
 */
bool ExtensionRuleCondition::isConditionMatched(const std::string& file_path)
{
    std::string extension = fs::path(file_path).extension().string();

    if (!extension.empty() && extension[0] == '.')
    {
        extension = extension.substr(1); // Remove leading dot
    }

    const auto iterator = std::ranges::find(extensions, extension);

    return iterator != extensions.end();
}

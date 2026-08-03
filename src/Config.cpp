#include "Config.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

namespace
{
    using json = nlohmann::json;
}


Config::Config(const std::string& configPath)
{
    load(configPath);
}


const std::vector<Rule>& Config::getRules() const
{
    return rules_;
}


void Config::load(const std::string& configPath)
{
    std::ifstream file(configPath);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Could not open config file: " + configPath
        );
    }

    json data;
    file >> data;

    for (const auto& ruleData : data["rules"])
    {
        std::vector<std::string> extensions =
            ruleData["extensions"]
            .get<std::vector<std::string>>();

        std::string destination =
            ruleData["destination"]
            .get<std::string>();

        rules_.emplace_back(
            extensions,
            destination
        );
    }
}
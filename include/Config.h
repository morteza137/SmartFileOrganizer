#pragma once

#include <string>
#include <vector>

#include "Rule.h"

class Config
{
public:
    explicit Config(const std::string& configPath);

    const std::vector<Rule>& getRules() const;

private:
    std::vector<Rule> rules_;
    void load(const std::string& configPath);
};
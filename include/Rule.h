#pragma once

#include <string>
#include <vector>

#include "FileInfo.h"

class Rule
{
public:
    Rule(const std::vector<std::string>& extensions,
         const std::string& destination);

    bool matches(const FileInfo& file) const;
    const std::string& getDestination() const;

private:
    std::vector<std::string> extensions_;
    std::string destination_;
};
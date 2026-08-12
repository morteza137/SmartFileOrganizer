#pragma once

#include <vector>

#include "FileInfo.h"
#include "Rule.h"
#include "FileOperation.h"

class Planner
{
public:
    std::vector<FileOperation> plan(
        const std::vector<FileInfo>& files,
        const std::vector<Rule>& rules,
        const std::filesystem::path& rootDirectory
    ) const;
};
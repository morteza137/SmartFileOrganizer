#pragma once

#include <filesystem>

#include "Config.h"
#include "Executor.h"
#include "Logger.h"
#include "Planner.h"
#include "Scanner.h"

class Organizer
{
public:
    void organize(
        const std::filesystem::path& directory,
        const std::filesystem::path& configPath,
        bool dryRun = false
    ) const;
};
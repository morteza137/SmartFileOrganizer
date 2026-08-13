#pragma once

#include <filesystem>
#include <string>

struct CLIOptions
{
    std::filesystem::path directory;
    std::filesystem::path configPath{"config.json"};

    bool dryRun{false};
    bool recursive{false};
    bool help{false};
};

class CLI
{
public:
    CLIOptions parse(int argc, char* argv[]) const;

    void printHelp() const;
};
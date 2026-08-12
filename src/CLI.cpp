#include "CLI.h"

#include <stdexcept>
#include <iostream>

CLIOptions CLI::parse(int argc, char* argv[]) const
{
    CLIOptions options;

    if (argc < 2)
    {
        throw std::runtime_error(
            "Directory argument is required."
        );
    }

    for (int i = 1; i < argc; ++i)
    {
        std::string argument = argv[i];

        if (argument == "--help")
        {
            options.help = true;
        }
        else if (argument == "--dry-run")
        {
            options.dryRun = true;
        }
        else if (argument == "--config")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error(
                    "--config requires a file path."
                );
            }

            options.configPath = argv[++i];
        }
        else if (options.directory.empty())
        {
            options.directory = argument;
        }
        else
        {
            throw std::runtime_error(
                "Unknown argument: " + argument
            );
        }
    }

    return options;
}

void CLI::printHelp() const
{
    std::cout
        << "Smart File Organizer\n\n"

        << "Usage:\n"
        << "  organizer <directory> [options]\n\n"

        << "Options:\n"
        << "  --help              Show this help message\n"
        << "  --dry-run           Show operations without moving files\n"
        << "  --config <file>     Specify configuration file\n";
}
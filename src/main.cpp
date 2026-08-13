#include <iostream>

#include "CLI.h"
#include "Organizer.h"

int main(int argc, char* argv[])
{
    try
    {
        CLI cli;

        CLIOptions options = cli.parse(argc, argv);

        if (options.help)
        {
            cli.printHelp();
            return 0;
        }

        Organizer organizer;

        organizer.organize(
            options.directory,
            options.configPath,
            options.dryRun,
            options.recursive
        );
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "[ERROR] "
            << e.what()
            << '\n';

        return 1;
    }

    return 0;
}
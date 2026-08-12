#include "Organizer.h"

#include <iostream>

void Organizer::organize(
    const std::filesystem::path& directory,
    const std::filesystem::path& configPath) const
{
    Config config(configPath);

    Scanner scanner;

    auto files = scanner.scan(directory);

    Planner planner;

    auto operations =
        planner.plan(
            files,
            config.getRules(),
            directory
        );

    Executor executor;

    for (const auto& operation : operations)
    {
        executor.execute(operation);

        std::cout
            << "Moved: "
            << operation.getSource()
            << " -> "
            << operation.getDestination()
            << '\n';
    }
}
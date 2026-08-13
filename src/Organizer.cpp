#include "Organizer.h"

void Organizer::organize(
    const std::filesystem::path& directory,
    const std::filesystem::path& configPath,
    bool dryRun,
    bool recursive) const
{
    Logger logger;

    logger.info("Starting organizer");

    Config config(configPath);

    Scanner scanner;

    logger.info(
        "Scanning directory: "
        + directory.string()
    );

    if (recursive)
    {
        logger.info("Recursive scan enabled");
    }

    auto files = scanner.scan(
        directory,
        recursive
    );

    logger.info(
        "Found "
        + std::to_string(files.size())
        + " files"
    );

    Planner planner;

    auto operations =
        planner.plan(
            files,
            config.getRules(),
            directory
        );

    logger.info(
        "Planned "
        + std::to_string(operations.size())
        + " operations"
    );

    Executor executor(dryRun);

    for (const auto& operation : operations)
    {
        executor.execute(operation);
    }

    logger.info("Organizer finished");
}
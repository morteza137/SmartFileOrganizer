#include "Executor.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

Executor::Executor(bool dryRun)
    : dryRun_(dryRun)
{
}

void Executor::execute(
    const FileOperation& operation) const
{
    const auto& source = operation.getSource();
    const auto& destination = operation.getDestination();

    if (dryRun_)
    {
        std::cout
            << "[DRY RUN] Would move: "
            << source
            << " -> "
            << destination
            << '\n';

        return;
    }

    if (!std::filesystem::exists(source))
    {
        throw std::runtime_error(
            "Source file does not exist: "
            + source.string()
        );
    }

    if (std::filesystem::exists(destination))
    {
        throw std::runtime_error(
            "Destination already exists: "
            + destination.string()
        );
    }

    std::filesystem::create_directories(
        destination.parent_path()
    );

    std::filesystem::rename(
        source,
        destination
    );
}
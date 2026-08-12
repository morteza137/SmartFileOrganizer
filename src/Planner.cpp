#include "Planner.h"

std::vector<FileOperation>
Planner::plan(
    const std::vector<FileInfo>& files,
    const std::vector<Rule>& rules,
    const std::filesystem::path& rootDirectory) const
{
    std::vector<FileOperation> operations;

    for (const auto& file : files)
    {
        for (const auto& rule : rules)
        {
            if (rule.matches(file))
            {
                std::filesystem::path destination =
                    rootDirectory /
                    rule.getDestination() /
                    file.getFilename();

                operations.emplace_back(
                    file.getPath(),
                    destination
                );

                break;
            }
        }
    }

    return operations;
}
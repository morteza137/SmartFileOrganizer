#include "Scanner.h"

#include <stdexcept>

std::vector<FileInfo> Scanner::scan(
    const std::filesystem::path& directory,
    bool recursive) const
{
    if (!std::filesystem::exists(directory))
    {
        throw std::runtime_error(
            "Directory does not exist: "
            + directory.string()
        );
    }

    if (!std::filesystem::is_directory(directory))
    {
        throw std::runtime_error(
            "Path is not a directory: "
            + directory.string()
        );
    }

    std::vector<FileInfo> files;

    if (recursive)
    {
        for (const auto& entry :
             std::filesystem::recursive_directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                files.emplace_back(entry);
            }
        }
    }
    else
    {
        for (const auto& entry :
             std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                files.emplace_back(entry);
            }
        }
    }

    return files;
}
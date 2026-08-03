#include "Scanner.h"

#include <stdexcept>

namespace fs = std::filesystem;

std::vector<FileInfo> Scanner::scan(
    const fs::path& directory) const
{
    if (!fs::exists(directory))
    {
        throw std::runtime_error(
            "Directory does not exist."
        );
    }

    if (!fs::is_directory(directory))
    {
        throw std::runtime_error(
            "Path is not a directory."
        );
    }

    std::vector<FileInfo> files;

    for (const auto& entry :
         fs::directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            files.emplace_back(entry);
        }
    }

    return files;
}
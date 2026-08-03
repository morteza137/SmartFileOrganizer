#pragma once

#include <filesystem>

class FileOperation
{
public:
    FileOperation(const std::filesystem::path& source,
                  const std::filesystem::path& destination);

    const std::filesystem::path& getSource() const;
    const std::filesystem::path& getDestination() const;

private:
    std::filesystem::path source_;
    std::filesystem::path destination_;
};
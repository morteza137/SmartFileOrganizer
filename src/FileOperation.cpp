#include "FileOperation.h"

FileOperation::FileOperation(
    const std::filesystem::path& source,
    const std::filesystem::path& destination)
    : source_(source),
      destination_(destination)
{
}

const std::filesystem::path&
FileOperation::getSource() const
{
    return source_;
}

const std::filesystem::path&
FileOperation::getDestination() const
{
    return destination_;
}
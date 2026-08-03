#include "FileInfo.h"

namespace fs = std::filesystem;

// Constructor
FileInfo::FileInfo(const fs::directory_entry& entry)
    : path_(entry.path()),
      size_(entry.is_regular_file() ? entry.file_size() : 0),
      lastWriteTime_(entry.last_write_time())
{
}

// Getters
const fs::path& FileInfo::getPath() const
{
    return path_;
}

std::string FileInfo::getFilename() const
{
    return path_.filename().string();
}

std::string FileInfo::getExtension() const
{
    return path_.extension().string();
}

std::uintmax_t FileInfo::getSize() const
{
    return size_;
}

const fs::file_time_type& FileInfo::getLastWriteTime() const
{
    return lastWriteTime_;
}
#pragma once

#include <filesystem>
#include <string>
#include <cstdint>

class FileInfo
{
public:
    FileInfo() = default;
    explicit FileInfo(const std::filesystem::directory_entry& entry);

    const std::filesystem::path& getPath() const;
    std::string getFilename() const;
    std::string getExtension() const;
    std::uintmax_t getSize() const;
    const std::filesystem::file_time_type& getLastWriteTime() const;

private:
    std::filesystem::path path_;
    std::uintmax_t size_{0};
    std::filesystem::file_time_type lastWriteTime_;
};
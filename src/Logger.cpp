#include "Logger.h"

#include <iostream>

void Logger::info(const std::string& message) const
{
    std::cout
        << "[INFO] "
        << message
        << '\n';
}

void Logger::error(const std::string& message) const
{
    std::cerr
        << "[ERROR] "
        << message
        << '\n';
}
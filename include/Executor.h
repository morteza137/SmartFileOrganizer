#pragma once

#include "FileOperation.h"

class Executor
{
public:
    void execute(const FileOperation& operation) const;
};
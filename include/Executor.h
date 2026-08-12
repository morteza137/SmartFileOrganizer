#pragma once

#include "FileOperation.h"

class Executor
{
public:
    explicit Executor(bool dryRun = false);

    void execute(const FileOperation& operation) const;

private:
    bool dryRun_;
};
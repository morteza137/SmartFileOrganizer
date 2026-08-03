#include "Rule.h"

#include <algorithm>

Rule::Rule(const std::vector<std::string>& extensions,
           const std::string& destination)
    : extensions_(extensions),
      destination_(destination)
{
}

bool Rule::matches(const FileInfo& file) const
{
    const std::string extension = file.getExtension();

    return std::find(
               extensions_.begin(),
               extensions_.end(),
               extension) != extensions_.end();
}

const std::string& Rule::getDestination() const
{
    return destination_;
}
#pragma once
#include <string>
#include <vector>

// An interface class that requires that the inheriting class implement a function to convert some
// object (a creature, etc) to a string.
//
// The various Dumper classes inherit from StringConverter.
class StringConverter
{
  public:
    virtual ~StringConverter() = default;
    virtual std::string str() const = 0;
};

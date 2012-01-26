#pragma once
#include <string>

// An interface class that requires that the inheriting class implement a function to convert some
// object (a creature, etc) to a string.
//
// The various Dumper classes inherit from StringConverter.
class StringConverter
{
  public:
    virtual ~StringConverter() {};
    virtual std::string str() const = 0;
};

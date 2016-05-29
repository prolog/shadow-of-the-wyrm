#pragma once
#include <string>
#include "CreatureFeatures.hpp"

class SizeTextKeys
{
  public:
    static const std::string SIZE;
    static const std::string SIZE_TINY;
    static const std::string SIZE_SMALL;
    static const std::string SIZE_MEDIUM;
    static const std::string SIZE_LARGE;
    static const std::string SIZE_HUGE;
    static const std::string SIZE_BEHEMOTH;
    
    static std::string get_size_sid_from_creature_size(const CreatureSize size);
    
  protected:
    SizeTextKeys();
    ~SizeTextKeys();
};

#pragma once
#include <string>

class ReligionManager
{
  public:
    ReligionManager();

    std::string get_deity_name_sid(const std::string& deity_id) const;
};

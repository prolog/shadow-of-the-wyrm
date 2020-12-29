#pragma once
#include <string>

class ProcgenTextKeys
{
  public:
    static const std::string HIRELING_DESC_SID;
    static const std::string HIRELING_SHORT_DESC_SID;
    static const std::string HIRELING_TEXT_DETAILS_SID;
    static const std::string HIRELING_LUA_SCRIPT_SID;

    static const std::string ADVENTURER_DESC_SID;
    static const std::string ADVENTURER_SHORT_DESC_SID;
    static const std::string ADVENTURER_TEXT_DETAILS_SID;
    static const std::string ADVENTURER_LUA_SCRIPT_SID;

  protected:
    ProcgenTextKeys();
    ~ProcgenTextKeys();
};
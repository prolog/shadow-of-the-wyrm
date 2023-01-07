#pragma once
#include <string>

class SettingTextKeys
{
  public:
    static const std::string SETTING_AUTOPICKUP;
    static const std::string SETTING_AUTOPICKUP_EXCLUDE_CORPSES;
    static const std::string SETTING_AUTOPICKUP_EXCLUDE_UNPAID;
    static const std::string SETTING_AUTOMELEE_AT_RANGE;

  protected:
    SettingTextKeys();
    ~SettingTextKeys();
};


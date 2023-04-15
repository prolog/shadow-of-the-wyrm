#pragma once
#include <string>

class SettingTextKeys
{
  public:
    static const std::string SETTING_AUTOPICKUP;
    static const std::string SETTING_AUTOPICKUP_EXCLUDE_CORPSES;
    static const std::string SETTING_AUTOPICKUP_EXCLUDE_UNPAID;
    static const std::string SETTING_AUTOPICKUP_EXCLUDE_OVER_WEIGHT;
    static const std::string SETTING_AUTOMELEE_AT_RANGE;
    static const std::string SETTING_AUTOMOVE_ALWAYS_STOP_ON_ITEMS;

    static std::string get_autopickup_exclude_over_weight_message(const std::string& weight_in_lbs);

  protected:
    SettingTextKeys();
    ~SettingTextKeys();
};


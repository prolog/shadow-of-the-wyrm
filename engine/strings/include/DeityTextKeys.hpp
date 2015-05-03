#pragma once
#include <string>

class DeityTextKeys
{
  public:
    static std::string get_prayer_message(const std::string& deity_sid);
    static std::string get_deity_change_message(const std::string& deity_sid);
    
    static const std::string PRAYER_INITIAL_MESSAGE;
    static const std::string PRAYER_DO_NOTHING;
    static const std::string PRAYER_FULL_HP;
    static const std::string PRAYER_FULL_AP;
    static const std::string PRAYER_SATIATE;
    static const std::string PRAYER_RESTORE_STATUS;
    static const std::string PRAYER_CROWNING;
    static const std::string PRAYER_WORLD_MAP;
    static const std::string PRAYER_PROTECTION;
    static const std::string DEITY_ACTION_DISPLEASED;
    static const std::string DEITY_FALLEN_CHAMPION;
    static const std::string DEITY_CHANGE_MESSAGE;
    
  protected:
    DeityTextKeys();
    ~DeityTextKeys();
};

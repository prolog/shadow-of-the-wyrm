#pragma once
#include <string>

class DeityTextKeys
{
  public:
    static std::string get_prayer_message(const std::string& deity_sid);
    
    static const std::string PRAYER_INITIAL_MESSAGE;
    static const std::string PRAYER_DO_NOTHING;
    static const std::string PRAYER_FULL_HP;
    static const std::string DEITY_ACTION_DISPLEASED;
    
  protected:
    DeityTextKeys();
    ~DeityTextKeys();
};

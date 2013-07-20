#pragma once
#include <string>

class CreatureProperties
{
  public:
    static const std::string CREATURE_PROPERTIES_CHAT_SCRIPT;
    static const std::string CREATURE_PROPERTIES_LAST_BESTIARY_SEARCH;
    static const std::string CREATURE_PROPERTIES_HASTE_MODIFIER; // used for both haste & slow

  protected:
    CreatureProperties();
    ~CreatureProperties();
};

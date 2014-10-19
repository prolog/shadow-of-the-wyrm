#pragma once
#include <string>
#include "AlignmentEnums.hpp"

// Text keys surrounding sacrificing items, crowning, etc.
class SacrificeTextKeys
{
  public:
    static const std::string SACRIFICE_NO_ALTAR;
    static const std::string SACRIFICE_NO_ITEMS;
    static const std::string SACRIFICE_NO_ITEM_SELECTED;

    static std::string get_sacrifice_message(const AlignmentRange alignment, ItemPtr item, const bool creature_blind);
    static std::string get_piety_message(const int piety);
    static std::string get_altar_conversion_message(const std::string& deity_name_sid);

  protected:
    SacrificeTextKeys();

    static const std::string SACRIFICE_MESSAGE_TIER_1;
    static const std::string SACRIFICE_MESSAGE_TIER_2;
    static const std::string SACRIFICE_MESSAGE_TIER_3;
    static const std::string SACRIFICE_MESSAGE_TIER_4;
    static const std::string SACRIFICE_MESSAGE_CROWNING;
    static const std::string SACRIFICE_MESSAGE_DISLIKED;

    static const std::string SACRIFICE_MESSAGE_EVIL;
    static const std::string SACRIFICE_MESSAGE_GOOD;
    static const std::string SACRIFICE_MESSAGE_NEUTRAL;
    static const std::string SACRIFICE_MESSAGE_CONVERT_ALTAR;
};


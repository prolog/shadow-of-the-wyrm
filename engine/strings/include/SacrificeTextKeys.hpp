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

  protected:
    SacrificeTextKeys();

    static const std::string SACRIFICE_MESSAGE_EVIL;
    static const std::string SACRIFICE_MESSAGE_GOOD;
    static const std::string SACRIFICE_MESSAGE_NEUTRAL;
};


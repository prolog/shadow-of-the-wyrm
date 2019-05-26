#pragma once
#include <string>
#include "common.hpp"
#include "Consumable.hpp"

class ItemTextKeys
{
  public:
    static const std::string ITEM_GLOW;
    static const std::string ITEM_MULTIPLE;
    static const std::string ITEM_CODEX_NOT_IDENTIFIED;
    static const std::string ITEM_CODEX_NO_INFORMATION_FOUND;

    static std::string get_value(const uint value);
    static std::string get_nutrition_message(ConsumablePtr consumable);
    static std::string get_standard_drinks_message(ConsumablePtr consumable);

  protected:
    ItemTextKeys();
    ~ItemTextKeys();

    static const std::string ITEM_VALUE;
    static const std::string NUTRITION_MESSAGE;
    static const std::string STANDARD_DRINKS_MESSAGE;
};

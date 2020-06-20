#pragma once
#include <string>
#include "common.hpp"
#include "Consumable.hpp"
#include "Wand.hpp"

class ItemTextKeys
{
  public:
    static const std::string ITEM_TRIED;
    static const std::string ITEM_GLOW;
    static const std::string ITEM_MULTIPLE;
    static const std::string ITEM_CODEX_NOT_IDENTIFIED;
    static const std::string ITEM_CODEX_NO_INFORMATION_FOUND;

    static std::string get_value(const uint value);
    static std::string get_nutrition_message(ConsumablePtr consumable);
    static std::string get_standard_drinks_message(ConsumablePtr consumable);
    static std::string get_number_of_charges_message(WandPtr wand);
    static std::string get_wearable_protection_message(const int evade, const int soak);
    static std::string get_speed_modifier_message(const int bonus);

  protected:
    ItemTextKeys();
    ~ItemTextKeys();

    static const std::string ITEM_VALUE;
    static const std::string NUTRITION_MESSAGE;
    static const std::string STANDARD_DRINKS_MESSAGE;
    static const std::string NUMBER_OF_CHARGES_MESSAGE;
    static const std::string WEARABLE_PROTECTION_MESSAGE;
    static const std::string SPEED_BONUS_MESSAGE;
    static const std::string SPEED_PENALTY_MESSAGE;
};

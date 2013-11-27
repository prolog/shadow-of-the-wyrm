#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "StatusTypes.hpp"

class FoodAction : public IActionManager
{
  public:
    ActionCostValue eat(CreaturePtr creature, ActionManager * const am);
    void add_hunger_level_message_if_necessary(CreaturePtr creature, const int old_hunger_level, const int new_hunger_level);

protected:
    friend class ActionManager;
    friend class CreatureHungerTimer;
    FoodAction();

    bool eat_food(CreaturePtr creature, ItemPtr food);

    void add_food_message(CreaturePtr creature, ItemPtr food, const bool successfully_ate);

    ActionCostValue get_action_cost_value() const override;

    static void initialize_hunger_message_sid_map();
    static std::map<HungerLevel, std::string> hunger_message_sid_map;
};


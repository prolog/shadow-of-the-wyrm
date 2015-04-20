#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "IItemFilter.hpp"
#include "StatusTypes.hpp"

class FoodAction : public IActionManager
{
  public:
    ActionCostValue eat(CreaturePtr creature, ActionManager * const am);
    void add_hunger_level_message_if_necessary(CreaturePtr creature, const int old_hunger_level, const int new_hunger_level);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class CreatureHungerTimer;
    FoodAction();

    ActionCostValue eat_food_off_ground(CreaturePtr creature, const std::list<IItemFilterPtr>& display_list);

    bool eat_food(CreaturePtr creature, ItemPtr food, IInventoryPtr inventory_for_food);

    void add_food_message(CreaturePtr creature, ItemPtr food, const bool successfully_ate);

    static void initialize_hunger_message_sid_map();
    static std::map<HungerLevel, std::string> hunger_message_sid_map;
};


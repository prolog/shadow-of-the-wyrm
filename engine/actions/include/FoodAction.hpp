#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "IItemFilter.hpp"
#include "StatusTypes.hpp"

class FoodAction : public IActionManager
{
  public:
    ActionCostValue eat(CreaturePtr creature, ActionManager * const am);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class CreatureHungerTimer;
    FoodAction();

    ActionCostValue eat_food_off_ground(CreaturePtr creature, const std::list<IItemFilterPtr>& display_list);

    bool eat_food(CreaturePtr creature, TilePtr tile, ItemPtr food, IInventoryPtr inventory_for_food);
    void create_seed_on_tile(CreaturePtr creature, TilePtr tile, const std::string& seed_item_id);
    void add_food_message(CreaturePtr creature, ItemPtr food, const bool successfully_ate);
};


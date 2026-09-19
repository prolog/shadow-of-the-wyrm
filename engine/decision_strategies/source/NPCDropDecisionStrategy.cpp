#include "Commands.hpp"
#include "EngineConversion.hpp"
#include "NPCDropDecisionStrategy.hpp"
#include "Wand.hpp"

CommandPtr NPCDropDecisionStrategy::decide(CreaturePtr creature, MapPtr map)
{
  CommandPtr drop_cmd;

  if (creature != nullptr && map != nullptr)
  {
    BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);

    if (bl == BurdenLevel::BURDEN_LEVEL_OVERBURDENED)
    {
      drop_cmd = get_drop_decision_overburdened(creature, map);
    }
    else
    {
      drop_cmd = get_drop_decision(creature, map);
    }
  }

  return drop_cmd;
}

CommandPtr NPCDropDecisionStrategy::get_drop_decision_overburdened(CreaturePtr creature, MapPtr map)
{
  CommandPtr drop_cmd;

  if (creature != nullptr && map != nullptr)
  {
    const std::list<ItemPtr>& items = creature->get_inventory()->get_items_cref();
    uint highest_weight = 0;

    // If we're overburdened, drop the heaviest item.
    for (ItemPtr item : items)
    {
      uint i_weight = item->get_weight().get_weight();
      
      if (i_weight > highest_weight)
      {
        highest_weight = i_weight;
        drop_cmd = std::make_unique<DropCommand>(item->get_id());
      }
    }
  }

  return drop_cmd;
}

CommandPtr NPCDropDecisionStrategy::get_drop_decision(CreaturePtr creature, MapPtr map)
{
  CommandPtr drop_cmd;

  if (creature != nullptr && map != nullptr)
  {
    const std::list<ItemPtr>& items = creature->get_inventory()->get_items_cref();

    for (ItemPtr item : items)
    {
      if (item != nullptr)
      {
        if (item->get_type() == ItemType::ITEM_TYPE_WAND)
        {
          WandPtr wand = std::dynamic_pointer_cast<Wand>(item);

          if (wand != nullptr)
          {
            if (wand->get_charges().get_current() == 0)
            {
              drop_cmd = std::make_unique<DropCommand>(wand->get_id());
            }
          }
        }
      }
    }
  }

  return drop_cmd;
}
#include "Commands.hpp"
#include "NPCDropDecisionStrategy.hpp"
#include "Wand.hpp"

CommandPtr NPCDropDecisionStrategy::decide(CreaturePtr creature, MapPtr map)
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

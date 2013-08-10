#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "EffectFactory.hpp"
#include "ItemFilterFactory.hpp"
#include "ReadStrategyFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "ReadAction.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

// Read a scroll or spellbook.  Scrolls cast a single spell, while
// spellbooks contain spells, and can be used to learn an individual
// spell (the ADOM/nethack model, rather than Angband's/DCSS's).
ActionCostValue ReadAction::read(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  CurrentCreatureAbilities cca;

  // Make sure that the creature can actually see before trying to read.
  if (!cca.can_see(creature, true))
  {
    return action_cost_value;
  }

  if (creature && am)
  {
    list<IItemFilterPtr> display_list = ItemFilterFactory::create_readable_filter();
    ItemPtr selected_readable_item = am->inventory(creature, creature->get_inventory(), display_list, false);
    
    if (selected_readable_item)
    {
      ReadablePtr readable = boost::dynamic_pointer_cast<Readable>(selected_readable_item);

      if (readable)
      {
        ReadStrategyPtr read_strategy = ReadStrategyFactory::create_read_strategy(readable->get_type());

        if (read_strategy)
        {
          // Cast or learn the spell from the scroll/spellbook/etc.
          action_cost_value = read_strategy->read(creature, am, readable);
        }
      }
    }    
  }

  return action_cost_value;
}

ActionCostValue ReadAction::get_action_cost_value() const
{
  return 1;
}

#include "WheelAndLoomManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "WeavingConstants.hpp"

using namespace std;

WheelAndLoomManipulator::WheelAndLoomManipulator(FeaturePtr feature)
: IFeatureManipulator(feature),
loom_map({ {EQUIPMENT_WORN_AROUND_BODY, "_cloak"}, {EQUIPMENT_WORN_BODY, "_robes"} })
{
}

void WheelAndLoomManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_WHEEL_AND_LOOM));
    manager.send();
  }
}

// Weave natural fibres into cloaks and robes.
// Any improvements to the items are in terms of resistances.
bool WheelAndLoomManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  if (tile && creature)
  {

    // Check for weaving skill.
    if (creature->get_skills().get_value(SKILL_GENERAL_WEAVING) <= 0)
    {
      add_no_weaving_skill_message(creature);
    }
    else
    {
      // Has weaving - check for fibres, etc.
      if (!creature->get_inventory()->has_item_with_property(WeavingConstants::WEAVING_MATERIAL_TYPE_KEY))
      {
        add_no_fibres_message(creature);
      }
      else
      {
        // Has fibres (whiteflower, etc).  Select one, then a worn slot.
        Game& game = Game::instance();
        ActionManager& am = game.get_action_manager_ref();

        vector<pair<string, string>> item_property_filter = { make_pair(WeavingConstants::WEAVING_MATERIAL_TYPE_KEY, "") };
        list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_property_type_filter(item_property_filter);

        ItemPtr selected_fibre = am.inventory(creature, creature->get_inventory(), display_filter_list, false);

        if (selected_fibre)
        {
        }
      }
    }
  }

  return handled;
}

void WheelAndLoomManipulator::add_no_weaving_skill_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WEAVE_NO_WEAVING_SKILL));
  manager.send();
}

// The creature has no fibres in its inventory - add a message.
void WheelAndLoomManipulator::add_no_fibres_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WEAVE_NO_FIBRES));
  manager.send();
}
#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "SkinAction.hpp"

using std::string;

SkinAction::SkinAction()
{
}

ActionCostValue SkinAction::skin(CreaturePtr creature, const ActionManager * const am)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    MapType map_type = current_map->get_map_type();

    if (map_type == MAP_TYPE_WORLD)
    {
      add_skin_world_map_message(creature);
    }
    // Overworld/underworld map - we can attempt to skin.
    else
    {
      acv = get_action_cost_value(creature);
    }
  }

  return acv;
}

void SkinAction::add_skin_world_map_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_WORLD_MAP));
  manager.send();
}

ActionCostValue SkinAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

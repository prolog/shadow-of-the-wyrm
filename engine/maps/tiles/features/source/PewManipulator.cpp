#include "ActionTextKeys.hpp"
#include "PewManipulator.hpp"
#include "MessageManagerFactory.hpp"
#include "Game.hpp"

using namespace std;

PewManipulator::PewManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

// Pews are a good feature, and only the good deities care about the
// desecration of pews.
void PewManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr /*feature_tile*/, const Coordinate& /*feature_coord*/, FeaturePtr /*feature*/)
{
  desecrate(creature, current_map);
}

bool PewManipulator::desecrate(CreaturePtr creature, MapPtr current_map)
{
  Game::instance().get_deity_action_manager_ref().notify_action(creature, current_map, CreatureActionKeys::ACTION_DESECRATE_GOOD, false);
  return true;
}

bool PewManipulator::handle(TilePtr /*tile*/, CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_HANDLE_PEW));
    manager.send();
  }

  return true;
}

bool PewManipulator::drop(CreaturePtr /*dropping_creature*/, TilePtr /*tile*/, ItemPtr /*item*/)
{
  return false;
}

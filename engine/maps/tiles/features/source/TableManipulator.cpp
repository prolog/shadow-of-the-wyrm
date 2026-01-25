#include "TableManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

TableManipulator::TableManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

void TableManipulator::strike(CreaturePtr creature, MapPtr /*current_map*/, TilePtr /*feature_tile*/, const Coordinate& /*feature_coord*/, FeaturePtr /*feat*/, ItemPtr /* item */)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_STRIKE_TABLE));
    manager.send();
  }
}

bool TableManipulator::handle(TilePtr /*tile*/, CreaturePtr /*creature*/)
{
  return false;
}

bool TableManipulator::drop(CreaturePtr /*dropping_creature*/, TilePtr /*tile*/, ItemPtr /*item*/)
{
  return false;
}

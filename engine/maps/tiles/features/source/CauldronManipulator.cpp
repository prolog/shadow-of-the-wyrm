#include "CauldronManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

CauldronManipulator::CauldronManipulator(FeaturePtr feature) 
: DefaultFeatureManipulator(feature)
{
}

void CauldronManipulator::strike(CreaturePtr creature, MapPtr /*current_map*/, TilePtr /*feature_tile*/, const Coordinate& /*feature_coord*/, FeaturePtr /*feature*/)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_CAULDRON));
    manager.send();
  }
}

// Manipulating a cauldron allows the character to brew any recipes they know.
bool CauldronManipulator::handle(TilePtr /*tile*/, CreaturePtr /*creature*/)
{
  // ... TODO ...
  return false;
}


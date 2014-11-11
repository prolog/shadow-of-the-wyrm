#include "JewelerWorkbenchManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SmithingConstants.hpp"

using namespace std;

JewelerWorkbenchManipulator::JewelerWorkbenchManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void JewelerWorkbenchManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_JEWELER_WORKBENCH));
    manager.send();
  }
}

bool JewelerWorkbenchManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  return handled;
}



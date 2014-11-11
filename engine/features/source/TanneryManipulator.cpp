#include "TanneryManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SmithingConstants.hpp"
#include "WeaponManager.hpp"

using namespace std;

TanneryManipulator::TanneryManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void TanneryManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_TANNERY));
    manager.send();
  }
}

bool TanneryManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool handled = false;

  return handled;
}



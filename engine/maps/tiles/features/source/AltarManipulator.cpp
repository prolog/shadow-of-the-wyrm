#include "ActionTextKeys.hpp"
#include "AltarManipulator.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

AltarManipulator::AltarManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

bool AltarManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_HANDLE_ALTAR));
    manager.send();
  }

  return true;
}


#include "SarcophagusManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

SarcophagusManipulator::SarcophagusManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void SarcophagusManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_SARCOPHAGUS));
    manager.send();
  }
}

bool SarcophagusManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool sarc_opened = false;

  if (tile != nullptr && creature != nullptr && feature != nullptr)
  {
  }

  return sarc_opened;
}

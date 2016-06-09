#include "SarcophagusManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "TextMessages.hpp"

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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::ACTION_OPEN_SARCOPHAGUS_CONFIRM));
    sarc_opened = creature->get_decision_strategy()->get_confirmation();

    if (sarc_opened)
    {
      // ...
    }
  }

  return sarc_opened;
}

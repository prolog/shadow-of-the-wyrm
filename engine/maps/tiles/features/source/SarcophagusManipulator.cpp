#include "SarcophagusManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "FeatureProperties.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "TextMessages.hpp"
#include "TileProperties.hpp"

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
      bool already_opened = String::to_bool(feature->get_additional_property(FeatureProperties::FEATURE_PROPERTIES_OPEN));

      if (already_opened)
      {
        // ...
      }
      else
      {
        // ...
      }
    }
  }

  return sarc_opened;
}

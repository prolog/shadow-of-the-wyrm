#include "SarcophagusManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "DefaultTileManipulator.hpp"
#include "FeatureProperties.hpp"
#include "Game.hpp"
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
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  if (tile != nullptr && creature != nullptr && feature != nullptr)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    bool already_opened = String::to_bool(feature->get_additional_property(FeatureProperties::FEATURE_PROPERTIES_OPEN));

    if (already_opened)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_OPEN_SARCOPHAGUS_ALREADY_OPEN));
    }
    else
    {
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::ACTION_OPEN_SARCOPHAGUS_CONFIRM));
      sarc_opened = creature->get_decision_strategy()->get_confirmation();

      if (sarc_opened)
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_OPEN_SARCOPHAGUS));

        DefaultTileManipulator dtm;

        // Break the graverobbing conduct.
        creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_NO_GRAVEDIGGING);
        game.get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_GRAVEROBBING);

        // Add undead/items.
        dtm.add_undead_if_necessary(creature, current_map, tile);
        dtm.add_item_if_necessary(creature, current_map, tile);

        feature->set_additional_property(FeatureProperties::FEATURE_PROPERTIES_OPEN, to_string(true));
      }
    }
  }

  return sarc_opened;
}

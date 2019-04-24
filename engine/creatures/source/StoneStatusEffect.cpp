#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "StoneCalculator.hpp"
#include "StoneStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatueGenerator.hpp"
#include "StatusTypes.hpp"

using namespace std;

StoneStatusEffect::StoneStatusEffect()
{
  status_calc = std::make_shared<StoneCalculator>();
}

// Stoning is nasty and an eventual insta-death, so give warnings every tick.
void StoneStatusEffect::tick(CreaturePtr creature, const int danger_level) const
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    string message;

    if (creature->get_is_player())
    {
      message = get_player_application_message();
    }
    else
    {
      message = get_npc_application_message(creature);
    }

    manager.add_new_message(message);
    manager.send();
  }
}

void StoneStatusEffect::finalize(CreaturePtr creature) const
{
  if (creature != nullptr)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

    CombatManager cm;
    CreaturePtr no_creature;
    string message_sid = StatusAilmentTextKeys::STATUS_MESSAGE_STONE_FINALIZE;

    // Get the statue tile before dealing damage so that the creature is still 
    // on the map, and thus has tracked coordinates.
    TilePtr creature_tile = MapUtils::get_tile_for_creature(current_map, creature);

    // The creature should not leave a corpse if it's going to leave a statue.
    // Its equipment will also petrify with it, so disallow transfer of eq
    // from the creature to the tile, as well as random items.  These can't be
    // picked up, anyway, since statues are blocking features.
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEAVES_CORPSE, Bool::to_string(false));
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEAVES_EQUIPMENT, Bool::to_string(false));
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_ALLOWS_RANDOM_DROPS, Bool::to_string(false));

    // Ensure that the tile doesn't already have a feature.
    if (creature_tile && !creature_tile->has_feature())
    {
      // Get the description so the statue can be "a statue of a goblin", etc.
      string description_sid = creature->get_description_sid();

      // Generate the statue
      PetrifiedCorpseStatuePtr corpse_statue = StatueGenerator::generate_petrified_corpse_statue(description_sid);

      // Add it to the tile
      creature_tile->set_feature(corpse_statue);
    }
    else
    {
      // Because each tile can only have one feature, add a message about the statue
      // immediately crumbling into dust.
      message_sid = StatusAilmentTextKeys::STATUS_MESSAGE_STONE_CRUMBLE;
    }

    manager.add_new_message(StringTable::get(message_sid));
    manager.send();

    Damage stone_default;
    cm.deal_damage(no_creature, creature, source_id, creature->get_hit_points().get_base(), stone_default);
  }
}

string StoneStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE);
  
  return message;
}

string StoneStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_stone_message(creature);
  return message;
}

string StoneStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE_CURED);
  
  return message;
}

string StoneStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_stone_message(creature);
  return message;
}

string StoneStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_STONE;
}


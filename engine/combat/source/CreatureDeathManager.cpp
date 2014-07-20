#include "CombatTextKeys.hpp"
#include "CorpseFactory.hpp"
#include "CreatureDeathManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using std::string;

CreatureDeathManager::CreatureDeathManager(CreaturePtr a_creature, CreaturePtr d_creature, MapPtr current_map)
: DeathManager(a_creature, d_creature, current_map)
{
}

CreatureDeathManager::~CreatureDeathManager()
{
}

void CreatureDeathManager::die() const
{
  Game& game = Game::instance();
  
  if (map && dead_creature)
  {
    // Add the message about the creature's death.
    //
    // Ensure that this is the first thing done, e.g., prior to actually
    // removing it from the map, so that view map checks work as expected.
    // Otherwise, the creature will already be gone from the other creatures'
    // view maps.
    IMessageManager& manager = MessageManagerFactory::instance(dead_creature, GameUtils::is_player_among_creatures(attacking_creature, dead_creature));

    // If the creature was killed by another creature, get a message of the form
    // "the foo is killed!".  Otherwise, if the creature was killed by something
    // other than a creature (poison, falling, etc), use "the foo dies!".
    string death_message;
    string creature_desc = StringTable::get(dead_creature->get_description_sid());

    if (attacking_creature)
    {
      death_message = CombatTextKeys::get_monster_killed_message(creature_desc);
    }
    else
    {
      death_message = CombatTextKeys::get_monster_dies_message(creature_desc);
    }

    manager.add_new_message(death_message);
    manager.send();

    // Remove the creature from the tile.
    TilePtr attacked_tile = MapUtils::get_tile_for_creature(map, dead_creature);
    MapUtils::remove_creature(map, dead_creature);

    // Remove all equipment.
    for (int worn_slot = EQUIPMENT_WORN_HEAD; worn_slot < EQUIPMENT_WORN_LAST; worn_slot++)
    {
      game.actions.remove_item(dead_creature, static_cast<EquipmentWornLocation>(worn_slot));
    }

    // Drop inventory on to the creature's tile.
    IInventoryPtr inv = dead_creature->get_inventory();
    IInventoryPtr ground = attacked_tile->get_items();
    
    while (!inv->empty())
    {
      ItemPtr current_item = inv->at(0);
      inv->remove(current_item->get_id());
      ground->add_front(current_item);
    }

    // Potentially generate a corpse as well.
    if (RNG::percent_chance(PCT_CHANCE_CORPSE))
    {
      ItemPtr corpse = CorpseFactory::create_corpse(dead_creature);
      if (corpse != nullptr)
      {
        ground->add_front(corpse);
      }
    }
  }
}

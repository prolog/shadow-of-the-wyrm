#include "CombatTextKeys.hpp"
#include "CreatureDeathManager.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

using std::string;

CreatureDeathManager::CreatureDeathManager(CreaturePtr attacked_creature, MapPtr current_map)
: DeathManager(attacked_creature, current_map)
{
}

CreatureDeathManager::~CreatureDeathManager()
{
}

void CreatureDeathManager::die()
{
  Game& game = Game::instance();
  
  if (map && creature)
  {
    // Remove the creature from the tile.
    TilePtr attacked_tile = MapUtils::get_tile_for_creature(map, creature);
    MapUtils::remove_creature(map, creature);

    // Remove all equipment.
    for (int worn_slot = EQUIPMENT_WORN_HEAD; worn_slot < EQUIPMENT_WORN_LAST; worn_slot++)
    {
      game.actions.remove_item(creature, static_cast<EquipmentWornLocation>(worn_slot));
    }

    // Drop inventory on to the creature's tile.
    Inventory inv = creature->get_inventory();
    Inventory& ground = attacked_tile->get_items();
    
    while (!inv.empty())
    {
      ItemPtr current_item = inv.at(0);
      inv.remove(current_item->get_id());
      ground.add_front(current_item);
    }

    IMessageManager& manager = MessageManagerFactory::instance(creature);
    string death_message = CombatTextKeys::get_monster_death_message(StringTable::get(creature->get_description_sid()));
    manager.add_new_message(death_message);      
  }
}

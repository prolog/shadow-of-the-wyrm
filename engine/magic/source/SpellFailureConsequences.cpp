#include <boost/foreach.hpp>
#include "CombatManager.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "RNG.hpp"
#include "SpellFailureConsequences.hpp"

using namespace std;

// The spellbook erupts in flames, dealing some amount of damage to the
// caster, and destroying the spellbook.
bool SpellFailureConsequences::damage_caster(CreaturePtr caster)
{
  bool spellbook_destroyed = false;

  float damage_pct = get_damage_pct();
  uint damage_in_hp = static_cast<uint>(caster->get_hit_points().get_current() * damage_pct);
  string spellbook_message_sid = get_damage_message_sid();

  // Marginal spell failures do nothing, so check to see if the creature's
  // actually been damaged.
  if (damage_in_hp > 0)
  {
    CombatManager cm;
    CreaturePtr no_attacker;
    cm.deal_damage(no_attacker, caster, damage_in_hp, spellbook_message_sid);

    spellbook_destroyed = true;
  }

  return spellbook_destroyed;
}

bool SpellFailureConsequences::inflict_status_ailments(CreaturePtr caster)
{
  return false;
}

bool SpellFailureConsequences::summon_creatures(CreaturePtr caster)
{
  pair<Dice, vector<string>> summoned_creature_details = get_summoned_creature_details();
  Dice num_creatures = summoned_creature_details.first;
  vector<string> possible_creatures = summoned_creature_details.second;
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  MapPtr map = caster->get_decision_strategy()->get_fov_map();
  TilesContainer tiles = map->get_tiles();

  vector<pair<string, TilePtr>> free_tiles;

  // Make a list of the free tiles surrounding the caster.  These will
  // be available for randomly placing the summoned creatures, as long
  // as the tiles can support the creature.
  BOOST_FOREACH(TilesContainer::value_type& fov_map_tile, tiles)
  {
    TilePtr tile = fov_map_tile.second;
    if (tile && !tile->get_is_blocking())
    {
      free_tiles.push_back(fov_map_tile);
    }
  }

  // Roll the num_creatures dice to get the number of creatures to
  // place.
  int n_creatures = RNG::dice(num_creatures);
  int cur_creatures_placed = 0;
  
  // Place n summoned creatures on the free tiles surrounding the
  // caster.  Stop if there are no more free tiles available.
  size_t pcreatures_size = possible_creatures.size();

  bool creatures_summoned = false;

  if (pcreatures_size > 0)
  {
    while ((cur_creatures_placed < n_creatures) && (!free_tiles.empty()))
    {
      // Select a tile at random
      int tile_idx = RNG::range(0, free_tiles.size() - 1);
      string creature_id = possible_creatures.at(RNG::range(0, pcreatures_size-1));

      // Create a creature to place.
      CreaturePtr summoned_creature = CreatureFactory::create_by_creature_id(game.get_action_manager_ref(), creature_id);

      // Place the creature on the tile
      pair<string, TilePtr> fov_tile = free_tiles.at(tile_idx);
      Coordinate coords = MapUtils::convert_map_key_to_coordinate(fov_tile.first);
      TilePtr tile = fov_tile.second;

      // Add the newly-summoned creature to the map, adding it as well to the
      // action coordinator if necessary.
      GameUtils::add_new_creature_to_map(game, summoned_creature, current_map, coords);
      
      // Remove the tile from the list of free tiles, and increment the number
      // of summoned creatures.
      free_tiles.erase(free_tiles.begin()+tile_idx);
      cur_creatures_placed++;
      if (creatures_summoned == false)
      {
        creatures_summoned = true;
      }
    }

    // Add an appropriate message.
    MessageManager& manager = MessageManager::instance();
    manager.add_new_message(StringTable::get(get_summoned_creatures_message_sid()));
    manager.send();
  }

  return false;
}


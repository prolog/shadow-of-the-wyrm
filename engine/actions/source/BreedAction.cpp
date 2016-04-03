#include "global_prototypes.hpp"
#include "BreedAction.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

BreedAction::BreedAction()
{
}

ActionCostValue BreedAction::breed(CreaturePtr creature, MapPtr map) const
{
  Game& game = Game::instance();

  if (creature != nullptr && map != nullptr)
  {
    string regen_rate_s = map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE);

    if (regen_rate_s.empty() || !fequal(String::to_float(regen_rate_s), 0.0f))
    {
      Coordinate creature_coords = map->get_location(creature->get_id());
      vector<Coordinate> coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coords.first, creature_coords.second);
      std::shuffle(coords.begin(), coords.end(), RNG::get_engine());

      if (creature != nullptr)
      {
        for (const Coordinate& c : coords)
        {
          TilePtr tile = map->at(c);

          if (tile && tile->has_creature() == false)
          {
            // Breed into the tile.
            string original_id = creature->get_original_id();
            CreatureFactory cf;

            CreaturePtr spawn = cf.create_by_creature_id(game.get_action_manager_ref(), original_id);
            GameUtils::add_new_creature_to_map(game, spawn, map, c);

            // Breeding is silent - the player gets no notification, so the message
            // manager is not needed.
            break;
          }
        }
      }
    }
  }

  return get_action_cost_value(creature);
}

ActionCostValue BreedAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

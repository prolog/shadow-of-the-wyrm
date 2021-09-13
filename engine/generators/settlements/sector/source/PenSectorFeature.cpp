#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "CreatureFeatures.hpp"
#include "DirectionUtils.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "PenSectorFeature.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"

using namespace std;

bool PenSectorFeature::generate_feature(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    generated = generate_pen(map, st_coord, end_coord);
    generated = generated && add_sheep_to_pen(map, st_coord, end_coord);
  }

  return generated;
}

bool PenSectorFeature::generate_pen(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Coordinate> fence_coords = CoordUtils::get_perimeter_coordinates(st_coord, end_coord);

    if (!fence_coords.empty())
    {
      for (const Coordinate& c : fence_coords)
      {
        FeaturePtr fence = FeatureGenerator::generate_fence();
        TilePtr tile = map->at(c);

        if (tile != nullptr && !tile->has_feature())
        {
          tile->get_items()->clear();
          tile->set_feature(fence);
        }
      }

      vector<CardinalDirection> gate_dirs = MapUtils::get_unblocked_door_dirs(map, st_coord, end_coord);

      if (!gate_dirs.empty())
      {
        Coordinate gate_coord = SettlementGeneratorUtils::get_door_location(st_coord.first, end_coord.first, st_coord.second, end_coord.second, DirectionUtils::get_random_cardinal_direction(gate_dirs));
        TilePtr tile = map->at(gate_coord);

        if (tile != nullptr)
        {
          FeaturePtr gate = FeatureGenerator::generate_gate();
          gate->set_material_type(MaterialType::MATERIAL_TYPE_WOOD);

          tile->set_feature(gate);
          tile->get_items()->clear();
        }
      }
    }

    generated = true;
  }
  
  return generated;
}

bool PenSectorFeature::add_sheep_to_pen(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Coordinate> interior = CoordUtils::get_interior_coordinates(st_coord, end_coord);
    std::shuffle(interior.begin(), interior.end(), RNG::get_engine());

    int num_sheep = RNG::range(1, std::max<int>(1, interior.size() / 3));
    int num_attempts = num_sheep * 2;
    Game& game = Game::instance();
    HostilityManager hm;

    for (int i = 0; i < num_attempts; i++)
    {
      if (interior.empty() || (i == num_sheep))
      {
        break;
      }

      Coordinate c = interior.back();
      interior.pop_back();

      CreatureFactory cf;
      CreaturePtr sheep = cf.create_by_creature_id(game.get_action_manager_ref(), CreatureID::CREATURE_ID_SHEEP, map);
      hm.clear_hostility(sheep);

      GameUtils::add_new_creature_to_map(game, sheep, map, c);
    }

    generated = true;
  }

  return generated;
}
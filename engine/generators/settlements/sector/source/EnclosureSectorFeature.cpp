#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "CreatureFeatures.hpp"
#include "DirectionUtils.hpp"
#include "EnclosureSectorFeature.hpp"
#include "FeatureGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TileGenerator.hpp"

using namespace std;

EnclosureSectorFeature::EnclosureSectorFeature(const EnclosureContentsType new_contents)
: pen_contents(new_contents)
{
}

bool EnclosureSectorFeature::generate_feature(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    EntranceStateType gate_state = EntranceStateType::ENTRANCE_TYPE_CLOSED;

    if (pen_contents == EnclosureContentsType::ENCLOSURE_CONTENTS_WEEDS)
    {
      gate_state = EntranceStateType::ENTRANCE_TYPE_OPEN;
    }

    generated = generate_enclosure(map, st_coord, end_coord, gate_state);

    switch (pen_contents)
    {
      case EnclosureContentsType::ENCLOSURE_CONTENTS_ANIMALS:
        generated = generated && add_animals(map, st_coord, end_coord);
        break;
      case EnclosureContentsType::ENCLOSURE_CONTENTS_VEGETABLES:
        generated = generated && add_vegetables(map, st_coord, end_coord);
        break;
      case EnclosureContentsType::ENCLOSURE_CONTENTS_WEEDS:
        generated = generated && add_weeds(map, st_coord, end_coord);
        break;
      case EnclosureContentsType::ENCLOSURE_CONTENTS_NONE:
      default:
        break;
    }
  }

  return generated;
}

bool EnclosureSectorFeature::generate_enclosure(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord, const EntranceStateType est)
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
          FeaturePtr gate = FeatureGenerator::generate_gate(est);
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

bool EnclosureSectorFeature::add_animals(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Coordinate> interior = CoordUtils::get_interior_coordinates(st_coord, end_coord);
    std::shuffle(interior.begin(), interior.end(), RNG::get_engine());
    vector<string> creature_ids = { CreatureID::CREATURE_ID_SHEEP, CreatureID::CREATURE_ID_CHICKEN };
    string creature_id = creature_ids[RNG::range(0, creature_ids.size() - 1)];
    int num_animals = RNG::range(1, std::max<int>(1, interior.size() / 3));
    int num_attempts = num_animals * 2;
    Game& game = Game::instance();
    HostilityManager hm;

    for (int i = 0; i < num_attempts; i++)
    {
      if (interior.empty() || (i == num_animals))
      {
        break;
      }

      Coordinate c = interior.back();
      interior.pop_back();

      CreatureFactory cf;
      CreaturePtr animal = cf.create_by_creature_id(game.get_action_manager_ref(), creature_id, map);

      if (animal != nullptr)
      {
        hm.clear_hostility(animal);
        GameUtils::add_new_creature_to_map(game, animal, map, c);
      }
    }

    generated = true;
  }

  return generated;
}

bool EnclosureSectorFeature::add_vegetables(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  Coordinate st_new = { st_coord.first + 1, st_coord.second + 1 };
  Coordinate end_new = { end_coord.first - 1, end_coord.second - 1 };
  FruitVegetableGardenGenerator fvgg(FruitVegetableGardenType::FVG_TYPE_VEGETABLE, "", AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, 1, 1, false);
  bool result = fvgg.generate(map, st_new, end_new);

  if (RNG::percent_chance(75))
  {
    vector<Coordinate> inner_coords = CoordUtils::get_coordinates_in_range(st_new, end_new);

    if (!inner_coords.empty())
    {
      ItemPtr shovel = ItemManager::create_item(ItemIdKeys::ITEM_ID_SHOVEL);
      MapUtils::add_item(map, inner_coords, shovel);
    }
  }

  return result;
}

bool EnclosureSectorFeature::add_weeds(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool weeds_added = false;

  if (map != nullptr)
  {
    vector<Coordinate> weed_coords = CoordUtils::get_coordinates_in_range({ st_coord.first + 1, st_coord.second + 1 }, { end_coord.first - 1, end_coord.second - 1 });

    if (!weed_coords.empty())
    {
      TileGenerator tg;
      TilePtr w_tile;

      for (const Coordinate& wc : weed_coords)
      {
        TilePtr tile = map->at(wc);

        if (tile != nullptr && tile->get_tile_type() == TileType::TILE_TYPE_FIELD)
        {
          w_tile = tg.generate(TileType::TILE_TYPE_WEEDS);
          w_tile->transform_from(tile);

          map->insert(wc, w_tile);
        }
      }

      weeds_added = true;
    }
  }

  return weeds_added;
}

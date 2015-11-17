#include "AgeTimeObserver.hpp"
#include "TileTransformObserver.hpp"
#include "Game.hpp"
#include "TileGenerator.hpp"

using namespace std;

void TileTransformObserver::notify(const ulonglong minutes_passed)
{
  double cur_seconds = 0;
  Game& game = Game::instance();
  WorldPtr world = game.get_current_world();

  if (world != nullptr)
  {
    cur_seconds = world->get_calendar().get_seconds();
    MapRegistry& mr = game.get_map_registry_ref();

    MapRegistryMap& maps = mr.get_maps_ref();

    for (auto& m_pair : maps)
    {
      MapPtr cur_map = m_pair.second;

      if (cur_map != nullptr)
      {
        process_tile_transforms(cur_map, cur_seconds);
      }
    }
  }
}


// Iterate over the tile transforms for this map, and if any have passed
// the minimum required time, do the transformation.
void TileTransformObserver::process_tile_transforms(MapPtr cur_map, const double cur_seconds)
{
  if (cur_map != nullptr)
  {
    TileTransformContainer& ttc = cur_map->get_tile_transforms_ref();

    for (auto t_it = ttc.begin(); t_it != ttc.end(); )
    {
      double seconds = t_it->first;

      if (cur_seconds < seconds)
      {
        break;
      }
      else
      {
        vector<TileTransform> tt_vec = t_it->second;

        for (const TileTransform tt : tt_vec)
        {
          Coordinate c = tt.get_coordinate();

          TileGenerator tg;
          TilePtr new_tile = tg.generate(tt.get_tile_type(), tt.get_tile_subtype());

          // Copy over features and items.
          new_tile->transform_from(cur_map->at(c));

          map<string, string> tt_props = tt.get_properties();
          for (const auto& p_pair : tt_props)
          {
            new_tile->set_additional_property(p_pair.first, p_pair.second);
          }

          cur_map->insert(c, new_tile);
        }

        ttc.erase(t_it++);
      }
    }
  }
}

ITimeObserver* TileTransformObserver::clone() 
{
  return new TileTransformObserver(*this);
}

ClassIdentifier TileTransformObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TILE_TRANSFORM_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileTransformObserver_test.cpp"
#endif


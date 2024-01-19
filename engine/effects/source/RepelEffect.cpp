#include "BresenhamLine.hpp"
#include "CoordUtils.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "RepelEffect.hpp"

using namespace std;

const int RepelEffect::DISTANCE_BLESSED = 5;
const int RepelEffect::DISTANCE_UNCURSED = 4;
const int RepelEffect::DISTANCE_CURSED = 3;

string RepelEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string message;
  
  if (creature != nullptr)
  {
    message = EffectTextKeys::get_repel_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return message;
}

Effect* RepelEffect::clone()
{
  return new RepelEffect(*this);
}

bool RepelEffect::repel(CreaturePtr creature, const Coordinate& affected_coordinate, const int distance)
{
  bool effect = false;

  if (creature != nullptr)
  {
    // Get the creatures immediately adjacent.
    MapPtr current_map = Game::instance().get_current_map();
    CreatureDirectionMap cdm = MapUtils::get_adjacent_creatures(current_map, creature);

    if (current_map != nullptr)
    {
      for (const auto& cdm_pair : cdm)
      {
        BresenhamLine bl;

        Coordinate adj_cc = CoordUtils::get_new_coordinate(affected_coordinate, cdm_pair.first);
        CreaturePtr adj_creature = cdm_pair.second;
        Coordinate new_coord = CoordUtils::get_new_coordinate(adj_cc, cdm_pair.first, distance);
        vector<Coordinate> line_points = bl.get_points_in_line(adj_cc.first, adj_cc.second, new_coord.first, new_coord.second);

        Coordinate repel_loc = adj_cc;
        TilePtr original_tile = current_map->at(adj_cc);

        for (const Coordinate& c : line_points)
        {
          if (c == adj_cc)
          {
            continue;
          }

          TilePtr tile = current_map->at(c);

          if (MapUtils::is_tile_available_for_creature(adj_creature, tile))
          {
            repel_loc = c;
          }
          else
          {
            // Something's blocking the way, or we can't move there for other
            // reasons (solid rock and not incorporeal, etc), exit with the
            // previously available location.
            break;
          }
        }

        if (repel_loc != adj_cc)
        {
          MapUtils::add_or_update_location(current_map, adj_creature, repel_loc, original_tile);
        }
      }
    }

    effect = true;
    Game::instance().get_sound(creature)->play(SoundEffectID::MAP_EFFECT);
  }

  return effect;
}

bool RepelEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return repel(creature, affected_coordinate, DISTANCE_BLESSED);
}

bool RepelEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return repel(creature, affected_coordinate, DISTANCE_UNCURSED);
}

bool RepelEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return repel(creature, affected_coordinate, DISTANCE_CURSED);
}


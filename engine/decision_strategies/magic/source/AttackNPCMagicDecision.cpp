#include "AttackNPCMagicDecision.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionUtils.hpp"
#include "Game.hpp"
#include "SpellShapeProcessorFactory.hpp"

using namespace std;

pair<bool, Direction> AttackNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& creature_threats) const
{
  pair<bool, Direction> decision_details(false, Direction::DIRECTION_NULL);
  int threat_level_count = 0;
  int nonthreat_level_count = 0;
  string leader_id = caster->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID);
  MapPtr current_map = Game::instance().get_current_map();

  CurrentCreatureAbilities cca;
  if (!cca.can_see(caster))
  {
    return decision_details;
  }

  if (caster != nullptr && current_map != nullptr && view_map != nullptr)
  {
    SpellShape ss = spell.get_shape();
    Coordinate caster_loc = current_map->get_location(caster->get_id());

    // Given the caster location and the spell shape, are there any targets
    // in range?
    SpellShapeProcessorPtr ssp = SpellShapeProcessorFactory::create_processor(ss.get_spell_shape_type());

    if (ssp != nullptr)
    {
      set<Direction> possible_directions = DirectionUtils::get_all_directions_for_category(ss.get_direction_category());

      for (const auto& dir : possible_directions)
      {
        threat_level_count = 0;
        nonthreat_level_count = 0;

        // JCD FIXME: this is basically being used out of convenience.  There's
        // no need to also compute the animation.  So if this turns out to be
        // too expensive, refactor the code so that the animation is also not
        // computed.
        pair<vector<pair<Coordinate, TilePtr>>, Animation> tiles_anim = ssp->get_affected_tiles_and_animation_for_spell(current_map, caster_loc, dir, spell);

        for (const auto& t_pair : tiles_anim.first)
        {
          // Only consider creatures in the NPC's own view map.  That is, don't
          // let the NPC make decisions about things it can't see.
          TilePtr tile = t_pair.second;

          if (tile && tile->has_creature())
          {
            CreaturePtr creature = view_map->get_creature(tile->get_creature()->get_id());

            if (creature != nullptr)
            {
              string creature_id = creature->get_id();
              string caster_id = caster->get_id();

              // The caster shouldn't allow itself to be targetted by its own
              // attack spells.
              if (creature_id == caster_id)
              {
                decision_details.first = false;
                break;
              }
              else
              {
                // Prevent NPC spellcasting if it would target its leader.
                if (creature_id == leader_id)
                {
                  decision_details.first = false;
                  decision_details.second = Direction::DIRECTION_NULL;

                  return decision_details;
                }

                if (creature_threats.find(creature_id) != creature_threats.end())
                {
                  threat_level_count += creature->get_level().get_current();
                }
                else
                {
                  nonthreat_level_count += creature->get_level().get_current();
                }
              }
            }
          }
        }

        if (threat_level_count > nonthreat_level_count)
        {
          decision_details.first = true;
          decision_details.second = dir;

          break;
        }
      }
    }
  }

  return decision_details;
}

#include "AttackNPCMagicDecision.hpp"
#include "DirectionUtils.hpp"
#include "SpellShapeProcessorFactory.hpp"

using namespace std;

pair<bool, Direction> AttackNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& creature_threats) const
{
  if (caster != nullptr && view_map != nullptr)
  {
    SpellShape ss = spell.get_shape();
    Coordinate caster_loc = view_map->get_location(caster->get_id());

    // Given the caster location and the spell shape, are there any targets
    // in range?
    SpellShapeProcessorPtr ssp = SpellShapeProcessorFactory::create_processor(ss.get_spell_shape_type());

    if (ssp != nullptr)
    {
      set<Direction> possible_directions = DirectionUtils::get_all_directions_for_category(ss.get_direction_category());

      for (const auto& dir : possible_directions)
      {
        // JCD FIXME: this is basically being used out of convenience.  There's
        // no need to also compute the animation.  So if this turns out to be
        // too expensive, refactor the code so that the animation is also not
        // computed.
        pair<vector<TilePtr>, Animation> tiles_anim = ssp->get_affected_tiles_and_animation_for_spell(view_map, caster_loc, dir, spell);

        for (TilePtr tile : tiles_anim.first)
        {
          if (tile && tile->has_creature() && (creature_threats.find(tile->get_creature()->get_id()) != creature_threats.end()))
          {
            return make_pair(true, dir);
          }
        }
      }
    }
  }

  return make_pair(false, Direction::DIRECTION_NULL);
}

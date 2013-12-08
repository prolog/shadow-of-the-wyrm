#include "Game.hpp"
#include "SpellcastingProcessor.hpp"

using namespace std;

// Process the spell and the associated animation.  Return true if the spell
// was identified during casting.
bool SpellcastingProcessor::process(SpellShapeProcessorPtr spell_processor, CreaturePtr caster, MapPtr current_map, const Coordinate& caster_coord, const Direction spell_direction, const Spell& spell, const ItemStatus effect_status) const
{
  Game& game = Game::instance();

  // Get the affected tiles and the animation.
  pair<vector<TilePtr>, Animation> affected_tiles_and_animation = spell_processor->get_affected_tiles_and_animation_for_spell(current_map, caster_coord, spell_direction, spell);
  vector<TilePtr> affected_tiles = affected_tiles_and_animation.first;
  Animation spell_animation = affected_tiles_and_animation.second;
          
  // Draw the animation.
  game.get_display()->draw_animation(spell_animation);

  // Apply the damage, effects, etc, to the affected tiles.
  return spell_processor->process_damage_and_effect(caster, affected_tiles, spell, effect_status, &game.get_action_manager_ref());
}

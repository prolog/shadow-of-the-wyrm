#include "Game.hpp"
#include "SpellcastingProcessor.hpp"

using namespace std;

// Process the spell and the associated animation.  Return true if the spell
// was identified during casting.
bool SpellcastingProcessor::process(SpellShapeProcessor* spell_processor, CreaturePtr caster, MapPtr current_map, const Coordinate& caster_coord, const Direction spell_direction, const Spell& spell, const int bonus, const ItemStatus effect_status) const
{
  Game& game = Game::instance();
  CreaturePtr player = game.get_current_player();
  MapPtr player_fov_map = player->get_decision_strategy()->get_fov_map();

  // Get the affected coords/tiles and the animation.
  pair<vector<pair<Coordinate, TilePtr>>, Animation> affected_tiles_and_animation = spell_processor->get_affected_tiles_and_animation_for_spell(current_map, caster_coord, spell_direction, spell);
  vector<pair<Coordinate, TilePtr>> affected_coord_tiles = affected_tiles_and_animation.first;
  Animation spell_animation = affected_tiles_and_animation.second;
          
  // Draw the animation.
  game.get_display()->draw_animation(spell_animation, player_fov_map);

  // Apply the damage, effects, etc, to the affected tiles.
  return spell_processor->process_damage_and_effect(caster, affected_coord_tiles, spell, bonus, effect_status, &game.get_action_manager_ref());
}

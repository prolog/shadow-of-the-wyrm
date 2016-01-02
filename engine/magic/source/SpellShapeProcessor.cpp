#include "ActionManager.hpp"
#include "AnimationTranslator.hpp"
#include "CombatManager.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "DisplayTile.hpp"
#include "EffectFactory.hpp"
#include "SpellShapeProcessor.hpp"

using namespace std;

SpellShapeProcessor::~SpellShapeProcessor()
{
}

// Create the affected tiles and animation for the spell shape.
pair<vector<TilePtr>, Animation> SpellShapeProcessor::create_affected_tiles_and_animation(CreaturePtr caster, MapPtr map, const std::vector<TilePtr>& affected_tiles, const std::vector<std::pair<DisplayTile, std::vector<Coordinate>>>& movement_path)
{
  MapPtr fov_map = caster->get_decision_strategy()->get_fov_map();
  Game& game = Game::instance();
  AnimationTranslator at(game.get_display());
  CurrentCreatureAbilities cca;
  CreaturePtr player = game.get_current_player();

  Animation animation = at.create_movement_animation(!cca.can_see(player), game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, map, fov_map);
  pair<vector<TilePtr>, Animation> affected_tiles_and_animation(affected_tiles, animation);

  return affected_tiles_and_animation;
}

// Process the shape.  This is done by generating all the affected tiles,
// and then applying damage and spell effects to each.
bool SpellShapeProcessor::process_damage_and_effect(CreaturePtr caster, const vector<TilePtr>& affected_tiles, const Spell& spell, const ItemStatus effect_status, ActionManager * const am)
{
  // Apply the spell's damage/effect to the tiles in order.
  return apply_damage_and_effect(caster, affected_tiles, spell, effect_status, am);
}

// Apply a spell to a particular tile by applying its damage and spell effect.
bool SpellShapeProcessor::apply_damage_and_effect(CreaturePtr caster, const vector<TilePtr>& affected_tiles, const Spell& spell, const ItemStatus effect_status, ActionManager * const am)
{
  bool spell_identified = false;

  for (TilePtr tile : affected_tiles)
  {
    bool damage_identified = apply_damage(caster, tile, spell, am);
    bool effect_identified = apply_effect(caster, tile, spell, effect_status, am);

    if ((damage_identified || effect_identified) && !spell_identified)
    {
      spell_identified = true;
    }
  }

  return spell_identified;
}

// Apply a spell's damage to a particular tile.
bool SpellShapeProcessor::apply_damage(CreaturePtr caster, TilePtr tile, const Spell& spell, ActionManager * const am)
{
  // A spell can be identified if the creature can see its damage type.
  // So, evoking a wand of frost, for example, identifies it.  Evoking
  // a wand with no damage and a null effect would not.
  bool spell_identified = spell.get_has_damage();

  CreaturePtr tile_creature = tile->get_creature();
  if (tile && spell.get_has_damage() && tile_creature)
  {
    CombatManager cm;

    if (spell.get_allows_bonus())
    {
      cm.attack(caster, tile_creature, AttackType::ATTACK_TYPE_MAGICAL, true);
    }
    else
    {
      // If the spell doesn't allow a bonus, it's an adhoc spell not present
      // in the game's list, and so the magical damage calculator isn't
      // appropriate.  Pass the damage directly to the combat manager.
      DamagePtr dmg = std::make_shared<Damage>(spell.get_damage());
      cm.attack(caster, tile_creature, AttackType::ATTACK_TYPE_MAGICAL, false, dmg);
    }


    spell_identified = true;
  }

  return spell_identified;
}

// Apply a spell effect to a particular tile.
bool SpellShapeProcessor::apply_effect(CreaturePtr caster, TilePtr tile, const Spell& spell, const ItemStatus effect_status, ActionManager * const am)
{
  if (tile)
  {
    EffectType effect_type = spell.get_effect();

    EffectPtr effect = EffectFactory::create_effect(effect_type, spell.get_modifier(), spell.get_properties(), spell.get_spell_id());
    CreaturePtr creature = tile->get_creature();

    if (effect && creature)
    {
      bool negative_effect = effect->is_negative_effect();

      if (negative_effect)
      {
        HostilityManager hm;
        hm.set_hostility_to_creature(creature, caster->get_id());
      }

      bool show_msg_on_unid = (creature && caster && caster->get_is_player() && creature->get_is_player());
      return effect->effect(creature, am, effect_status, show_msg_on_unid);
    }
  }

  // Something went wrong; anyway, the spell can't be identified in this case.
  return false;
}

bool SpellShapeProcessor::is_coordinate_adjacent_to_coordinate_in_previous_frame(const Coordinate& c, const vector<Coordinate>& prev_frame)
{
  for (const Coordinate& prev_frame_coord : prev_frame)
  {
    if (CoordUtils::are_coordinates_adjacent(c, prev_frame_coord))
    {
      return true;
    }
  }

  return false;
}
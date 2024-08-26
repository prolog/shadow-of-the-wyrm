#include "TrapManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "AnimationTranslator.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DamageCalculatorFactory.hpp"
#include "DeathSourceTextKeys.hpp"
#include "EffectFactory.hpp"
#include "FeatureProperties.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PhaseOfMoonCalculator.hpp"
#include "ResistancesCalculator.hpp"
#include "RNG.hpp"

using namespace std;

TrapManipulator::TrapManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

void TrapManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_TRAP));
    manager.send();
  }
}

bool TrapManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  Game& game = Game::instance();
  FeaturePtr feature = tile->get_feature();
  TrapPtr trap = dynamic_pointer_cast<Trap>(feature);
  bool handled = false;

  // Traps can only be manipulated when the manipulating creature is standing
  // directly on the tile.
  if (tile != nullptr)
  {
    CreaturePtr tile_creature = tile->get_creature();

    if (tile_creature != nullptr && creature != nullptr && (tile_creature->get_id() == creature->get_id()))
    {
      if (trap && creature)
      {
        MapPtr current_map = game.get_current_map();
        Coordinate creature_coord = MapUtils::get_coordinate_for_creature(current_map, creature);

        trigger_trap(trap, creature);
        apply_effects_to_creature(trap, creature);
        create_item_if_necessary(tile, trap);

        // Pass the coordinate in now because the triggering of the trap
        // may have killed the creature...
        create_and_draw_animation(trap, creature, creature_coord);
        handled = true;
      }
    }
    else
    {
      if (creature && creature->get_is_player())
      {
        IMessageManager& manager = MM::instance();
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_APPLY_TRAP_TOO_FAR));
        manager.send();
      }
    }
  }

  return handled;
}

bool TrapManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

void TrapManipulator::trigger_trap(TrapPtr trap, CreaturePtr creature)
{
  string trigger_message = StringTable::get(trap->get_trigger_message_sid());
  Game& game = Game::instance();

  if (creature)
  {
    IMessageManager& manager = MM::instance();
    bool show_msg = GameUtils::is_creature_in_player_view_map(game, creature->get_id());

    if (show_msg)
    {
      manager.add_new_message(trigger_message);
      manager.send();
    }

    Game::instance().get_sound()->play(SoundEffectID::CLICK);
  }

  trap->set_triggered(true);
}

void TrapManipulator::apply_effects_to_creature(TrapPtr trap, CreaturePtr creature)
{
  string creature_id = creature ? creature->get_id() : "";
  Damage damage = trap->get_damage();
  DamageType dt = damage.get_damage_type();
  EffectType effect = trap->get_effect();
  int effect_bonus = damage.get_effect_bonus();
  StatusAilments status_ailments = damage.get_status_ailments();
  float soak_mult = 1.0f; // the creature's soak should use the standard multiplier.

  // Deal the damage to the creature:
  CombatManager cm;
  const AttackType attack_type = AttackType::ATTACK_TYPE_RANGED;
  bool slays_race = false;
  int dmg_roll = RNG::dice(damage);

  string message;
  if (creature && creature->get_is_player())
  {
    message = trap->get_player_damage_message_sid();
  }

  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  PhaseOfMoonCalculator pomc;
  PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());

  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type, phase);

  // Technically, traps are hidden, but I don't want to apply the 2x damage
  // multiplier.
  int damage_dealt = damage_calc->calculate(creature, false, slays_race, damage, dmg_roll, soak_mult);
  Damage damage_default;
  damage_default.set_modifier(damage_dealt);
  string source_id; // sprung traps don't give exp when they kill creatures.
  ItemStatus status = ItemStatus::ITEM_STATUS_UNCURSED;
  string trap_status_s = trap->get_additional_property(FeatureProperties::FEATURE_PROPERTIES_TRAP_EFFECT_STATUS);

  if (!trap_status_s.empty())
  {
    status = static_cast<ItemStatus>(String::to_int(trap_status_s));
  }

  // First apply the regular effect, assuming there is one.
  if (effect != EffectType::EFFECT_TYPE_NULL)
  {
    Modifier m;
    EffectPtr effectp = EffectFactory::create_effect(effect, m, trap->get_additional_properties(), "", creature_id);

    if (creature != nullptr)
    {
      pair<Coordinate, TilePtr> creature_loc = current_map->get_location_and_tile(creature->get_id());

      if (effectp != nullptr)
      {
        effectp->effect(creature, &game.get_action_manager_ref(), status, creature_loc.first, creature_loc.second);
      }
    }
  }

  // Only apply the damage-based effect if there is damage to be dealt.
  if (damage_dealt > 0)
  {
    string trap_sid = DeathSourceTextKeys::DEATH_SOURCE_TRAP;

    if (trap != nullptr)
    {
      trap_sid = trap->get_description_and_replacement_sids().first;
    }

    cm.handle_damage_effects(nullptr, creature, damage_dealt, dt, effect_bonus, status_ailments, 1);
    cm.deal_damage(nullptr, creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, source_id, damage_dealt, damage_default, message, trap_sid);
  }
}

void TrapManipulator::create_item_if_necessary(TilePtr tile, TrapPtr trap)
{
  // Generate an item, if applicable.
  ItemManager im;
  IInventoryPtr inv = tile->get_items();
  string trap_item_id = trap->get_item_id();

  if (!trap_item_id.empty())
  {
    const ItemMap items = Game::instance().get_items_ref();
    auto i_it = items.find(trap_item_id);

    if (i_it != items.end() && i_it->second != nullptr)
    {
      string item_destruction_s = i_it->second->get_additional_property(ItemProperties::ITEM_PROPERTIES_DESTRUCTION_PCT_CHANCE);
      int item_destruction_pct = item_destruction_s.empty() ? 0 : String::to_int(item_destruction_s);
      int upper_bound = 100 - item_destruction_pct;
      int lower_bound = upper_bound / 2;

      im.create_item_with_probability(lower_bound, upper_bound, inv, trap_item_id);
    }
  }
}

void TrapManipulator::create_and_draw_animation(TrapPtr trap, CreaturePtr creature, const Coordinate& creature_coord)
{
  if (CreatureUtils::is_player_or_in_los(creature))
  {
    // Create the animation
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    CreaturePtr player = game.get_current_player();
    MapPtr player_fov_map = player->get_decision_strategy()->get_fov_map();

    CurrentCreatureAbilities cca;
    AnimationTranslator at(game.get_display());
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
    Symbol s = trap->get_trigger_symbol();
    DisplayTile display_tile(s);
    MovementPath movement_path;

    movement_path.push_back({make_pair(display_tile, creature_coord)});
    bool player_blind = false;

    if (creature->get_is_player())
    {
      player_blind = !cca.can_see(creature);
    }

    Animation animation = at.create_movement_animation(creature, player_blind, game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, current_map, fov_map);

    // Draw the animation.
    DisplayPtr display = game.get_display();
    display->draw_animation(animation, player_fov_map);
  }
}

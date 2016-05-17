#include "TrapManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "AnimationTranslator.hpp"
#include "CombatManager.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DamageCalculatorFactory.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PhaseOfMoonCalculator.hpp"
#include "ResistancesCalculator.hpp"
#include "RNG.hpp"

using namespace std;

TrapManipulator::TrapManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void TrapManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_TRAP));
    manager.send();
  }
}

bool TrapManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  FeaturePtr feature = tile->get_feature();
  TrapPtr trap = dynamic_pointer_cast<Trap>(feature);

  // Traps can only be manipulated when the manipulating creature is standing
  // directly on the tile.
  if (tile != nullptr)
  {
    CreaturePtr tile_creature = tile->get_creature();

    if (tile_creature != nullptr && creature != nullptr && (tile_creature->get_id() == creature->get_id()))
    {
      if (trap && creature)
      {
        trigger_trap(trap, creature);
        apply_effects_to_creature(trap, creature);
        create_item_if_necessary(tile, trap);
        create_and_draw_animation(trap, creature);
      }
    }
    else
    {
      if (creature && creature->get_is_player())
      {
        IMessageManager& manager = MessageManagerFactory::instance();
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_APPLY_TRAP_TOO_FAR));
        manager.send();
      }
    }
  }

  return true;
}

void TrapManipulator::trigger_trap(TrapPtr trap, CreaturePtr creature)
{
  string trigger_message_sid = trap->get_trigger_message_sid();

  if (creature && creature->get_is_player())
  {
    // Traps only affect the creature on the exact tile (the creature passed
    // as an argument to this function).
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(trigger_message_sid));
    manager.send();
  }

  trap->set_triggered(true);
}

void TrapManipulator::apply_effects_to_creature(TrapPtr trap, CreaturePtr creature)
{
  Damage& damage = trap->get_damage();
  DamageType dt = damage.get_damage_type();
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
  PhaseOfMoonCalculator pomc;
  PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());

  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type, phase);
  int damage_dealt = damage_calc->calculate(creature, slays_race, damage, dmg_roll, soak_mult);

  // Only apply the effect if there is damage to be dealt.
  if (damage_dealt > 0)
  {
    cm.deal_damage(nullptr, creature, damage_dealt, message);
    cm.handle_damage_effects(creature, damage_dealt, dt, effect_bonus, status_ailments);
  }
}

void TrapManipulator::create_item_if_necessary(TilePtr tile, TrapPtr trap)
{
  // Generate an item, if applicable.
  ItemManager im;
  IInventoryPtr inv = tile->get_items();
  im.create_item_with_probability(50, 100, inv, trap->get_item_id());
}

void TrapManipulator::create_and_draw_animation(TrapPtr trap, CreaturePtr creature)
{
  if (CreatureUtils::is_player_or_in_los(creature))
  {
    // Create the animation
    Game& game = Game::instance();
    CurrentCreatureAbilities cca;
    AnimationTranslator at(game.get_display());
    MapPtr current_map = game.get_current_map();
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
    Coordinate creature_coord = MapUtils::get_coordinate_for_creature(current_map, creature);
    DisplayTile display_tile(trap->get_trigger_symbol(), static_cast<int>(trap->get_colour()));
    MovementPath movement_path;

    movement_path.push_back({make_pair(display_tile, creature_coord)});

    Animation animation = at.create_movement_animation(!cca.can_see(creature), game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, current_map, fov_map);

    // Draw the animation.
    DisplayPtr display = game.get_display();
    display->draw_animation(animation);

  }
}

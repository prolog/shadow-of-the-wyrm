#include "TrapManipulator.hpp"
#include "CombatManager.hpp"
#include "DamageCalculatorFactory.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"
#include "ResistancesCalculator.hpp"
#include "RNG.hpp"
#include "Trap.hpp"

using namespace std;

TrapManipulator::TrapManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void TrapManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  // JCD FIXME add a message about "narrowly avoiding setting off the trap"...
}

bool TrapManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  FeaturePtr feature = tile->get_feature();
  TrapPtr trap = dynamic_pointer_cast<Trap>(feature);

  if (trap && creature)
  {
    string trigger_message_sid = trap->get_trigger_message_sid();

    // Traps only affect the creature on the exact tile (the creature passed
    // as an argument to this function).
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(trigger_message_sid));
    manager.send();

    trap->set_triggered(true);

    Damage& damage = trap->get_damage();
    DamageType dt = damage.get_damage_type();
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

    DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type);
    int damage_dealt = damage_calc->calculate(creature, slays_race, damage, dmg_roll, soak_mult);

    if (damage_dealt > 0)
    { 
      cm.deal_damage(nullptr, creature, damage_dealt, message);
    }

    // Generate an item, if applicable.
    ItemManager im;
    IInventoryPtr inv = tile->get_items();
    im.create_item_with_probability(50, 100, inv, trap->get_item_id());
  }

  return true;
}


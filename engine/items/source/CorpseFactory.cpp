#include "ClassManager.hpp"
#include "Consumable.hpp"
#include "ConsumableConstants.hpp"
#include "CorpseFactory.hpp"
#include "ItemManager.hpp"
#include "RaceManager.hpp"
#include "ResistancesCalculator.hpp"

using namespace std;

map<CreatureSize, float> CorpseFactory::size_weight_multipliers;

CorpseFactory::CorpseFactory()
{
  initialize_size_weight_multipliers();
}

CorpseFactory::~CorpseFactory()
{
}

void CorpseFactory::initialize_size_weight_multipliers()
{
  size_weight_multipliers = map<CreatureSize, float>
                            {{CREATURE_SIZE_TINY, 0.05f},
                             {CREATURE_SIZE_SMALL, 0.4f},
                             {CREATURE_SIZE_MEDIUM, 1.0f},
                             {CREATURE_SIZE_LARGE, 4.0f},
                             {CREATURE_SIZE_HUGE, 10.0f},
                             {CREATURE_SIZE_BEHEMOTH, 100.0f}};
}

// Creates a corpse.  Checks:
// - Is creature currently not incorporeal?
// - Is the creature's race considered corporeal?
ItemPtr CorpseFactory::create_corpse(CreaturePtr creature)
{
  ItemPtr corpse;

  if (creature)
  {
    if (!creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
    {
      RaceManager rm;

      RacePtr race = rm.get_race(creature->get_race_id());

      if (race && race->get_corporeal().get_current())
      {
        // All the conditions to create a corpse have been met - create the
        // corpse, setting the appropriate values so that it will be
        // recognized as a goblin corpse, a harpy corpse, etc.

        // Create the base corpse
        corpse = ItemManager::create_item("_corpse");

        if (corpse)
        {
          // Set whatever internal flags are necessary for things like
          // checking cannibalism, etc.
          set_internal_details(creature, corpse);

          // Set various aspects of the display detail - name of the creature
          // being corpseified, colour of the corpse, etc.
          set_display_details(creature, corpse);

          // If the creature's damage contains any poison component, the corpse
          // should be poisoned as well.
          set_poisoned_if_necessary(creature, corpse);

          // Adjust the weight of the corpse based on the size of the creature.
          set_weight(creature, corpse);

          // If the creature has any resistances, transfer these to the corpse
          // so that these can be used later: for increasing the eater's
          // resistances, or adding the resistances to a skin, etc.
          set_resistances(creature, corpse);
        }
      }
    }
  }

  return corpse;
}

void CorpseFactory::set_internal_details(CreaturePtr creature, ItemPtr corpse)
{
  if (creature && corpse)
  {
    // Set the corpse's race ID so that cannibalism can be punished when
    // necessary.
    corpse->set_additional_property(ConsumableConstants::CORPSE_RACE_ID, creature->get_race_id());
  }
}

void CorpseFactory::set_display_details(CreaturePtr creature, ItemPtr corpse)
{
  if (corpse)
  {
    // The corpse's colour should be that of the creature's.
    corpse->set_colour(creature->get_colour());

    // Set the description SID, which will be used by the appropriate
    // item describer to print something like "a chimera corpse".
    corpse->set_additional_property(ConsumableConstants::CORPSE_DESCRIPTION_SID, creature->get_description_sid());
	corpse->set_additional_property(ConsumableConstants::CORPSE_SHORT_DESCRIPTION_SID, creature->get_short_description_sid());
  }
}

void CorpseFactory::set_poisoned_if_necessary(CreaturePtr creature, ItemPtr corpse)
{
  if (creature->get_base_damage().contains(DAMAGE_TYPE_POISON))
  {
    ConsumablePtr c_corpse = dynamic_pointer_cast<Consumable>(corpse);

    if (c_corpse)
    {
      c_corpse->set_poisoned(true);
    }
  }
}

void CorpseFactory::set_weight(CreaturePtr creature, ItemPtr corpse)
{
  if (creature && corpse)
  {
    CreatureSize size = creature->get_size();
    float weight_multiplier = size_weight_multipliers[size];
    Weight weight = corpse->get_weight();
    uint weight_oz = static_cast<uint>(weight.get_weight() * weight_multiplier);
    weight.set_weight(weight_oz);

    corpse->set_weight(weight);
  }
}

void CorpseFactory::set_resistances(CreaturePtr creature, ItemPtr corpse)
{
  if (creature && corpse)
  {
    RaceManager rm;
    ClassManager cm;

    Resistances& corpse_resists  = corpse->get_resistances_ref();

    // Ensure that we don't consider equipment resistances when creating the
    // corpse - don't factor in equipment.
    ResistancesCalculator rc;
    Resistances creature_resists = rc.calculate_non_equipment_resistances(creature, rm.get_race(creature->get_race_id()), cm.get_class(creature->get_class_id()));

    // Only copy in resistances - never vulnerabilities.
    for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
    {
      double cur_val = creature_resists.get_resistance_value(dt);

      if (cur_val > 0)
      {
        corpse_resists.set_resistance_value(dt, cur_val);
      }
    }
  }
}
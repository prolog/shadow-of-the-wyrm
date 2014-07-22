#include "ConsumableConstants.hpp"
#include "CorpseFactory.hpp"
#include "ItemManager.hpp"
#include "RaceManager.hpp"

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
          // Adjust the weight of the corpse based on the size of the creature.
          CreatureSize size = creature->get_size();
          float weight_multiplier = size_weight_multipliers[size];
          Weight weight = corpse->get_weight();
          uint weight_oz = static_cast<uint>(weight.get_weight() * weight_multiplier);
          weight.set_weight(weight_oz);

          corpse->set_weight(weight);

          // Set the description SID, which will be used by the appropriate
          // item describer to print something like "a chimera corpse".
          corpse->set_additional_property(ConsumableConstants::CORPSE_DESCRIPTION_SID, creature->get_description_sid());
        }
      }
    }
  }

  return corpse;
}


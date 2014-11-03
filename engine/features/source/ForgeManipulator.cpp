#include "ForgeManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "WeaponManager.hpp"

using namespace std;

ForgeManipulator::ForgeManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void ForgeManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  // JCD FIXME
}

bool ForgeManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (feature != nullptr)
  {
    // Is the creature wielding something suitably hammer-y?
    WeaponManager wm;
    WeaponPtr weapon1 = wm.get_weapon(creature, ATTACK_TYPE_MELEE_PRIMARY);
    WeaponPtr weapon2 = wm.get_weapon(creature, ATTACK_TYPE_MELEE_SECONDARY);

    // Does the creature know anything about smithing?
    SkillPtr smithing_skill;
    if (creature && (smithing_skill = creature->get_skills().get_skill(SKILL_GENERAL_SMITHING)) != nullptr)
    {
      if (smithing_skill->get_value() <= 0)
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_NO_SMITHING_SKILL));
        manager.send();

        return false;
      }
    }

    // Either weapon a club/hammer?
    if (!((weapon1 && weapon1->get_trained_skill() == SKILL_MELEE_BLUDGEONS) ||
        (weapon2 && weapon2->get_trained_skill() == SKILL_MELEE_BLUDGEONS)))
    {
      // Inform the creature of the lack of suitable hammer.
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FORGE_NO_SUITABLE_HAMMER));
      manager.send();

      return false;
    }
  }

  // The creature's got some skill in smithing, is wielding the appropriate
  // weapon, and has something to smith with.

  return true;
}



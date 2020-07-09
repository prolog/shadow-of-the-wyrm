#include "ActionTextKeys.hpp"
#include "BeastmasterySkillProcessor.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceManager.hpp"

using namespace std;

ActionCostValue BeastmasterySkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::DEFAULT;

  if (creature != nullptr)
  {
    CurrentCreatureAbilities cca;
    if (cca.can_act(creature, true) && cca.can_focus(creature, true) && cca.can_see(creature, true))
    {
      MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
      CreatureMap fov_creatures = fov_map->get_creatures();
      CreatureMap tameable_fov = get_tameable_creatures(fov_creatures);
      
      tame_creatures(creature, tameable_fov);
    }
  }

  return acv;
}

CreatureMap BeastmasterySkillProcessor::get_tameable_creatures(const CreatureMap& fov_creatures)
{
  RaceManager rm;
  CreatureMap tameable_fov;

  // Creatures are tameable if their race indicates that they are, and if the
  // particular creature hasn't been tamed before.
  for (auto fc_pair : fov_creatures)
  {
    CreaturePtr c = fc_pair.second;

    if (c != nullptr && !String::to_bool(c->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_TAMED)))
    {
      Race* race = rm.get_race(fc_pair.second->get_race_id());

      if (race && race->get_tameable())
      {
        tameable_fov.insert(fc_pair);
      }
    }
  }

  return tameable_fov;
}

void BeastmasterySkillProcessor::tame_creatures(CreaturePtr taming_creature, const CreatureMap& tameable_fov)
{
  if (taming_creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, taming_creature, taming_creature->get_is_player());
    SkillType bm_sk = SkillType::SKILL_GENERAL_BEASTMASTERY;

    if (tameable_fov.empty())
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_TAME_NO_TARGETS));
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_TAME_BEGIN));

      // For each tameable FOV creature, try to tame it...
      for (auto t_pair : tameable_fov)
      {
        // Is the creature tamed?
        // Mark Beastmastery if successful.

        // At the end of the process, regardless of success, mark Beastmastery
        // once more.
        taming_creature->get_skills().mark(bm_sk);
      }
    }

    manager.send();
  }
}

SkillProcessorPtr BeastmasterySkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<BeastmasterySkillProcessor>();
  return proc;
}

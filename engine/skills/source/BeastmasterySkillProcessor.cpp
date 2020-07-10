#include "ActionTextKeys.hpp"
#include "BeastmasteryCalculator.hpp"
#include "BeastmasterySkillProcessor.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "EffectFactory.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"

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
    BeastmasteryCalculator bc;
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();
    MapPtr map = game.get_current_map();

    if (tameable_fov.empty())
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_TAME_NO_TARGETS));
    }
    else if (map != nullptr)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_TAME_BEGIN));

      // For each tameable FOV creature, try to tame it...
      for (auto t_pair : tameable_fov)
      {
        CreaturePtr to_tame = t_pair.second;

        // Is the creature tamed?
        // Mark Beastmastery if successful.
        if (RNG::percent_chance(bc.calculate_pct_chance_tame(taming_creature, to_tame)))
        {
          handle_tame(taming_creature, to_tame, manager);
        }
        // If unsuccessful, the creature becomes enraged
        else
        {
          handle_anger(taming_creature, t_pair, map, manager);
        }
      }

      // At the end of the process, regardless of success, mark Beastmastery
      // once more.
      taming_creature->get_skills().mark(bm_sk);
    }

    manager.send();
  }
}

void BeastmasterySkillProcessor::handle_tame(CreaturePtr taming_creature, CreaturePtr to_tame, IMessageManager& manager)
{
  if (taming_creature != nullptr && to_tame != nullptr)
  {
    HostilityManager hm;

    hm.remove_hostility_to_creature(to_tame, taming_creature->get_id());
    
    to_tame->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_NO_EXP, to_string(true));
    to_tame->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_TAMED, to_string(true));

    taming_creature->get_skills().mark(SkillType::SKILL_GENERAL_BEASTMASTERY);
    manager.add_new_message(ActionTextKeys::get_tamed_message(taming_creature->get_description_sid(), to_tame->get_description_sid(), taming_creature->get_is_player()));

    ExperienceManager em;
    BeastmasteryCalculator bc;
    
    double proportion = bc.calculate_exp_proportion(taming_creature);
    uint tamed_xp = to_tame->get_experience_value() * proportion;
    tamed_xp = std::max<uint>(tamed_xp, 1);

    em.gain_experience(taming_creature, tamed_xp);
  }
}

void BeastmasterySkillProcessor::handle_anger(CreaturePtr taming_creature, const pair<string, CreaturePtr>& t_pair, MapPtr map, IMessageManager& manager)
{
  CreaturePtr to_tame = t_pair.second;

  if (taming_creature != nullptr && to_tame != nullptr)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();

    Coordinate cc = map->get_location(t_pair.first);
    TilePtr ct = map->at(cc);
    EffectPtr effect = EffectFactory::create_effect(EffectType::EFFECT_TYPE_RAGE, {}, {}, "", "");

    if (effect != nullptr)
    {
      HostilityManager hm;
      hm.set_hostility_to_creature(to_tame, taming_creature->get_id());
      effect->effect(to_tame, &am, ItemStatus::ITEM_STATUS_UNCURSED, cc, ct);
      manager.add_new_message(ActionTextKeys::get_tame_failure_message(to_tame->get_description_sid()));
    }
  }
}
SkillProcessorPtr BeastmasterySkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<BeastmasterySkillProcessor>();
  return proc;
}

#include "ActionTextKeys.hpp"
#include "BeastmasterySkillProcessor.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "EffectFactory.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "MessageManagerFactory.hpp"
#include "PacificationCalculator.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "TameScript.hpp"

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
    PacificationCalculator pc;
    Game& game = Game::instance();
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
        if (RNG::percent_chance(pc.calculate_pct_chance_tame_beastmastery(taming_creature, to_tame)))
        {
          handle_tame(taming_creature, to_tame, map, manager);
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

void BeastmasterySkillProcessor::handle_tame(CreaturePtr taming_creature, CreaturePtr to_tame, MapPtr current_map, IMessageManager& manager)
{
  if (taming_creature != nullptr && to_tame != nullptr)
  {
    HostilityManager hm;

    hm.remove_hostility_to_creature(to_tame, taming_creature->get_id());
    
    to_tame->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_NO_EXP, to_string(true));
    to_tame->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_TAMED, to_string(true));
    to_tame->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID, taming_creature->get_id());

    taming_creature->get_skills().mark(SkillType::SKILL_GENERAL_BEASTMASTERY);
    manager.add_new_message(ActionTextKeys::get_tamed_message(taming_creature->get_description_sid(), to_tame->get_description_sid(), taming_creature->get_is_player()));

    ExperienceManager em;
    PacificationCalculator pc;
    
    double proportion = pc.calculate_exp_proportion(taming_creature, SkillType::SKILL_GENERAL_BEASTMASTERY);
    uint tamed_xp = static_cast<uint>(to_tame->get_experience_value() * proportion);
    tamed_xp = std::max<uint>(tamed_xp, 1);

    em.gain_experience(taming_creature, tamed_xp);

    run_tame_event(taming_creature, to_tame, current_map);
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
    vector<EffectType> anger_effects = { EffectType::EFFECT_TYPE_RAGE, EffectType::EFFECT_TYPE_SPEED };

    for (auto etype : anger_effects)
    {
      EffectPtr effect = EffectFactory::create_effect(etype, {}, {}, "", "");

      if (effect != nullptr)
      {
        effect->effect(to_tame, &am, ItemStatus::ITEM_STATUS_UNCURSED, cc, ct);
      }
    }

    HostilityManager hm;
    hm.set_hostility_to_creature(to_tame, taming_creature->get_id());

    manager.add_new_message(ActionTextKeys::get_tame_failure_message(to_tame->get_description_sid()));
  }
}

void BeastmasterySkillProcessor::run_tame_event(CreaturePtr taming_creature, CreaturePtr tamed_creature, MapPtr map)
{
  string tame_script_id = CreatureEventScripts::CREATURE_EVENT_SCRIPT_TAME;
  ScriptDetails sd = tamed_creature->get_event_script(tame_script_id);
  string event_script_name = sd.get_script();
  int chance = sd.get_chance();

  if (!event_script_name.empty() && RNG::percent_chance(chance))
  {
    ScriptEngine& se = Game::instance().get_script_engine_ref();
    TameScript ts;
    ts.execute(se, event_script_name, tamed_creature, taming_creature, map);

    // Ensure each creature's tame script is only run once.
    tamed_creature->remove_event_script(tame_script_id);
  }
}

SkillProcessorPtr BeastmasterySkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<BeastmasterySkillProcessor>();
  return proc;
}

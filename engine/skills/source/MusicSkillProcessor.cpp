#include "MusicSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "EffectFactory.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MusicTextKeys.hpp"
#include "PacificationCalculator.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "StatusEffectFactory.hpp"
#include "TameScript.hpp"

using namespace std;

ActionCostValue MusicSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature != nullptr && map != nullptr)
  {
    ItemPtr instr = get_musical_instrument(creature);
    pair<string, string> instr_sids = get_instrument_performance_sids(instr);
    int music_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_MUSIC);

    if (music_val > 0)
    {
      perform(creature, map, instr, instr_sids);
    }
    else
    {
      // The performance automatically fails when the player has no skill.
      // Ever tried playing a trumpet or violin with no experience?
      // There are no natural 20s.
      add_performance_details_message(creature, instr_sids.second);
    }

    acv = get_default_skill_action_cost_value(creature);
  }

  return acv;
}

SkillProcessorPtr MusicSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<MusicSkillProcessor>();
  return proc;
}

// Go through the creature's wielded equipment, looking for an instrument.
// If none are found, return a nullptr - this is fine, and will indicate to the
// calling code to consider this a vocal performance.
ItemPtr MusicSkillProcessor::get_musical_instrument(CreaturePtr creature)
{
  ItemPtr instr;

  if (creature != nullptr)
  {
    ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    ItemPtr offhand = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);

    vector<ItemPtr> potential_instr = {wielded, offhand};

    for (ItemPtr item : potential_instr)
    {
      if (item != nullptr && item->has_additional_property(ItemProperties::ITEM_PROPERTIES_MUSIC_PERFORMANCE))
      {
        instr = item;
        break;
      }
    }
  }

  return instr;
}

bool MusicSkillProcessor::is_vocal_performance(ItemPtr item)
{
  bool is_vocal = true;

  if (item != nullptr && item->has_additional_property(ItemProperties::ITEM_PROPERTIES_MUSIC_PERFORMANCE))
  {
    is_vocal = false;
  }

  return is_vocal;
}

// Get the success/failure performance SIDs for the instrument, defaulting to
// the SIDs for voice if the instrument is null or if its SIDs aren't defined.
pair<string, string> MusicSkillProcessor::get_instrument_performance_sids(ItemPtr instr)
{
  string music_performance_sid;
  string music_performance_failed_sid;

  if (instr != nullptr)
  {
    music_performance_sid = instr->get_additional_property(ItemProperties::ITEM_PROPERTIES_MUSIC_PERFORMANCE);
    music_performance_failed_sid = instr->get_additional_property(ItemProperties::ITEM_PROPERTIES_MUSIC_PERFORMANCE_FAILED);
  }

  if (music_performance_sid.empty() || music_performance_failed_sid.empty())
  {
    music_performance_sid = MusicTextKeys::MUSIC_PERFORMANCE_VOICE;
    music_performance_failed_sid = MusicTextKeys::MUSIC_PERFORMANCE_VOICE_FAILED;
  }

  return make_pair(music_performance_sid, music_performance_failed_sid);
}

void MusicSkillProcessor::perform(CreaturePtr creature, MapPtr map, ItemPtr instr, const pair<string, string>& perf_sids)
{
  if (creature != nullptr && map != nullptr)
  {
    CurrentCreatureAbilities cca;
    TilePtr creature_tile = MapUtils::get_tile_for_creature(map, creature);

    if (is_vocal_performance(instr) && !cca.can_speak(creature))
    {
      add_performance_details_message(creature, MusicTextKeys::MUSIC_PERFORMANCE_VOICE_MUTE);
    }
    else if (creature_tile && creature_tile->get_submerged())
    {
      add_performance_details_message(creature, MusicTextKeys::MUSIC_PERFORMANCE_UNDERWATER);
    }
    else
    {
      if (creature_tile && creature_tile->get_tile_type() == TileType::TILE_TYPE_VOID)
      {
        add_performance_details_message(creature, MusicTextKeys::MUSIC_PERFORMANCE_COSMOS);
      }

      CreatureMap fov_creatures = creature->get_decision_strategy()->get_fov_map()->get_creatures();
      int num_hostile = 0;
      int num_pacified = 0;
      int num_not_pacifiable = 0;
      string perf_sid = perf_sids.first; // Start off with the success SID.

      // Begin the performance.
      add_start_performance_message(creature);

      // For each hostile creature, try to tame it.
      for (auto cr_pair : fov_creatures)
      {
        CreaturePtr fov_creature = cr_pair.second;

        if (fov_creature->hostile_to(creature->get_id()))
        {
          auto po = attempt_pacification(instr, creature, fov_creature, map, num_hostile, num_pacified);

          if (po == PacificationOutcome::PACIFICATION_OUTCOME_NOT_PACIFIABLE)
          {
            num_not_pacifiable++;
          }
        }
      }

      // If there were hostile creatures, but none of them were pacified, the
      // performance was a failure.
      if (num_hostile > 0 && num_pacified == 0 && num_hostile != num_not_pacifiable)
      {
        perf_sid = perf_sids.second;
      }
      else if (num_pacified > 0)
      {
        creature->get_skills().mark(SkillType::SKILL_GENERAL_MUSIC);
      }

      add_performance_details_message(creature, perf_sid);
    }
  }
}

PacificationOutcome MusicSkillProcessor::attempt_pacification(ItemPtr instr, CreaturePtr creature, CreaturePtr fov_creature, MapPtr current_map, int& num_hostile, int& num_pacified)
{
  PacificationOutcome po = PacificationOutcome::PACIFICATION_OUTCOME_FAILURE;

  if (creature != nullptr && fov_creature != nullptr)
  {
    num_hostile++;

    ItemStatus item_status = ItemStatus::ITEM_STATUS_UNCURSED;

    if (instr != nullptr)
    {
      item_status = instr->get_status();
    }

    // Certain races are more susceptible to certain instruments.
    bool charms_creature = get_charms_creature(instr, fov_creature);

    PacificationCalculator pc;
    int pct_chance_pacify = pc.calculate_pct_chance_pacify_music(creature, fov_creature, charms_creature, item_status);
    bool pacified = String::to_bool(fov_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_PACIFIED));
    Game& game = Game::instance();

    if (!pacified)
    {
      RaceManager rm;
      Race* race = rm.get_race(fov_creature->get_race_id());

      if (race != nullptr)
      {
        if (race->get_pacifiable())
        {
          if (RNG::percent_chance(pct_chance_pacify))
          {
            game.get_deity_action_manager_ref().notify_action(creature, current_map, CreatureActionKeys::ACTION_PACIFY, true);

            pacify(creature, fov_creature, charms_creature);
            po = PacificationOutcome::PACIFICATION_OUTCOME_SUCCESS;

            num_pacified++;
          }
          else
          {
            if (RNG::percent_chance(75))
            {
              add_unimpressed_message(creature, fov_creature);
            }
            else
            {
              // Creatures that can see through attempts to musically pacify
              // are often unimpressed.
              enrage(creature, fov_creature);
            }
          }
        }
        else
        {
          add_not_pacifiable_message(creature, fov_creature);
          po = PacificationOutcome::PACIFICATION_OUTCOME_NOT_PACIFIABLE;
        }
      }
    }
  }

  return po;
}

void MusicSkillProcessor::add_start_performance_message(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(MusicTextKeys::MUSIC_PERFORMANCE_BEGIN));
    manager.send();
  }
}
void MusicSkillProcessor::add_performance_details_message(CreaturePtr creature, const string& perf_sid)
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(perf_sid));
    manager.send();
  }
}

void MusicSkillProcessor::pacify(CreaturePtr creature, CreaturePtr fov_creature, const bool charms_creature)
{
  if (creature != nullptr && fov_creature != nullptr)
  {
    string creature_id = creature->get_id();

    HostilityManager hm;
    hm.remove_hostility_to_creature(fov_creature, creature_id);
    MapPtr current_map = Game::instance().get_current_map();

    fov_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_PACIFIED, to_string(true));
    fov_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_NO_EXP, to_string(true));
    CreatureUtils::set_leadership(fov_creature, creature_id, current_map);

    // Add a message about the pacification.
    bool creature_is_player = creature->get_is_player();
    bool fov_is_player = fov_creature->get_is_player();

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, fov_creature, creature_is_player || fov_is_player);

    if (charms_creature)
    {
      manager.add_new_message(CombatTextKeys::get_charmed_message(creature_is_player, fov_is_player, StringTable::get(creature->get_description_sid()), StringTable::get(fov_creature->get_description_sid())));
    }
    else
    {
      manager.add_new_message(CombatTextKeys::get_pacification_message(creature_is_player, fov_is_player, StringTable::get(creature->get_description_sid()), StringTable::get(fov_creature->get_description_sid()), true /* pacifiable */));
    }
    
    manager.send();

    ExperienceManager em;
    PacificationCalculator pc;

    double proportion = pc.calculate_exp_proportion(creature, SkillType::SKILL_GENERAL_MUSIC);
    uint tamed_xp = static_cast<uint>(fov_creature->get_experience_value() * proportion);
    tamed_xp = std::max<uint>(tamed_xp, 1);

    em.gain_experience(creature, tamed_xp);
    run_pacification_event(creature, fov_creature);
  }
}

void MusicSkillProcessor::add_unimpressed_message(CreaturePtr creature, CreaturePtr fov_creature)
{
  if (creature != nullptr && fov_creature != nullptr)
  {
    CurrentCreatureAbilities cca;

    if (cca.can_see(creature))
    {
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, fov_creature, creature && creature->get_is_player());
      manager.add_new_message(ActionTextKeys::get_unimpressed_message(fov_creature->get_description_sid(), fov_creature->get_is_player()));
      manager.send();
    }
  }
}
// Enraged creatures have the status set appropriately, causing them to
// deal more damage, soak more, and evade less.
void MusicSkillProcessor::enrage(CreaturePtr creature, CreaturePtr fov_creature)
{
  if (creature != nullptr && fov_creature != nullptr)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();
    MapPtr map = game.get_current_map();
    Coordinate cc = map->get_location(fov_creature->get_id());
    TilePtr ct = map->at(cc);
    vector<EffectType> anger_effects = { EffectType::EFFECT_TYPE_RAGE, EffectType::EFFECT_TYPE_SPEED };

    for (auto etype : anger_effects)
    {
      EffectPtr effect = EffectFactory::create_effect(etype, {}, {}, "", "");

      if (effect != nullptr)
      {
        effect->effect(fov_creature, &am, ItemStatus::ITEM_STATUS_UNCURSED, cc, ct);
      }
    }

    HostilityManager hm;
    hm.set_hostility_to_creature(fov_creature, creature->get_id(), ThreatConstants::ACTIVE_THREAT_RATING);
  }
}

void MusicSkillProcessor::add_not_pacifiable_message(CreaturePtr creature, CreaturePtr fov_creature)
{
  if (creature != nullptr && fov_creature != nullptr)
  {
    bool creature_is_player = creature->get_is_player();
    bool fov_is_player = fov_creature->get_is_player();

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, fov_creature, creature_is_player || fov_is_player);
    manager.add_new_message(CombatTextKeys::get_pacification_message(creature_is_player, fov_is_player, StringTable::get(creature->get_description_sid()), StringTable::get(fov_creature->get_description_sid()), false /* not pacifiable */));
    manager.send();
  }
}

bool MusicSkillProcessor::get_charms_creature(ItemPtr item, CreaturePtr fov_creature)
{
  bool charms = false;

  if (item != nullptr && fov_creature != nullptr)
  {
    RaceManager rm;
    string race_id = fov_creature->get_race_id();
    string charm_races_csv = item->get_additional_property(ItemProperties::ITEM_PROPERTIES_MUSIC_CHARM_RACES);
    vector<string> charm_races = String::create_string_vector_from_csv_string(charm_races_csv);

    charms = std::find(charm_races.begin(), charm_races.end(), race_id) != charm_races.end();
  }
  
  return charms;
}

void MusicSkillProcessor::run_pacification_event(CreaturePtr creature, CreaturePtr fov_creature)
{
  MapPtr map = Game::instance().get_current_map();

  if (map != nullptr)
  {
    // Pacification and Taming are not quite the same thing, but use the same
    // script event.
    string tame_script_id = CreatureEventScripts::CREATURE_EVENT_SCRIPT_TAME;
    ScriptDetails sd = fov_creature->get_event_script(tame_script_id);
    string event_script_name = sd.get_script();
    int chance = sd.get_chance();

    if (!event_script_name.empty() && RNG::percent_chance(chance))
    {
      ScriptEngine& se = Game::instance().get_script_engine_ref();
      TameScript ts;
      ts.execute(se, event_script_name, fov_creature, creature, map);

      // Ensure each creature's tame script is only run once.
      fov_creature->remove_event_script(tame_script_id);
    }
  }
}


#include "MusicSkillProcessor.hpp"
#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemProperties.hpp"
#include "MessageManagerFactory.hpp"
#include "MusicTextKeys.hpp"
#include "PacificationCalculator.hpp"
#include "RNG.hpp"

using namespace std;

ActionCostValue MusicSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

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
    if (is_vocal_performance(instr) && !cca.can_speak(creature))
    {
      add_performance_details_message(creature, MusicTextKeys::MUSIC_PERFORMANCE_VOICE_MUTE);
    }
    else
    {
      PacificationCalculator pc;
      CreatureMap fov_creatures = creature->get_decision_strategy()->get_fov_map()->get_creatures();
      int num_hostile = 0;
      int num_pacified = 0;
      string perf_sid = perf_sids.first; // Start off with the success SID.

      // For each hostile creature, try to tame it.
      for (auto cr_pair : fov_creatures)
      {
        CreaturePtr fov_creature = cr_pair.second;

        if (fov_creature->hostile_to(creature->get_id()))
        {
          num_hostile++;
          int pct_chance_pacify = pc.calculate_pct_chance_pacify_music(creature, fov_creature);
          bool pacified = String::to_bool(fov_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_PACIFIED));

          if (!pacified)
          {
            fov_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_PACIFIED, to_string(true));
            if (RNG::percent_chance(pct_chance_pacify))
            {
              pacify(creature, fov_creature);
              num_pacified++;
            }
            else
            {
              // Creatures that can see through attempts to musically pacify
              // tend to be unimpressed.
              enrage(creature, fov_creature);
            }
          }
        }
      }

      // If there were hostile creatures, but none of them were pacified, the
      // performance was a failure.
      if (num_hostile > 0 && num_pacified == 0)
      {
        perf_sid = perf_sids.second;
      }

      add_performance_details_message(creature, perf_sid);

      // Add messages about which creatures were pacified.
    }
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

void MusicSkillProcessor::pacify(CreaturePtr creature, CreaturePtr fov_creature)
{
  if (creature != nullptr && fov_creature != nullptr)
  {
    HostilityManager hm;
    hm.remove_hostility_to_creature(fov_creature, creature->get_id());

    // Add a message about the pacification.
    bool creature_is_player = creature->get_is_player();
    bool fov_is_player = fov_creature->get_is_player();

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, fov_creature, creature_is_player || fov_is_player);
    manager.add_new_message(CombatTextKeys::get_pacification_message(creature_is_player, fov_is_player, creature->get_description_sid(), fov_creature->get_description_sid()));
    manager.send();
  }
}

// Enraged creatures get a bonus to their base damage.
void MusicSkillProcessor::enrage(CreaturePtr creature, CreaturePtr fov_creature)
{
  if (creature != nullptr && fov_creature != nullptr)
  {
    // Set the status on the FOV creatures.
    //...
  }
}
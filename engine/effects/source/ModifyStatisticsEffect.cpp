#include "Creature.hpp"
#include "CreatureCalculator.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ModifyStatisticsCalculator.hpp"
#include "ModifyStatisticsEffect.hpp"

using namespace std;

void ModifyStatisticsEffect::set_modifier(const Modifier& new_m)
{
  m = new_m;
}

Modifier ModifyStatisticsEffect::get_modifier() const
{
  return m;
}

void ModifyStatisticsEffect::set_spell_id(const string& new_spell_id)
{
  spell_id = new_spell_id;
}

string ModifyStatisticsEffect::get_spell_id() const
{
  return spell_id;
}

string ModifyStatisticsEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  string creature_desc_sid;
  bool is_player = false;
  
  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }
  
  return EffectTextKeys::get_modify_statistics_effect_message(creature_desc_sid, is_player);
}

Effect* ModifyStatisticsEffect::clone()
{
  return new ModifyStatisticsEffect(*this);
}

bool ModifyStatisticsEffect::apply_modifiers(CreaturePtr creature, const Modifier& m, const ModifyStatisticsDuration msd, const double preset_duration) const
{
  bool result = false;

  // The statistic modifiers can't be applied over and over!
  // This isn't Final Fantasy with RUSE.
  if (creature && !creature->is_affected_by_modifier_spell(spell_id))
  {
    ModifyStatisticsCalculator msc;

    double duration_end = preset_duration;

    if (msd == ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_CALCULATE)
    {
      Game& game = Game::instance();
      double seconds = GameUtils::get_seconds(game);

      duration_end = seconds + (msc.calculate_duration() * 60);
    }

    // Get the statistics modifiers.
    auto& cr_sm = creature->get_modifiers_ref();

    // Are there any other modifiers set for a particular duration?
    vector<pair<string, Modifier>> v_m;
    auto cr_sm_it = cr_sm.find(duration_end);

    if (cr_sm_it != cr_sm.end())
    {
      v_m = cr_sm_it->second;
    }

    // Add the statistics modifier to the current list, and add to the creature.
    v_m.push_back(make_pair(spell_id, m));
    cr_sm[duration_end] = v_m;

    // Add any statuses on the modifier to the creature
    vector<string> status_ids = m.get_affected_status_keys();

    for (const auto& status_id : status_ids)
    {
      creature->set_status(status_id, true);
    }

    // Update the creature's calculated values.
    CreatureCalculator::update_calculated_values(creature);

    result = true;
  }

  return result;
}

bool ModifyStatisticsEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  vector<int> blessed_sm_v = m.get_raw_values();
  std::transform(blessed_sm_v.begin(), blessed_sm_v.end(), blessed_sm_v.begin(), 
  [](int a)
    {
      if (a > 0)
      {
        return a * 2;
      }
      else
      {
        return a / 2;
      }
  });

  Modifier blessed_m(blessed_sm_v);
  return apply_modifiers(creature, blessed_m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_CALCULATE);
}

bool ModifyStatisticsEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return apply_modifiers(creature, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_CALCULATE);
}

bool ModifyStatisticsEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  vector<int> blessed_sm_v = m.get_raw_values();
  std::transform(blessed_sm_v.begin(), blessed_sm_v.end(), blessed_sm_v.begin(),
  [](int a)
  {
    if (a < 0)
    {
      return a * 2;
    }
    else
    {
      return a / 2;
    }
  });

  Modifier blessed_m(blessed_sm_v);
  return apply_modifiers(creature, blessed_m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_CALCULATE);
}

// Adjust negative statistics modifiers so that creature stats cannot
// go below 1.
Modifier ModifyStatisticsEffect::adjust_negative_modifiers(CreaturePtr creature, const Modifier& m) const
{
  Modifier new_m = m;

  if (creature)
  {
    // Get the primary statistic modifiers, for checking.  Adding these to the lowest
    // statistic value (base or current) should not bring the stat below 0.
    int str = creature->get_strength().get_lowest();
    int str_mod = new_m.get_strength_modifier();

    int dex = creature->get_dexterity().get_lowest();
    int dex_mod = new_m.get_dexterity_modifier();

    int agi = creature->get_agility().get_lowest();
    int agi_mod = new_m.get_agility_modifier();

    int hea = creature->get_health().get_lowest();
    int hea_mod = new_m.get_health_modifier();

    int itl = creature->get_intelligence().get_lowest();
    int itl_mod = new_m.get_intelligence_modifier();

    int wil = creature->get_willpower().get_lowest();
    int wil_mod = new_m.get_willpower_modifier();

    int cha = creature->get_charisma().get_lowest();
    int cha_mod = new_m.get_charisma_modifier();

    // Evade, soak can be < 0.  But get the values so that new modifiers
    // can be constructed using the vector constructor.
    int evade_mod = new_m.get_evade_modifier();
    int soak_mod = new_m.get_soak_modifier();

    vector<pair<int, int>> pri_stats = { { str, str_mod }, { dex, dex_mod }, { agi, agi_mod }, { hea, hea_mod }, { itl, itl_mod }, { wil, wil_mod }, { cha, cha_mod } };
    vector<int> trans_mods;

    for (const auto& pair : pri_stats)
    {
      trans_mods.push_back(get_primary_statistic_modifier(pair.first, pair.second));
    }

    trans_mods.push_back(evade_mod);
    trans_mods.push_back(soak_mod);

    Modifier transformed(trans_mods);
    new_m = transformed;
  }

  return new_m;
}

// For primary statistics (str, dex, etc) the score can't go above 99 or below 1.
// So calculate the new value for the modifier, given current lowest of the stat's
// base/current.
int ModifyStatisticsEffect::get_primary_statistic_modifier(const int stat_score, const int stat_modifier) const
{
  int modifier = stat_modifier;

  if (stat_score + modifier > 99)
  {
    modifier = 99 - stat_score;
  }
  else if (stat_score + stat_modifier < 1)
  {
    modifier = (stat_score - 1) * -1;
  }

  return modifier;
}

#ifdef UNIT_TESTS
#include "unit_tests/ModifyStatisticsEffect_test.cpp"
#endif
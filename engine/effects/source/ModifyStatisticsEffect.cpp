#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ModifyStatisticsCalculator.hpp"
#include "ModifyStatisticsEffect.hpp"

using namespace std;

void ModifyStatisticsEffect::set_statistics_modifier(const StatisticsModifier& new_sm)
{
  sm = new_sm;
}

StatisticsModifier ModifyStatisticsEffect::get_statistics_modifier() const
{
  return sm;
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

bool ModifyStatisticsEffect::apply_statistics_modifiers(CreaturePtr creature, const StatisticsModifier& sm) const
{
  bool result = false;

  // The statistic modifiers can't be applied over and over!
  // This isn't Final Fantasy with RUSE.
  if (creature && !creature->is_affected_by_modifier_spell(spell_id))
  {
    Game& game = Game::instance();
    double seconds = GameUtils::get_seconds(game);

    ModifyStatisticsCalculator msc;
    double duration_end = seconds + (msc.calculate_duration() * 60);

    // Get the statistics modifiers.
    auto& cr_sm = creature->get_statistics_modifiers_ref();

    // Are there any other modifiers set for a particular duration?
    vector<pair<string, StatisticsModifier>> v_sm;
    auto cr_sm_it = cr_sm.find(duration_end);

    if (cr_sm_it != cr_sm.end())
    {
      v_sm = cr_sm_it->second;
    }

    // Add the statistics modifier to the current list, and add to the creature.
    v_sm.push_back(make_pair(spell_id, sm));
    cr_sm[duration_end] = v_sm;

    result = true;
  }

  return result;
}

bool ModifyStatisticsEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  vector<int> blessed_sm_v = sm.get_raw_values();
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

  StatisticsModifier blessed_sm(blessed_sm_v);
  return apply_statistics_modifiers(creature, blessed_sm);
}

bool ModifyStatisticsEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return apply_statistics_modifiers(creature, sm);
}

bool ModifyStatisticsEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  vector<int> blessed_sm_v = sm.get_raw_values();
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

  StatisticsModifier blessed_sm(blessed_sm_v);
  return apply_statistics_modifiers(creature, blessed_sm);
}

// Adjust negative statistics modifiers so that creature stats cannot
// go below 1.
StatisticsModifier ModifyStatisticsEffect::adjust_negative_statistics_modifiers(CreaturePtr creature, const StatisticsModifier& sm) const
{
  StatisticsModifier new_sm = sm;

  if (creature)
  {
    // Get the primary statistic modifiers, for checking.  Adding these to the lowest
    // statistic value (base or current) should not bring the stat below 0.
    int str = creature->get_strength().get_lowest();
    int str_mod = new_sm.get_strength_modifier();

    int dex = creature->get_dexterity().get_lowest();
    int dex_mod = new_sm.get_dexterity_modifier();

    int agi = creature->get_agility().get_lowest();
    int agi_mod = new_sm.get_agility_modifier();

    int hea = creature->get_health().get_lowest();
    int hea_mod = new_sm.get_health_modifier();

    int itl = creature->get_intelligence().get_lowest();
    int itl_mod = new_sm.get_intelligence_modifier();

    int wil = creature->get_willpower().get_lowest();
    int wil_mod = new_sm.get_willpower_modifier();

    int cha = creature->get_charisma().get_lowest();
    int cha_mod = new_sm.get_charisma_modifier();

    // Evade, soak can be < 0.  But get the values so that new modifiers
    // can be constructed using the vector constructor.
    int evade_mod = new_sm.get_evade_modifier();
    int soak_mod = new_sm.get_soak_modifier();

    vector<pair<int, int>> pri_stats = { { str, str_mod }, { dex, dex_mod }, { agi, agi_mod }, { hea, hea_mod }, { itl, itl_mod }, { wil, wil_mod }, { cha, cha_mod } };
    vector<int> trans_mods;

    for (const auto& pair : pri_stats)
    {
      trans_mods.push_back(get_primary_statistic_modifier(pair.first, pair.second));
    }

    trans_mods.push_back(evade_mod);
    trans_mods.push_back(soak_mod);

    StatisticsModifier transformed(trans_mods);
    new_sm = transformed;
  }

  return new_sm;
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
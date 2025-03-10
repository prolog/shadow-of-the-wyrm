#include "Creature.hpp"
#include "CreatureCalculator.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ModifyStatisticsCalculator.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "StatusTypes.hpp"

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

void ModifyStatisticsEffect::set_source_id(const string& new_source_id)
{
  source_id = new_source_id;
}

string ModifyStatisticsEffect::get_source_id() const
{
  return source_id;
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

bool ModifyStatisticsEffect::is_negative_effect() const
{
  return m.is_negative();
}

bool ModifyStatisticsEffect::apply_modifiers(CreaturePtr creature, const Modifier& m_apply, const ModifyStatisticsDuration msd, const double preset_duration) const
{
  bool result = false;

  // The statistic modifiers can't be applied over and over!
  // This isn't Final Fantasy with RUSE.
  if (creature && (StatusIdentifiers::is_status_identifier(spell_id) || !creature->is_affected_by_modifier_spell(spell_id)))
  {
    ModifyStatisticsCalculator msc;

    double duration_end = preset_duration;

    if (msd == ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_CALCULATE)
    {
      Game& game = Game::instance();
      double seconds = GameUtils::get_seconds(game);

      duration_end = seconds + (static_cast<double>(msc.calculate_duration()) * 60);
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
    v_m.push_back(make_pair(spell_id, m_apply));
    cr_sm[duration_end] = v_m;

    // Add any statuses on the modifier to the creature
    vector<pair<string, int>> statuses = m_apply.get_affected_statuses();

    for (const auto& status : statuses)
    {
      if (!creature->has_status(status.first))
      {
        creature->set_status(status.first, { status.first, true, status.second, source_id });
      }
    }

    // Update the creature's calculated values.
    CreatureCalculator cc;
    cc.update_calculated_values(creature);

    result = true;
  }

  return result;
}

bool ModifyStatisticsEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
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

bool ModifyStatisticsEffect::effect_uncursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return apply_modifiers(creature, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_CALCULATE);
}

bool ModifyStatisticsEffect::effect_cursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
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
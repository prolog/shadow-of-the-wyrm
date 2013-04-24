#include "Game.hpp"
#include "MagicalAttackSpeedCalculator.hpp"
#include "NullSpeedCalculator.hpp"

using namespace std;

ActionCostValue MagicalAttackSpeedCalculator::calculate(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 1;

  if (creature)
  {
    string spell_id = creature->get_spell_knowledge_ref().get_most_recently_cast_spell_id();

    if (!spell_id.empty())
    {
      Spell spell = Game::instance().get_spells_ref().find(spell_id)->second;
      action_cost_value = spell.get_speed();
    }
  }

  return action_cost_value;
}

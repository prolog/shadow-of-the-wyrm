#include "WandsAttackSpeedCalculator.hpp"

using namespace std;

const int WandsAttackSpeedCalculator::WANDCRAFT_SPEED_DIVISOR = 10;

ActionCostValue WandsAttackSpeedCalculator::calculate(CreaturePtr creature)
{
  ActionCostValue action_cost_value = ActionCostConstants::BASE_EVOKE;

  if (creature)
  {
    action_cost_value = std::max<int>(ActionCostConstants::DEFAULT, action_cost_value - (creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT) / WANDCRAFT_SPEED_DIVISOR));
  }

  return action_cost_value;
}

#ifdef UNIT_TESTS
#include "unit_tests/WandsAttackSpeedCalculator_test.cpp"
#endif

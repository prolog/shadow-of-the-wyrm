#include "CreatureSkillMarkerChecker.hpp"
#include "EngineConversion.hpp"

using namespace std;

CreatureSkillMarkerChecker::CreatureSkillMarkerChecker()
: minutes_interval(1)
{
}

CreatureSkillMarkerChecker::CreatureSkillMarkerChecker(const uint new_interval)
: minutes_interval(new_interval)
{
}

void CreatureSkillMarkerChecker::tick(CreaturePtr creature, TilePtr tile, const ulonglong min_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature != nullptr)
  {
    if (total_minutes_elapsed % minutes_interval == 0)
    {
      // JCD FIXME Refactor this if we need to do multiple skills
      // in future.
      BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);
      int num_marks = 0;

      if (bl == BurdenLevel::BURDEN_LEVEL_BURDENED)
      {
        num_marks+=2;
      }
      else if (bl == BurdenLevel::BURDEN_LEVEL_STRAINED)
      {
        num_marks += 3;
      }

      for (int i = 0; i < num_marks; i++)
      {
        creature->get_skills().mark(SkillType::SKILL_GENERAL_CARRYING);
      }
    }
  }
}

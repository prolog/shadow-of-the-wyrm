#include "SkillProcessorFactory.hpp"
#include "SkillProcessors.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

SkillProcessorFactory::SkillProcessorFactory()
{
}

SkillProcessorFactory::~SkillProcessorFactory()
{
}

ISkillProcessorPtr SkillProcessorFactory::create(const SkillType st)
{
  ISkillProcessorPtr sp = std::make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_UNIMPLEMENTED);

  if (st >= SkillType::SKILL_GENERAL_ARCHERY && st < SkillType::SKILL_GENERAL_LAST)
  {
    // Handle the individual skills as necessary here.
  }
  else if (st >= SkillType::SKILL_MELEE_BEGIN && st < SkillType::SKILL_MELEE_LAST)
  {
    sp = make_shared<WeaponSkillProcessor>();
  }
  else if (st >= SkillType::SKILL_RANGED_BEGIN && st < SkillType::SKILL_RANGED_LAST)
  {
    sp = make_shared<WeaponSkillProcessor>();
  }
  else if (st >= SkillType::SKILL_MAGIC_BEGIN && st < SkillType::SKILL_MAGIC_LAST)
  {
    sp = make_shared<MagicSkillProcessor>();
  }

  return sp;
}


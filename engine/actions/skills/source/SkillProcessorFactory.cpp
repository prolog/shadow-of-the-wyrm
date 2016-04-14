#include "SkillProcessorFactory.hpp"
#include "SkillProcessors.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

map<SkillType, string> SkillProcessorFactory::skill_map;

SkillProcessorFactory::SkillProcessorFactory()
{
}

SkillProcessorFactory::~SkillProcessorFactory()
{
}

void SkillProcessorFactory::populate_skill_map()
{
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_ARCHERY, SkillTextKeys::SKILL_USAGE_ARCHERY));
}

ISkillProcessorPtr SkillProcessorFactory::create(const SkillType st)
{
  static_assert(SkillType::SKILL_GENERAL_LAST == static_cast<SkillType>(49), "Unexpected SKILL_GENERAL_LAST");
  static_assert(SkillType::SKILL_MELEE_LAST == static_cast<SkillType>(1010), "Unexpected SKILL_MELEE_LAST");
  static_assert(SkillType::SKILL_RANGED_LAST == static_cast<SkillType>(2010), "Unexpected SKILL_RANGED_LAST");
  static_assert(SkillType::SKILL_MAGIC_LAST == static_cast<SkillType>(3005), "Unexpected SKILL_MAGIC_LAST");

  if (skill_map.empty())
  {
    populate_skill_map();
  }

  ISkillProcessorPtr sp = std::make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_UNIMPLEMENTED);

  if (st >= SkillType::SKILL_GENERAL_ARCHERY && st < SkillType::SKILL_GENERAL_LAST)
  {
    // Handle the individual skills as necessary here.
    auto s_it = skill_map.find(st);

    if (s_it != skill_map.end())
    {
      sp = std::make_shared<DefaultSkillProcessor>(s_it->second);
    }
    // else: get the "not yet implemented" message
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


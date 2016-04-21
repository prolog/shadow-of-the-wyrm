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
  skill_map = {{SkillType::SKILL_GENERAL_ARCHERY, SkillTextKeys::SKILL_USAGE_ARCHERY},
               {SkillType::SKILL_GENERAL_AWARENESS, SkillTextKeys::SKILL_USAGE_AWARENESS},
               {SkillType::SKILL_GENERAL_BLIND_FIGHTING, SkillTextKeys::SKILL_USAGE_BLIND_FIGHTING},
               {SkillType::SKILL_GENERAL_CARRYING, SkillTextKeys::SKILL_USAGE_CARRYING},
               {SkillType::SKILL_GENERAL_COMBAT, SkillTextKeys::SKILL_USAGE_COMBAT},
               {SkillType::SKILL_GENERAL_DETECTION, SkillTextKeys::SKILL_USAGE_DETECTION},
               {SkillType::SKILL_GENERAL_DUAL_WIELD, SkillTextKeys::SKILL_USAGE_DUAL_WIELD},
               {SkillType::SKILL_GENERAL_ESCAPE, SkillTextKeys::SKILL_USAGE_ESCAPE},
               {SkillType::SKILL_GENERAL_FORAGING, SkillTextKeys::SKILL_USAGE_FORAGING},
               {SkillType::SKILL_GENERAL_JEWELER, SkillTextKeys::SKILL_USAGE_JEWELER},
               {SkillType::SKILL_GENERAL_MAGIC, SkillTextKeys::SKILL_USAGE_GENERAL_MAGIC},
               {SkillType::SKILL_GENERAL_MOUNTAINEERING, SkillTextKeys::SKILL_USAGE_MOUNTAINEERING},
               {SkillType::SKILL_GENERAL_RELIGION, SkillTextKeys::SKILL_USAGE_RELIGION},
               {SkillType::SKILL_GENERAL_SKINNING, SkillTextKeys::SKILL_USAGE_SKINNING},
               {SkillType::SKILL_GENERAL_SMITHING, SkillTextKeys::SKILL_USAGE_SMITHING},
               {SkillType::SKILL_GENERAL_SWIMMING, SkillTextKeys::SKILL_USAGE_SWIMMING},
               {SkillType::SKILL_GENERAL_TANNING, SkillTextKeys::SKILL_USAGE_TANNING},
               {SkillType::SKILL_GENERAL_WEAVING, SkillTextKeys::SKILL_USAGE_WEAVING}};
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


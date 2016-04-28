#include "FishingSkillProcessor.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillProcessors.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

map<SkillType, SkillProcessorPtr> SkillProcessorFactory::skill_map;

SkillProcessorFactory::SkillProcessorFactory()
{
}

SkillProcessorFactory::~SkillProcessorFactory()
{
}

void SkillProcessorFactory::populate_skill_map()
{
  skill_map = {make_pair(SkillType::SKILL_GENERAL_ARCHERY, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_ARCHERY)),
               make_pair(SkillType::SKILL_GENERAL_AWARENESS, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_AWARENESS)),
               make_pair(SkillType::SKILL_GENERAL_BLIND_FIGHTING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_BLIND_FIGHTING)),
               make_pair(SkillType::SKILL_GENERAL_CARRYING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_CARRYING)),
               make_pair(SkillType::SKILL_GENERAL_COMBAT, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_COMBAT)),
               make_pair(SkillType::SKILL_GENERAL_DETECTION, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_DETECTION)),
               make_pair(SkillType::SKILL_GENERAL_DUAL_WIELD, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_DUAL_WIELD)),
               make_pair(SkillType::SKILL_GENERAL_ESCAPE, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_ESCAPE)),
               make_pair(SkillType::SKILL_GENERAL_FISHING, make_shared<FishingSkillProcessor>()),
               make_pair(SkillType::SKILL_GENERAL_FORAGING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_FORAGING)),
               make_pair(SkillType::SKILL_GENERAL_HUNTING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_HUNTING)),
               make_pair(SkillType::SKILL_GENERAL_JEWELER, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_JEWELER)),
               make_pair(SkillType::SKILL_GENERAL_MAGIC, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_GENERAL_MAGIC)),
               make_pair(SkillType::SKILL_GENERAL_MOUNTAINEERING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_MOUNTAINEERING)),
               make_pair(SkillType::SKILL_GENERAL_RELIGION, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_RELIGION)),
               make_pair(SkillType::SKILL_GENERAL_SKINNING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_SKINNING)),
               make_pair(SkillType::SKILL_GENERAL_SMITHING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_SMITHING)),
               make_pair(SkillType::SKILL_GENERAL_SWIMMING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_SWIMMING)),
               make_pair(SkillType::SKILL_GENERAL_TANNING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_TANNING)),
               make_pair(SkillType::SKILL_GENERAL_WEAVING, make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_WEAVING))};
}

SkillProcessorPtr SkillProcessorFactory::create(const SkillType st)
{
  static_assert(SkillType::SKILL_GENERAL_LAST == static_cast<SkillType>(49), "Unexpected SKILL_GENERAL_LAST");
  static_assert(SkillType::SKILL_MELEE_LAST == static_cast<SkillType>(1010), "Unexpected SKILL_MELEE_LAST");
  static_assert(SkillType::SKILL_RANGED_LAST == static_cast<SkillType>(2010), "Unexpected SKILL_RANGED_LAST");
  static_assert(SkillType::SKILL_MAGIC_LAST == static_cast<SkillType>(3005), "Unexpected SKILL_MAGIC_LAST");

  if (skill_map.empty())
  {
    populate_skill_map();
  }

  SkillProcessorPtr sp = std::make_shared<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_UNIMPLEMENTED);

  if (st >= SkillType::SKILL_GENERAL_ARCHERY && st < SkillType::SKILL_GENERAL_LAST)
  {
    // Handle the individual skills as necessary here.
    auto s_it = skill_map.find(st);

    if (s_it != skill_map.end() && s_it->second != nullptr)
    {
      sp = s_it->second;
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


#include "BeastmasterySkillProcessor.hpp"
#include "BowyerSkillProcessor.hpp"
#include "DisarmTrapsSkillProcessor.hpp"
#include "FishingSkillProcessor.hpp"
#include "FletcherySkillProcessor.hpp"
#include "HidingSkillProcessor.hpp"
#include "MusicSkillProcessor.hpp"
#include "PapercraftSkillProcessor.hpp"
#include "ScribingSkillProcessor.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillProcessors.hpp"
#include "SkillTextKeys.hpp"
#include "ThieverySkillProcessor.hpp"
#include "WandcraftSkillProcessor.hpp"

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
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_ARCHERY, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_ARCHERY)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_AWARENESS, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_AWARENESS)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_BARGAINING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_BARGAINING  )));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_BEASTMASTERY, make_unique<BeastmasterySkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_BLIND_FIGHTING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_BLIND_FIGHTING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_BOWYER, make_unique<BowyerSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_CARRYING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_CARRYING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_COMBAT, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_COMBAT)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_DETECTION, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_DETECTION)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_DISARM_TRAPS, make_unique<DisarmTrapsSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_DUAL_WIELD, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_DUAL_WIELD)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_DUNGEONEERING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_DUNGEONEERING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_ESCAPE, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_ESCAPE)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_FISHING, make_unique<FishingSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_FLETCHERY, make_unique<FletcherySkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_FORAGING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_FORAGING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_HERBALISM, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_HERBALISM)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_HIDING, make_unique<HidingSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_HUNTING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_HUNTING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_INTIMIDATION, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_INTIMIDATION)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_JEWELER, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_JEWELER)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_LEADERSHIP, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_LEADERSHIP)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_LITERACY, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_LITERACY)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_LORE, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_LORE)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_MAGIC, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_GENERAL_MAGIC)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_MEDICINE, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_MEDICINE)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_MOUNTAINEERING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_MOUNTAINEERING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_MUSIC, make_unique<MusicSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_NIGHT_SIGHT, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_NIGHT_SIGHT)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_PAPERCRAFT, make_unique<PapercraftSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_RELIGION, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_RELIGION)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_SCRIBING, make_unique<ScribingSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_SKINNING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_SKINNING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_SMITHING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_SMITHING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_STEALTH,  make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_STEALTH)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_SWIMMING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_SWIMMING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_TANNING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_TANNING)));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_THIEVERY, make_unique<ThieverySkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_WANDCRAFT, make_unique<WandcraftSkillProcessor>()));
  skill_map.insert(make_pair(SkillType::SKILL_GENERAL_WEAVING, make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_WEAVING)));
}

SkillProcessorPtr SkillProcessorFactory::create(const SkillType st)
{
  static_assert(SkillType::SKILL_GENERAL_LAST == static_cast<SkillType>(50), "Unexpected SKILL_GENERAL_LAST");
  static_assert(SkillType::SKILL_MELEE_LAST == static_cast<SkillType>(1010), "Unexpected SKILL_MELEE_LAST");
  static_assert(SkillType::SKILL_RANGED_LAST == static_cast<SkillType>(2010), "Unexpected SKILL_RANGED_LAST");
  static_assert(SkillType::SKILL_MAGIC_LAST == static_cast<SkillType>(3005), "Unexpected SKILL_MAGIC_LAST");

  if (skill_map.empty())
  {
    populate_skill_map();
  }

  SkillProcessorPtr sp = std::make_unique<DefaultSkillProcessor>(SkillTextKeys::SKILL_USAGE_UNIMPLEMENTED);

  if (st >= SkillType::SKILL_GENERAL_ARCHERY && st < SkillType::SKILL_GENERAL_LAST)
  {
    // Handle the individual skills as necessary here.
    auto s_it = skill_map.find(st);

    if (s_it != skill_map.end() && s_it->second != nullptr)
    {
      sp = s_it->second->clone();
    }
    // else: get the "not yet implemented" message
  }
  else if (st >= SkillType::SKILL_MELEE_BEGIN && st < SkillType::SKILL_MELEE_LAST)
  {
    sp = make_unique<WeaponSkillProcessor>();
  }
  else if (st >= SkillType::SKILL_RANGED_BEGIN && st < SkillType::SKILL_RANGED_LAST)
  {
    sp = make_unique<WeaponSkillProcessor>();
  }
  else if (st >= SkillType::SKILL_MAGIC_BEGIN && st < SkillType::SKILL_MAGIC_LAST)
  {
    sp = make_unique<MagicSkillProcessor>();
  }

  return sp;
}


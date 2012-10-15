#include <boost/make_shared.hpp>
#include "SkillFactory.hpp"

using namespace std;

SkillSerializationMap SkillFactory::skill_map;

SkillFactory::SkillFactory()
{
}

SkillFactory::~SkillFactory()
{
}

SkillPtr SkillFactory::create_skill(const ClassIdentifier ci)
{
  SkillPtr skill;

  if (skill_map.empty())
  {
    initialize_skill_map();
  }

  SkillSerializationMap::iterator s_it = skill_map.find(ci);

  if (s_it != skill_map.end())
  {
    skill = SkillPtr(s_it->second->clone());
  }

  return skill;
}

void SkillFactory::initialize_skill_map()
{
  skill_map.clear();

  boost::shared_ptr<ArcherySkill> archery = boost::make_shared<ArcherySkill>();
  boost::shared_ptr<AwarenessSkill> awareness = boost::make_shared<AwarenessSkill>();
  boost::shared_ptr<BargainingSkill> bargaining = boost::make_shared<BargainingSkill>();
  boost::shared_ptr<BeastmasterySkill> beastmastery = boost::make_shared<BeastmasterySkill>();
  boost::shared_ptr<BlindFightingSkill> blind_fighting = boost::make_shared<BlindFightingSkill>();
  boost::shared_ptr<BoatingSkill> boating = boost::make_shared<BoatingSkill>();
  boost::shared_ptr<BowyerSkill> bowyer = boost::make_shared<BowyerSkill>();
  boost::shared_ptr<BrewingSkill> brewing = boost::make_shared<BrewingSkill>();
  boost::shared_ptr<CantripsSkill> cantrips = boost::make_shared<CantripsSkill>();
  boost::shared_ptr<CarryingSkill> carrying = boost::make_shared<CarryingSkill>();
  boost::shared_ptr<CombatSkill> combat = boost::make_shared<CombatSkill>();
  boost::shared_ptr<CraftingSkill> crafting = boost::make_shared<CraftingSkill>();
  boost::shared_ptr<DesertLoreSkill> desert_lore = boost::make_shared<DesertLoreSkill>();
  boost::shared_ptr<DetectionSkill> detection = boost::make_shared<DetectionSkill>();
  boost::shared_ptr<DisarmTrapsSkill> disarm_traps = boost::make_shared<DisarmTrapsSkill>();
  boost::shared_ptr<DualWieldSkill> dual_wield = boost::make_shared<DualWieldSkill>();
  boost::shared_ptr<DungeoneeringSkill> dungeoneering = boost::make_shared<DungeoneeringSkill>();
  boost::shared_ptr<EscapeSkill> escape = boost::make_shared<EscapeSkill>();
  boost::shared_ptr<FishingSkill> fishing = boost::make_shared<FishingSkill>();
  boost::shared_ptr<FletcherySkill> fletchery = boost::make_shared<FletcherySkill>();
  boost::shared_ptr<ForagingSkill> foraging = boost::make_shared<ForagingSkill>();
  boost::shared_ptr<ForestLoreSkill> forest_lore = boost::make_shared<ForestLoreSkill>();
  boost::shared_ptr<HerbalismSkill> herbalism = boost::make_shared<HerbalismSkill>();
  boost::shared_ptr<HidingSkill> hiding = boost::make_shared<HidingSkill>();
  boost::shared_ptr<HuntingSkill> hunting = boost::make_shared<HuntingSkill>();
  boost::shared_ptr<IntimidationSkill> intimidation = boost::make_shared<IntimidationSkill>();
  boost::shared_ptr<JewelerSkill> jeweler = boost::make_shared<JewelerSkill>();
  boost::shared_ptr<JumpingSkill> jumping = boost::make_shared<JumpingSkill>();
  boost::shared_ptr<LeadershipSkill> leadership = boost::make_shared<LeadershipSkill>();
  boost::shared_ptr<LiteracySkill> literacy = boost::make_shared<LiteracySkill>();
  boost::shared_ptr<LoreSkill> lore = boost::make_shared<LoreSkill>();
  boost::shared_ptr<MagicGeneralSkill> magic = boost::make_shared<MagicGeneralSkill>();
  boost::shared_ptr<MarshLoreSkill> marsh_lore = boost::make_shared<MarshLoreSkill>();
  boost::shared_ptr<MedicineSkill> medicine = boost::make_shared<MedicineSkill>();
  boost::shared_ptr<MountainLoreSkill> mountain_lore = boost::make_shared<MountainLoreSkill>();
  boost::shared_ptr<MountaineeringSkill> mountaineering = boost::make_shared<MountaineeringSkill>();
  boost::shared_ptr<MusicSkill> music = boost::make_shared<MusicSkill>();
  boost::shared_ptr<NightSightSkill> night_sight = boost::make_shared<NightSightSkill>();
  boost::shared_ptr<OceanographySkill> oceanography = boost::make_shared<OceanographySkill>();
  boost::shared_ptr<PapercraftSkill> papercraft = boost::make_shared<PapercraftSkill>();
  boost::shared_ptr<ReligionSkill> religion = boost::make_shared<ReligionSkill>();
  boost::shared_ptr<ScribingSkill> scribing = boost::make_shared<ScribingSkill>();
  boost::shared_ptr<SkinningSkill> skinning = boost::make_shared<SkinningSkill>();
  boost::shared_ptr<SmithingSkill> smithing = boost::make_shared<SmithingSkill>();
  boost::shared_ptr<SpelunkingSkill> spelunking = boost::make_shared<SpelunkingSkill>();
  boost::shared_ptr<StealthSkill> stealth = boost::make_shared<StealthSkill>();
  boost::shared_ptr<SwimmingSkill> swimming = boost::make_shared<SwimmingSkill>();
  boost::shared_ptr<TanningSkill> tanning = boost::make_shared<TanningSkill>();
  boost::shared_ptr<ThieverySkill> thievery = boost::make_shared<ThieverySkill>();
  boost::shared_ptr<WeavingSkill> weaving = boost::make_shared<WeavingSkill>();
  boost::shared_ptr<AxesSkill> axes = boost::make_shared<AxesSkill>();
  boost::shared_ptr<ShortBladesSkill> short_blades = boost::make_shared<ShortBladesSkill>();
  boost::shared_ptr<LongBladesSkill> long_blades = boost::make_shared<LongBladesSkill>();
  boost::shared_ptr<BludgeonsSkill> bludgeons = boost::make_shared<BludgeonsSkill>();
  boost::shared_ptr<DaggersSkill> daggers = boost::make_shared<DaggersSkill>();
  boost::shared_ptr<RodsAndStavesSkill> rods_and_staves = boost::make_shared<RodsAndStavesSkill>();
  boost::shared_ptr<SpearsSkill> spears = boost::make_shared<SpearsSkill>();
  boost::shared_ptr<UnarmedSkill> unarmed = boost::make_shared<UnarmedSkill>();
  boost::shared_ptr<WhipsSkill> whips = boost::make_shared<WhipsSkill>();
  boost::shared_ptr<ExoticMeleeSkill> exotic = boost::make_shared<ExoticMeleeSkill>();
  boost::shared_ptr<ThrownAxesSkill> thrown_axes = boost::make_shared<ThrownAxesSkill>();
  boost::shared_ptr<ThrownBladesSkill> thrown_blades = boost::make_shared<ThrownBladesSkill>();
  boost::shared_ptr<ThrownBludgeonsSkill> thrown_bludgeons = boost::make_shared<ThrownBludgeonsSkill>();
  boost::shared_ptr<BowsSkill> bows = boost::make_shared<BowsSkill>();
  boost::shared_ptr<CrossbowsSkill> crossbows = boost::make_shared<CrossbowsSkill>();
  boost::shared_ptr<ThrownDaggersSkill> thrown_daggers = boost::make_shared<ThrownDaggersSkill>();
  boost::shared_ptr<RocksSkill> rocks = boost::make_shared<RocksSkill>();
  boost::shared_ptr<SlingsSkill> slings = boost::make_shared<SlingsSkill>();
  boost::shared_ptr<ThrownSpearsSkill> thrown_spears = boost::make_shared<ThrownSpearsSkill>();
  boost::shared_ptr<ExoticRangedSkill> thrown_exotic = boost::make_shared<ExoticRangedSkill>();
  boost::shared_ptr<ArcaneMagicSkill> arcane = boost::make_shared<ArcaneMagicSkill>();
  boost::shared_ptr<DivineMagicSkill> divine = boost::make_shared<DivineMagicSkill>();
  boost::shared_ptr<MysticMagicSkill> mystic = boost::make_shared<MysticMagicSkill>();
  boost::shared_ptr<PrimordialMagicSkill> primordial = boost::make_shared<PrimordialMagicSkill>();

  skill_map.insert(make_pair(CLASS_ID_SKILL_ARCHERY, archery));
  skill_map.insert(make_pair(CLASS_ID_SKILL_AWARENESS, awareness));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BARGAINING, bargaining));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BEASTMASTERY, beastmastery));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BLINDFIGHTING, blind_fighting));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BOATING, boating));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BOWYER, bowyer));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BREWING, brewing));
  skill_map.insert(make_pair(CLASS_ID_SKILL_CANTRIPS, cantrips));
  skill_map.insert(make_pair(CLASS_ID_SKILL_CARRYING, carrying));
  skill_map.insert(make_pair(CLASS_ID_SKILL_COMBAT, combat));
  skill_map.insert(make_pair(CLASS_ID_SKILL_CRAFTING, crafting));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DESERT_LORE, desert_lore));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DETECTION, detection));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DISARM_TRAPS, disarm_traps));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DUAL_WIELD, dual_wield));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DUNGEONEERING, dungeoneering));
  skill_map.insert(make_pair(CLASS_ID_SKILL_ESCAPE, escape));
  skill_map.insert(make_pair(CLASS_ID_SKILL_FISHING, fishing));
  skill_map.insert(make_pair(CLASS_ID_SKILL_FLETCHERY, fletchery));
  skill_map.insert(make_pair(CLASS_ID_SKILL_FORAGING, foraging));
  skill_map.insert(make_pair(CLASS_ID_SKILL_FOREST_LORE, forest_lore));
  skill_map.insert(make_pair(CLASS_ID_SKILL_HERBALISM, herbalism));
  skill_map.insert(make_pair(CLASS_ID_SKILL_HIDING, hiding));
  skill_map.insert(make_pair(CLASS_ID_SKILL_HUNTING, hunting));
  skill_map.insert(make_pair(CLASS_ID_SKILL_INTIMIDATION, intimidation));
  skill_map.insert(make_pair(CLASS_ID_SKILL_JEWELER, jeweler));
  skill_map.insert(make_pair(CLASS_ID_SKILL_JUMPING, jumping));
  skill_map.insert(make_pair(CLASS_ID_SKILL_LEADERSHIP, leadership));
  skill_map.insert(make_pair(CLASS_ID_SKILL_LITERACY, literacy));
  skill_map.insert(make_pair(CLASS_ID_SKILL_LORE, lore));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MAGICGENERAL, magic));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MARSH_LORE, marsh_lore));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MEDICINE, medicine));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MOUNTAIN_LORE, mountain_lore));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MOUNTAINEERING, mountaineering));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MUSIC, music));
  skill_map.insert(make_pair(CLASS_ID_SKILL_NIGHT_SIGHT, night_sight));
  skill_map.insert(make_pair(CLASS_ID_SKILL_OCEANOGRAPHY, oceanography));
  skill_map.insert(make_pair(CLASS_ID_SKILL_PAPERCRAFT, papercraft));
  skill_map.insert(make_pair(CLASS_ID_SKILL_RELIGION, religion));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SCRIBING, scribing));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SKINNING, skinning));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SMITHING, smithing));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SPELUNKING, spelunking));
  skill_map.insert(make_pair(CLASS_ID_SKILL_STEALTH, stealth));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SWIMMING, swimming));
  skill_map.insert(make_pair(CLASS_ID_SKILL_TANNING, tanning));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THIEVERY, thievery));
  skill_map.insert(make_pair(CLASS_ID_SKILL_WEAVING, weaving));
  skill_map.insert(make_pair(CLASS_ID_SKILL_AXES, axes));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SHORT_BLADES, short_blades));
  skill_map.insert(make_pair(CLASS_ID_SKILL_LONG_BLADES, long_blades));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BLUDGEONS, bludgeons));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DAGGERS, daggers));
  skill_map.insert(make_pair(CLASS_ID_SKILL_RODS_AND_STAVES, rods_and_staves));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SPEARS, spears));
  skill_map.insert(make_pair(CLASS_ID_SKILL_UNARMED, unarmed));
  skill_map.insert(make_pair(CLASS_ID_SKILL_WHIPS, whips));
  skill_map.insert(make_pair(CLASS_ID_SKILL_EXOTIC, exotic));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THROWN_AXES, thrown_axes));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THROWN_BLADES, thrown_blades));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THROWN_BLUDGEONS, thrown_bludgeons));
  skill_map.insert(make_pair(CLASS_ID_SKILL_BOWS, bows));
  skill_map.insert(make_pair(CLASS_ID_SKILL_CROSSBOWS, crossbows));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THROWN_DAGGERS, thrown_daggers));
  skill_map.insert(make_pair(CLASS_ID_SKILL_ROCKS, rocks));
  skill_map.insert(make_pair(CLASS_ID_SKILL_SLINGS, slings));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THROWN_SPEARS, thrown_spears));
  skill_map.insert(make_pair(CLASS_ID_SKILL_THROWN_EXOTIC, thrown_exotic));
  skill_map.insert(make_pair(CLASS_ID_SKILL_ARCANE, arcane));
  skill_map.insert(make_pair(CLASS_ID_SKILL_DIVINE, divine));
  skill_map.insert(make_pair(CLASS_ID_SKILL_MYSTIC, mystic));
  skill_map.insert(make_pair(CLASS_ID_SKILL_PRIMORDIAL, primordial));
}

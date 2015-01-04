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

  std::shared_ptr<ArcherySkill> archery = std::make_shared<ArcherySkill>();
  std::shared_ptr<AwarenessSkill> awareness = std::make_shared<AwarenessSkill>();
  std::shared_ptr<BargainingSkill> bargaining = std::make_shared<BargainingSkill>();
  std::shared_ptr<BeastmasterySkill> beastmastery = std::make_shared<BeastmasterySkill>();
  std::shared_ptr<BlindFightingSkill> blind_fighting = std::make_shared<BlindFightingSkill>();
  std::shared_ptr<BoatingSkill> boating = std::make_shared<BoatingSkill>();
  std::shared_ptr<BowyerSkill> bowyer = std::make_shared<BowyerSkill>();
  std::shared_ptr<BrewingSkill> brewing = std::make_shared<BrewingSkill>();
  std::shared_ptr<CantripsSkill> cantrips = std::make_shared<CantripsSkill>();
  std::shared_ptr<CarryingSkill> carrying = std::make_shared<CarryingSkill>();
  std::shared_ptr<CombatSkill> combat = std::make_shared<CombatSkill>();
  std::shared_ptr<CraftingSkill> crafting = std::make_shared<CraftingSkill>();
  std::shared_ptr<DesertLoreSkill> desert_lore = std::make_shared<DesertLoreSkill>();
  std::shared_ptr<DetectionSkill> detection = std::make_shared<DetectionSkill>();
  std::shared_ptr<DisarmTrapsSkill> disarm_traps = std::make_shared<DisarmTrapsSkill>();
  std::shared_ptr<DualWieldSkill> dual_wield = std::make_shared<DualWieldSkill>();
  std::shared_ptr<DungeoneeringSkill> dungeoneering = std::make_shared<DungeoneeringSkill>();
  std::shared_ptr<EscapeSkill> escape = std::make_shared<EscapeSkill>();
  std::shared_ptr<FishingSkill> fishing = std::make_shared<FishingSkill>();
  std::shared_ptr<FletcherySkill> fletchery = std::make_shared<FletcherySkill>();
  std::shared_ptr<ForagingSkill> foraging = std::make_shared<ForagingSkill>();
  std::shared_ptr<ForestLoreSkill> forest_lore = std::make_shared<ForestLoreSkill>();
  std::shared_ptr<HerbalismSkill> herbalism = std::make_shared<HerbalismSkill>();
  std::shared_ptr<HidingSkill> hiding = std::make_shared<HidingSkill>();
  std::shared_ptr<HuntingSkill> hunting = std::make_shared<HuntingSkill>();
  std::shared_ptr<IntimidationSkill> intimidation = std::make_shared<IntimidationSkill>();
  std::shared_ptr<JewelerSkill> jeweler = std::make_shared<JewelerSkill>();
  std::shared_ptr<JumpingSkill> jumping = std::make_shared<JumpingSkill>();
  std::shared_ptr<LeadershipSkill> leadership = std::make_shared<LeadershipSkill>();
  std::shared_ptr<LiteracySkill> literacy = std::make_shared<LiteracySkill>();
  std::shared_ptr<LoreSkill> lore = std::make_shared<LoreSkill>();
  std::shared_ptr<MagicGeneralSkill> magic = std::make_shared<MagicGeneralSkill>();
  std::shared_ptr<MarshLoreSkill> marsh_lore = std::make_shared<MarshLoreSkill>();
  std::shared_ptr<MedicineSkill> medicine = std::make_shared<MedicineSkill>();
  std::shared_ptr<MountainLoreSkill> mountain_lore = std::make_shared<MountainLoreSkill>();
  std::shared_ptr<MountaineeringSkill> mountaineering = std::make_shared<MountaineeringSkill>();
  std::shared_ptr<MusicSkill> music = std::make_shared<MusicSkill>();
  std::shared_ptr<NightSightSkill> night_sight = std::make_shared<NightSightSkill>();
  std::shared_ptr<OceanographySkill> oceanography = std::make_shared<OceanographySkill>();
  std::shared_ptr<PapercraftSkill> papercraft = std::make_shared<PapercraftSkill>();
  std::shared_ptr<ReligionSkill> religion = std::make_shared<ReligionSkill>();
  std::shared_ptr<ScribingSkill> scribing = std::make_shared<ScribingSkill>();
  std::shared_ptr<SkinningSkill> skinning = std::make_shared<SkinningSkill>();
  std::shared_ptr<SmithingSkill> smithing = std::make_shared<SmithingSkill>();
  std::shared_ptr<SpelunkingSkill> spelunking = std::make_shared<SpelunkingSkill>();
  std::shared_ptr<StealthSkill> stealth = std::make_shared<StealthSkill>();
  std::shared_ptr<SwimmingSkill> swimming = std::make_shared<SwimmingSkill>();
  std::shared_ptr<TanningSkill> tanning = std::make_shared<TanningSkill>();
  std::shared_ptr<ThieverySkill> thievery = std::make_shared<ThieverySkill>();
  std::shared_ptr<WeavingSkill> weaving = std::make_shared<WeavingSkill>();
  std::shared_ptr<AxesSkill> axes = std::make_shared<AxesSkill>();
  std::shared_ptr<ShortBladesSkill> short_blades = std::make_shared<ShortBladesSkill>();
  std::shared_ptr<LongBladesSkill> long_blades = std::make_shared<LongBladesSkill>();
  std::shared_ptr<BludgeonsSkill> bludgeons = std::make_shared<BludgeonsSkill>();
  std::shared_ptr<DaggersSkill> daggers = std::make_shared<DaggersSkill>();
  std::shared_ptr<RodsAndStavesSkill> rods_and_staves = std::make_shared<RodsAndStavesSkill>();
  std::shared_ptr<SpearsSkill> spears = std::make_shared<SpearsSkill>();
  std::shared_ptr<UnarmedSkill> unarmed = std::make_shared<UnarmedSkill>();
  std::shared_ptr<WhipsSkill> whips = std::make_shared<WhipsSkill>();
  std::shared_ptr<ExoticMeleeSkill> exotic = std::make_shared<ExoticMeleeSkill>();
  std::shared_ptr<ThrownAxesSkill> thrown_axes = std::make_shared<ThrownAxesSkill>();
  std::shared_ptr<ThrownBladesSkill> thrown_blades = std::make_shared<ThrownBladesSkill>();
  std::shared_ptr<ThrownBludgeonsSkill> thrown_bludgeons = std::make_shared<ThrownBludgeonsSkill>();
  std::shared_ptr<BowsSkill> bows = std::make_shared<BowsSkill>();
  std::shared_ptr<CrossbowsSkill> crossbows = std::make_shared<CrossbowsSkill>();
  std::shared_ptr<ThrownDaggersSkill> thrown_daggers = std::make_shared<ThrownDaggersSkill>();
  std::shared_ptr<RocksSkill> rocks = std::make_shared<RocksSkill>();
  std::shared_ptr<SlingsSkill> slings = std::make_shared<SlingsSkill>();
  std::shared_ptr<ThrownSpearsSkill> thrown_spears = std::make_shared<ThrownSpearsSkill>();
  std::shared_ptr<ExoticRangedSkill> thrown_exotic = std::make_shared<ExoticRangedSkill>();
  std::shared_ptr<ArcaneMagicSkill> arcane = std::make_shared<ArcaneMagicSkill>();
  std::shared_ptr<DivineMagicSkill> divine = std::make_shared<DivineMagicSkill>();
  std::shared_ptr<MysticMagicSkill> mystic = std::make_shared<MysticMagicSkill>();
  std::shared_ptr<PrimordialMagicSkill> primordial = std::make_shared<PrimordialMagicSkill>();

  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ARCHERY, archery));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_AWARENESS, awareness));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BARGAINING, bargaining));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BEASTMASTERY, beastmastery));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BLINDFIGHTING, blind_fighting));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BOATING, boating));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BOWYER, bowyer));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BREWING, brewing));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CANTRIPS, cantrips));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CARRYING, carrying));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_COMBAT, combat));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CRAFTING, crafting));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DESERT_LORE, desert_lore));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DETECTION, detection));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DISARM_TRAPS, disarm_traps));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DUAL_WIELD, dual_wield));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DUNGEONEERING, dungeoneering));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ESCAPE, escape));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FISHING, fishing));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FLETCHERY, fletchery));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FORAGING, foraging));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FOREST_LORE, forest_lore));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_HERBALISM, herbalism));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_HIDING, hiding));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_HUNTING, hunting));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_INTIMIDATION, intimidation));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_JEWELER, jeweler));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_JUMPING, jumping));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LEADERSHIP, leadership));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LITERACY, literacy));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LORE, lore));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MAGICGENERAL, magic));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MARSH_LORE, marsh_lore));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MEDICINE, medicine));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MOUNTAIN_LORE, mountain_lore));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MOUNTAINEERING, mountaineering));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MUSIC, music));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_NIGHT_SIGHT, night_sight));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_OCEANOGRAPHY, oceanography));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_PAPERCRAFT, papercraft));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_RELIGION, religion));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SCRIBING, scribing));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SKINNING, skinning));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SMITHING, smithing));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SPELUNKING, spelunking));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_STEALTH, stealth));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SWIMMING, swimming));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_TANNING, tanning));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THIEVERY, thievery));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_WEAVING, weaving));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_AXES, axes));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SHORT_BLADES, short_blades));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LONG_BLADES, long_blades));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BLUDGEONS, bludgeons));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DAGGERS, daggers));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_RODS_AND_STAVES, rods_and_staves));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SPEARS, spears));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_UNARMED, unarmed));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_WHIPS, whips));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_EXOTIC, exotic));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_AXES, thrown_axes));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_BLADES, thrown_blades));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_BLUDGEONS, thrown_bludgeons));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BOWS, bows));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CROSSBOWS, crossbows));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_DAGGERS, thrown_daggers));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ROCKS, rocks));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SLINGS, slings));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_SPEARS, thrown_spears));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_EXOTIC, thrown_exotic));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ARCANE, arcane));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DIVINE, divine));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MYSTIC, mystic));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_PRIMORDIAL, primordial));
}

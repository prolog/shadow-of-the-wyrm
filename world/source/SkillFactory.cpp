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
  static_assert(SkillType::SKILL_GENERAL_LAST == SkillType(50), "Unexpected SkillType::SKILL_GENERAL_LAST");

  skill_map.clear();

  std::unique_ptr<ArcherySkill> archery = std::make_unique<ArcherySkill>();
  std::unique_ptr<AwarenessSkill> awareness = std::make_unique<AwarenessSkill>();
  std::unique_ptr<BargainingSkill> bargaining = std::make_unique<BargainingSkill>();
  std::unique_ptr<BeastmasterySkill> beastmastery = std::make_unique<BeastmasterySkill>();
  std::unique_ptr<BlindFightingSkill> blind_fighting = std::make_unique<BlindFightingSkill>();
  std::unique_ptr<BoatingSkill> boating = std::make_unique<BoatingSkill>();
  std::unique_ptr<BowyerSkill> bowyer = std::make_unique<BowyerSkill>();
  std::unique_ptr<BrewingSkill> brewing = std::make_unique<BrewingSkill>();
  std::unique_ptr<CantripsSkill> cantrips = std::make_unique<CantripsSkill>();
  std::unique_ptr<CarryingSkill> carrying = std::make_unique<CarryingSkill>();
  std::unique_ptr<CombatSkill> combat = std::make_unique<CombatSkill>();
  std::unique_ptr<CraftingSkill> crafting = std::make_unique<CraftingSkill>();
  std::unique_ptr<DesertLoreSkill> desert_lore = std::make_unique<DesertLoreSkill>();
  std::unique_ptr<DetectionSkill> detection = std::make_unique<DetectionSkill>();
  std::unique_ptr<DisarmTrapsSkill> disarm_traps = std::make_unique<DisarmTrapsSkill>();
  std::unique_ptr<DualWieldSkill> dual_wield = std::make_unique<DualWieldSkill>();
  std::unique_ptr<DungeoneeringSkill> dungeoneering = std::make_unique<DungeoneeringSkill>();
  std::unique_ptr<EscapeSkill> escape = std::make_unique<EscapeSkill>();
  std::unique_ptr<FishingSkill> fishing = std::make_unique<FishingSkill>();
  std::unique_ptr<FletcherySkill> fletchery = std::make_unique<FletcherySkill>();
  std::unique_ptr<ForagingSkill> foraging = std::make_unique<ForagingSkill>();
  std::unique_ptr<ForestLoreSkill> forest_lore = std::make_unique<ForestLoreSkill>();
  std::unique_ptr<HerbalismSkill> herbalism = std::make_unique<HerbalismSkill>();
  std::unique_ptr<HidingSkill> hiding = std::make_unique<HidingSkill>();
  std::unique_ptr<HuntingSkill> hunting = std::make_unique<HuntingSkill>();
  std::unique_ptr<IntimidationSkill> intimidation = std::make_unique<IntimidationSkill>();
  std::unique_ptr<JewelerSkill> jeweler = std::make_unique<JewelerSkill>();
  std::unique_ptr<JumpingSkill> jumping = std::make_unique<JumpingSkill>();
  std::unique_ptr<LeadershipSkill> leadership = std::make_unique<LeadershipSkill>();
  std::unique_ptr<LiteracySkill> literacy = std::make_unique<LiteracySkill>();
  std::unique_ptr<LoreSkill> lore = std::make_unique<LoreSkill>();
  std::unique_ptr<MagicGeneralSkill> magic = std::make_unique<MagicGeneralSkill>();
  std::unique_ptr<MarshLoreSkill> marsh_lore = std::make_unique<MarshLoreSkill>();
  std::unique_ptr<MedicineSkill> medicine = std::make_unique<MedicineSkill>();
  std::unique_ptr<MountainLoreSkill> mountain_lore = std::make_unique<MountainLoreSkill>();
  std::unique_ptr<MusicSkill> music = std::make_unique<MusicSkill>();
  std::unique_ptr<NightSightSkill> night_sight = std::make_unique<NightSightSkill>();
  std::unique_ptr<OceanLoreSkill> ocean_lore = std::make_unique<OceanLoreSkill>();
  std::unique_ptr<PapercraftSkill> papercraft = std::make_unique<PapercraftSkill>();
  std::unique_ptr<ReligionSkill> religion = std::make_unique<ReligionSkill>();
  std::unique_ptr<ScribingSkill> scribing = std::make_unique<ScribingSkill>();
  std::unique_ptr<SkinningSkill> skinning = std::make_unique<SkinningSkill>();
  std::unique_ptr<SmithingSkill> smithing = std::make_unique<SmithingSkill>();
  std::unique_ptr<SpelunkingSkill> spelunking = std::make_unique<SpelunkingSkill>();
  std::unique_ptr<StealthSkill> stealth = std::make_unique<StealthSkill>();
  std::unique_ptr<SwimmingSkill> swimming = std::make_unique<SwimmingSkill>();
  std::unique_ptr<TanningSkill> tanning = std::make_unique<TanningSkill>();
  std::unique_ptr<ThieverySkill> thievery = std::make_unique<ThieverySkill>();
  std::unique_ptr<WandcraftSkill> wandcraft = std::make_unique<WandcraftSkill>();
  std::unique_ptr<WeavingSkill> weaving = std::make_unique<WeavingSkill>();
  std::unique_ptr<AxesSkill> axes = std::make_unique<AxesSkill>();
  std::unique_ptr<ShortBladesSkill> short_blades = std::make_unique<ShortBladesSkill>();
  std::unique_ptr<LongBladesSkill> long_blades = std::make_unique<LongBladesSkill>();
  std::unique_ptr<BludgeonsSkill> bludgeons = std::make_unique<BludgeonsSkill>();
  std::unique_ptr<DaggersSkill> daggers = std::make_unique<DaggersSkill>();
  std::unique_ptr<RodsAndStavesSkill> rods_and_staves = std::make_unique<RodsAndStavesSkill>();
  std::unique_ptr<SpearsSkill> spears = std::make_unique<SpearsSkill>();
  std::unique_ptr<UnarmedSkill> unarmed = std::make_unique<UnarmedSkill>();
  std::unique_ptr<WhipsSkill> whips = std::make_unique<WhipsSkill>();
  std::unique_ptr<ExoticMeleeSkill> exotic = std::make_unique<ExoticMeleeSkill>();
  std::unique_ptr<ThrownAxesSkill> thrown_axes = std::make_unique<ThrownAxesSkill>();
  std::unique_ptr<ThrownBladesSkill> thrown_blades = std::make_unique<ThrownBladesSkill>();
  std::unique_ptr<ThrownBludgeonsSkill> thrown_bludgeons = std::make_unique<ThrownBludgeonsSkill>();
  std::unique_ptr<BowsSkill> bows = std::make_unique<BowsSkill>();
  std::unique_ptr<CrossbowsSkill> crossbows = std::make_unique<CrossbowsSkill>();
  std::unique_ptr<ThrownDaggersSkill> thrown_daggers = std::make_unique<ThrownDaggersSkill>();
  std::unique_ptr<RocksSkill> rocks = std::make_unique<RocksSkill>();
  std::unique_ptr<SlingsSkill> slings = std::make_unique<SlingsSkill>();
  std::unique_ptr<ThrownSpearsSkill> thrown_spears = std::make_unique<ThrownSpearsSkill>();
  std::unique_ptr<ExoticRangedSkill> thrown_exotic = std::make_unique<ExoticRangedSkill>();
  std::unique_ptr<ArcaneMagicSkill> arcane = std::make_unique<ArcaneMagicSkill>();
  std::unique_ptr<DivineMagicSkill> divine = std::make_unique<DivineMagicSkill>();
  std::unique_ptr<MysticMagicSkill> mystic = std::make_unique<MysticMagicSkill>();
  std::unique_ptr<PrimordialMagicSkill> primordial = std::make_unique<PrimordialMagicSkill>();

  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ARCHERY, std::move(archery)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_AWARENESS, std::move(awareness)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BARGAINING, std::move(bargaining)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BEASTMASTERY, std::move(beastmastery)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BLINDFIGHTING, std::move(blind_fighting)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BOATING, std::move(boating)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BOWYER, std::move(bowyer)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BREWING, std::move(brewing)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CANTRIPS, std::move(cantrips)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CARRYING, std::move(carrying)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_COMBAT, std::move(combat)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CRAFTING, std::move(crafting)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DESERT_LORE, std::move(desert_lore)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DETECTION, std::move(detection)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DISARM_TRAPS, std::move(disarm_traps)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DUAL_WIELD, std::move(dual_wield)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DUNGEONEERING, std::move(dungeoneering)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ESCAPE, std::move(escape)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FISHING, std::move(fishing)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FLETCHERY, std::move(fletchery)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FORAGING, std::move(foraging)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_FOREST_LORE, std::move(forest_lore)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_HERBALISM, std::move(herbalism)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_HIDING, std::move(hiding)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_HUNTING, std::move(hunting)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_INTIMIDATION, std::move(intimidation)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_JEWELER, std::move(jeweler)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_JUMPING, std::move(jumping)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LEADERSHIP, std::move(leadership)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LITERACY, std::move(literacy)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LORE, std::move(lore)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MAGICGENERAL, std::move(magic)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MARSH_LORE, std::move(marsh_lore)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MEDICINE, std::move(medicine)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MOUNTAIN_LORE, std::move(mountain_lore)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MUSIC, std::move(music)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_NIGHT_SIGHT, std::move(night_sight)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_OCEAN_LORE, std::move(ocean_lore)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_PAPERCRAFT, std::move(papercraft)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_RELIGION, std::move(religion)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SCRIBING, std::move(scribing)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SKINNING, std::move(skinning)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SMITHING, std::move(smithing)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SPELUNKING, std::move(spelunking)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_STEALTH, std::move(stealth)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SWIMMING, std::move(swimming)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_TANNING, std::move(tanning)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THIEVERY, std::move(thievery)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_WANDCRAFT, std::move(wandcraft)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_WEAVING, std::move(weaving)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_AXES, std::move(axes)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SHORT_BLADES, std::move(short_blades)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_LONG_BLADES, std::move(long_blades)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BLUDGEONS, std::move(bludgeons)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DAGGERS, std::move(daggers)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_RODS_AND_STAVES, std::move(rods_and_staves)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SPEARS, std::move(spears)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_UNARMED, std::move(unarmed)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_WHIPS, std::move(whips)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_EXOTIC, std::move(exotic)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_AXES, std::move(thrown_axes)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_BLADES, std::move(thrown_blades)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_BLUDGEONS, std::move(thrown_bludgeons)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_BOWS, std::move(bows)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_CROSSBOWS, std::move(crossbows)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_DAGGERS, std::move(thrown_daggers)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ROCKS, std::move(rocks)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_SLINGS, std::move(slings)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_SPEARS, std::move(thrown_spears)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_THROWN_EXOTIC, std::move(thrown_exotic)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_ARCANE, std::move(arcane)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_DIVINE, std::move(divine)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_MYSTIC, std::move(mystic)));
  skill_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILL_PRIMORDIAL, std::move(primordial)));
}

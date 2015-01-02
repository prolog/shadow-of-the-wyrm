#include "XMLSkillsReaders.hpp"

// XMLSkillsReader
Skills XMLSkillsReader::get_skills(const XMLNode& skills_node)
{
  Skills skills;

  XMLNode general_skills_node = XMLUtils::get_next_element_by_local_name(skills_node, "GeneralSkills");
  XMLNode weapon_skills_node = XMLUtils::get_next_element_by_local_name(skills_node, "WeaponSkills");
  XMLNode ranged_weapon_skills_node = XMLUtils::get_next_element_by_local_name(skills_node, "RangedWeaponSkills");
  XMLNode magic_skills_node = XMLUtils::get_next_element_by_local_name(skills_node, "MagicSkills");

  general_skills_reader.parse_general_skills(skills, general_skills_node);
  weapon_skills_reader.parse_weapon_skills(skills, weapon_skills_node);
  ranged_weapon_skills_reader.parse_ranged_weapon_skills(skills, ranged_weapon_skills_node);
  magic_skills_reader.parse_magic_skills(skills, magic_skills_node);

  return skills;
}

// XMLGeneralSkillsReader
void XMLGeneralSkillsReader::parse_general_skills(Skills& skills, const XMLNode& general_skills_node)
{
  if (!general_skills_node.is_null())
  {
    int archery_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Archery");
    int awareness_value        = XMLUtils::get_child_node_int_value(general_skills_node, "Awareness");
    int bargaining_value       = XMLUtils::get_child_node_int_value(general_skills_node, "Bargaining");
    int beastmastery_value     = XMLUtils::get_child_node_int_value(general_skills_node, "Beastmastery");
    int blind_fighting_value   = XMLUtils::get_child_node_int_value(general_skills_node, "BlindFighting");
    int boating_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Boating");
    int bowyer_value           = XMLUtils::get_child_node_int_value(general_skills_node, "Bowyer");
    int brewing_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Brewing");
    int cantrips_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Cantrips");
    int carrying_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Carrying");
    int combat_value           = XMLUtils::get_child_node_int_value(general_skills_node, "Combat");
    int crafting_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Crafting");
    int desert_lore_value      = XMLUtils::get_child_node_int_value(general_skills_node, "DesertLore");
    int detection_value        = XMLUtils::get_child_node_int_value(general_skills_node, "Detection");
    int disarm_traps_value     = XMLUtils::get_child_node_int_value(general_skills_node, "DisarmTraps");
    int dual_wield_value       = XMLUtils::get_child_node_int_value(general_skills_node, "DualWield");
    int dungeoneering_value    = XMLUtils::get_child_node_int_value(general_skills_node, "Dungeoneering");
    int escape_value           = XMLUtils::get_child_node_int_value(general_skills_node, "Escape");
    int fishing_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Fishing");
    int fletchery_value        = XMLUtils::get_child_node_int_value(general_skills_node, "Fletchery");
    int foraging_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Foraging");
    int forest_lore_value      = XMLUtils::get_child_node_int_value(general_skills_node, "ForestLore");
    int herbalism_value        = XMLUtils::get_child_node_int_value(general_skills_node, "Herbalism");
    int hiding_value           = XMLUtils::get_child_node_int_value(general_skills_node, "Hiding");
    int hunting_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Hunting");
    int intimidation_value     = XMLUtils::get_child_node_int_value(general_skills_node, "Intimidation");
    int jeweler_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Jeweler");
    int jumping_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Jumping");
    int leadership_value       = XMLUtils::get_child_node_int_value(general_skills_node, "Leadership");
    int literacy_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Literacy");
    int lore_value             = XMLUtils::get_child_node_int_value(general_skills_node, "Lore");
    int magic_value            = XMLUtils::get_child_node_int_value(general_skills_node, "Magic");
    int marsh_lore_value       = XMLUtils::get_child_node_int_value(general_skills_node, "MarshLore");
    int medicine_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Medicine");
    int mountain_lore_value    = XMLUtils::get_child_node_int_value(general_skills_node, "MountainLore");
    int mountaineering_value   = XMLUtils::get_child_node_int_value(general_skills_node, "Mountaineering");
    int music_value            = XMLUtils::get_child_node_int_value(general_skills_node, "Music");
    int night_sight_value      = XMLUtils::get_child_node_int_value(general_skills_node, "NightSight");
    int oceanography_value     = XMLUtils::get_child_node_int_value(general_skills_node, "Oceanography");
    int papercraft_value       = XMLUtils::get_child_node_int_value(general_skills_node, "Papercraft");
    int religion_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Religion");
    int scribing_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Scribing");
    int skinning_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Skinning");
    int smithing_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Smithing");
    int spelunking_value       = XMLUtils::get_child_node_int_value(general_skills_node, "Spelunking");
    int stealth_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Stealth");
    int swimming_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Swimming");
    int tanning_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Tanning");
    int thievery_value         = XMLUtils::get_child_node_int_value(general_skills_node, "Thievery");
    int weaving_value          = XMLUtils::get_child_node_int_value(general_skills_node, "Weaving");

    skills.set_value(SkillType::SKILL_GENERAL_ARCHERY, archery_value);
    skills.set_value(SkillType::SKILL_GENERAL_AWARENESS, awareness_value);
    skills.set_value(SkillType::SKILL_GENERAL_BARGAINING, bargaining_value);
    skills.set_value(SkillType::SKILL_GENERAL_BEASTMASTERY, beastmastery_value);
    skills.set_value(SkillType::SKILL_GENERAL_BLIND_FIGHTING, blind_fighting_value);
    skills.set_value(SkillType::SKILL_GENERAL_BOATING, boating_value);
    skills.set_value(SkillType::SKILL_GENERAL_BOWYER, bowyer_value);
    skills.set_value(SkillType::SKILL_GENERAL_BREWING, brewing_value);
    skills.set_value(SkillType::SKILL_GENERAL_CANTRIPS, cantrips_value);
    skills.set_value(SkillType::SKILL_GENERAL_CARRYING, carrying_value);
    skills.set_value(SkillType::SKILL_GENERAL_COMBAT, combat_value);
    skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, crafting_value);
    skills.set_value(SkillType::SKILL_GENERAL_DESERT_LORE, desert_lore_value);
    skills.set_value(SkillType::SKILL_GENERAL_DETECTION, detection_value);
    skills.set_value(SkillType::SKILL_GENERAL_DISARM_TRAPS, disarm_traps_value);
    skills.set_value(SkillType::SKILL_GENERAL_DUAL_WIELD, dual_wield_value);
    skills.set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, dungeoneering_value);
    skills.set_value(SkillType::SKILL_GENERAL_ESCAPE, escape_value);
    skills.set_value(SkillType::SKILL_GENERAL_FISHING, fishing_value);
    skills.set_value(SkillType::SKILL_GENERAL_FLETCHERY, fletchery_value);
    skills.set_value(SkillType::SKILL_GENERAL_FORAGING, foraging_value);
    skills.set_value(SkillType::SKILL_GENERAL_FOREST_LORE, forest_lore_value);
    skills.set_value(SkillType::SKILL_GENERAL_HERBALISM, herbalism_value);
    skills.set_value(SkillType::SKILL_GENERAL_HIDING, hiding_value);
    skills.set_value(SkillType::SKILL_GENERAL_HUNTING, hunting_value);
    skills.set_value(SkillType::SKILL_GENERAL_INTIMIDATION, intimidation_value);
    skills.set_value(SkillType::SKILL_GENERAL_JEWELER, jeweler_value);
    skills.set_value(SkillType::SKILL_GENERAL_JUMPING, jumping_value);
    skills.set_value(SkillType::SKILL_GENERAL_LEADERSHIP, leadership_value);
    skills.set_value(SkillType::SKILL_GENERAL_LITERACY, literacy_value);
    skills.set_value(SkillType::SKILL_GENERAL_LORE, lore_value);
    skills.set_value(SkillType::SKILL_GENERAL_MAGIC, magic_value);
    skills.set_value(SkillType::SKILL_GENERAL_MARSH_LORE, marsh_lore_value);
    skills.set_value(SkillType::SKILL_GENERAL_MEDICINE, medicine_value);
    skills.set_value(SkillType::SKILL_GENERAL_MOUNTAIN_LORE, mountain_lore_value);
    skills.set_value(SkillType::SKILL_GENERAL_MOUNTAINEERING, mountaineering_value);
    skills.set_value(SkillType::SKILL_GENERAL_MUSIC, music_value);
    skills.set_value(SkillType::SKILL_GENERAL_NIGHT_SIGHT, night_sight_value);
    skills.set_value(SkillType::SKILL_GENERAL_OCEANOGRAPHY, oceanography_value);
    skills.set_value(SkillType::SKILL_GENERAL_PAPERCRAFT, papercraft_value);
    skills.set_value(SkillType::SKILL_GENERAL_RELIGION, religion_value);
    skills.set_value(SkillType::SKILL_GENERAL_SCRIBING, scribing_value);
    skills.set_value(SkillType::SKILL_GENERAL_SKINNING, skinning_value);
    skills.set_value(SkillType::SKILL_GENERAL_SMITHING, smithing_value);
    skills.set_value(SkillType::SKILL_GENERAL_SPELUNKING, spelunking_value);
    skills.set_value(SkillType::SKILL_GENERAL_STEALTH, stealth_value);
    skills.set_value(SkillType::SKILL_GENERAL_SWIMMING, swimming_value);
    skills.set_value(SkillType::SKILL_GENERAL_TANNING, tanning_value);
    skills.set_value(SkillType::SKILL_GENERAL_THIEVERY, thievery_value);
    skills.set_value(SkillType::SKILL_GENERAL_WEAVING, weaving_value);
  }
}

// XMLWeaponSkillsReader
void XMLWeaponSkillsReader::parse_weapon_skills(Skills& skills, const XMLNode& weapon_skills_node)
{
  if (!weapon_skills_node.is_null())
  {
    int axes_value            = XMLUtils::get_child_node_int_value(weapon_skills_node, "Axes");
    int short_blades_value    = XMLUtils::get_child_node_int_value(weapon_skills_node, "ShortBlades");
    int long_blades_value     = XMLUtils::get_child_node_int_value(weapon_skills_node, "LongBlades");
    int bludgeons_value       = XMLUtils::get_child_node_int_value(weapon_skills_node, "Bludgeons");
    int daggers_value         = XMLUtils::get_child_node_int_value(weapon_skills_node, "Daggers");
    int rods_and_staves_value = XMLUtils::get_child_node_int_value(weapon_skills_node, "RodsAndStaves");
    int spears_value          = XMLUtils::get_child_node_int_value(weapon_skills_node, "Spears");
    int unarmed_value         = XMLUtils::get_child_node_int_value(weapon_skills_node, "Unarmed");
    int whips_value           = XMLUtils::get_child_node_int_value(weapon_skills_node, "Whips");

    skills.set_value(SkillType::SKILL_MELEE_AXES, axes_value);
    skills.set_value(SkillType::SKILL_MELEE_SHORT_BLADES, short_blades_value);
    skills.set_value(SkillType::SKILL_MELEE_LONG_BLADES, long_blades_value);
    skills.set_value(SkillType::SKILL_MELEE_BLUDGEONS, bludgeons_value);
    skills.set_value(SkillType::SKILL_MELEE_DAGGERS, daggers_value);
    skills.set_value(SkillType::SKILL_MELEE_RODS_AND_STAVES, rods_and_staves_value);
    skills.set_value(SkillType::SKILL_MELEE_SPEARS, spears_value);
    skills.set_value(SkillType::SKILL_MELEE_UNARMED, unarmed_value);
    skills.set_value(SkillType::SKILL_MELEE_WHIPS, whips_value);
  }
}

// XMLRangedWeaponSkillsReader
void XMLRangedWeaponSkillsReader::parse_ranged_weapon_skills(Skills& skills, const XMLNode& ranged_weapon_skills_node)
{
  if (!ranged_weapon_skills_node.is_null())
  {
    int axes_value      = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Axes");
    int blades_value    = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Blades");
    int bludgeons_value = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Bludgeons");
    int bows_value      = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Bows");
    int crossbows_value = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Crossbows");
    int daggers_value   = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Daggers");
    int rocks_value     = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Rocks");
    int slings_value    = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Slings");
    int spears_value    = XMLUtils::get_child_node_int_value(ranged_weapon_skills_node, "Spears");

    skills.set_value(SkillType::SKILL_RANGED_AXES, axes_value);
    skills.set_value(SkillType::SKILL_RANGED_BLADES, blades_value);
    skills.set_value(SkillType::SKILL_RANGED_BLUDGEONS, bludgeons_value);
    skills.set_value(SkillType::SKILL_RANGED_BOWS, bows_value);
    skills.set_value(SkillType::SKILL_RANGED_CROSSBOWS, crossbows_value);
    skills.set_value(SkillType::SKILL_RANGED_DAGGERS, daggers_value);
    skills.set_value(SkillType::SKILL_RANGED_ROCKS, rocks_value);
    skills.set_value(SkillType::SKILL_RANGED_SLINGS, slings_value);
    skills.set_value(SkillType::SKILL_RANGED_SPEARS, spears_value);
  }
}

// XMLMagicSkillsReader
void XMLMagicSkillsReader::parse_magic_skills(Skills& skills, const XMLNode& magic_skills_node)
{
  if (!magic_skills_node.is_null())
  {
    int arcane_value = XMLUtils::get_child_node_int_value(magic_skills_node, "Arcane");
    int divine_value = XMLUtils::get_child_node_int_value(magic_skills_node, "Divine");
    int mystic_value = XMLUtils::get_child_node_int_value(magic_skills_node, "Mystic");
    int primordial_value = XMLUtils::get_child_node_int_value(magic_skills_node, "Primordial");

    skills.set_value(SkillType::SKILL_MAGIC_ARCANE, arcane_value);
    skills.set_value(SkillType::SKILL_MAGIC_DIVINE, divine_value);
    skills.set_value(SkillType::SKILL_MAGIC_MYSTIC, mystic_value);
    skills.set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, primordial_value);
  }
}


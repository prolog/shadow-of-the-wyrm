require('level')

-- NPCs get an extra d6 HP and AP per level, and get those stats restored.
local function npc_gain_hp_ap(creature_id)
  local lvl_hp = RNG_range(1,6)
  local lvl_ap = RNG_range(1,6)

  local base_hp = get_creature_base_hp(creature_id)
  local base_ap = get_creature_base_ap(creature_id)

  local cur_hp = get_creature_current_hp(creature_id)
  local cur_ap = get_creature_current_ap(creature_id)

  -- NPCs get their HP and AP restored when they level.
  -- Life's not fair.
  base_hp = base_hp + lvl_hp
  base_ap = base_ap + lvl_ap

  set_creature_base_hp(creature_id, base_hp)
  set_creature_current_hp(creature_id, base_hp)
  set_creature_base_ap(creature_id, base_ap)
  set_creature_current_ap(creature_id, base_ap)
end

-- Creatures get an extra d2 damage per level
local function npc_gain_damage(creature_id)
  local ndice, dsides, modifier = get_creature_base_damage(creature_id)
  dsides = dsides + 2
  set_creature_base_damage(creature_id, ndice, dsides, modifier)
end

-- Ignore witchling spells - these will be automatically gained by witchling
-- NPCs as part of the class scripts.
local function npc_gain_spells(creature_id, level)
  local no_spell_specified = ""
  local castings = math.max(4, level / 2)
  
  local t_skills = get_trained_magic_skills(creature_id)

  local spell = {CSKILL_MAGIC_CANTRIPS = {"c_02_flame_dart", "c_05_spirit_bolt", "c_09_force_bolt", "c_11_blast"},
                 CSKILL_MAGIC_ARCANE = {"a_01_wreath_of_fire", "a_02_dragon_breath", "a_03_lightning_bolt", "a_04_shockwave", "a_06_cross_of_flame", "a_07_fireball", "a_09_frost_bolt", "a_15_vorpal_bolt"},
                 CSKILL_MAGIC_DIVINE = {"d_02_smite", "d_10_radiant_beam"},
                 CSKILL_MAGIC_MYSTIC = {"m_02_poison", "m_03_blind", "m_05_spellbind", "m_08_stone"}}

  for i,v in t_skills do
    local spell_list = spells[v]
    local spell_id = spell_list[RNG_range(1, #spell_list)]

    add_spell_castings(creature_id, spell_id, RNG_range(3, 8))
  end
end

local function npc_level_gain_fn(creature_id, level)
  if level > 1 then
    npc_gain_hp_ap(creature_id)
    npc_gain_damage(creature_id)
    npc_gain_spells(creature_id, level)

    add_npc_level_message(creature_id)
  end
end

local npc_lvl_fn = npc_level_gain_fn

level.set_misc_gain_level_fn("_npc", npc_lvl_fn)


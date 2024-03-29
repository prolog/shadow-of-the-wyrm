require('constants')
require('level')

local function witchling_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_int(creature_id, is_player(creature_id))
  end
end

local function witchling_level_fn(creature_id, lvl)
  -- Witchlings always recognize their own, and form kind of a loose
  -- association.
  if lvl == 1 then
    add_membership(creature_id, WITCHLINGS_MEMBERSHIP_ID, "WITCHLINGS_MEMBERSHIP_SID")
  end

  -- Always add castings of Shadow Flame
  add_spell_castings(creature_id, "p_01_shadow_flame", get_primordial_castings(creature_id, 2 * lvl))

  -- Always add castings of Curse of Shadows
  add_spell_castings(creature_id, "p_02_curse_of_shadows", get_primordial_castings(creature_id, 1.25 * lvl))

  -- Add Cloak of Shadows at level 3.
  if (lvl >= 3) then
    add_spell_castings(creature_id, "p_03_cloak_of_shadows", get_primordial_castings(creature_id, 1.25 * lvl))
  end

  -- Start adding castings of Nether Bolt at level 5.
  if (lvl >= 5) then
    add_spell_castings(creature_id, "p_04_nether_bolt", get_primordial_castings(creature_id, lvl))
  end

  -- Start adding castings of Chaos Aura at level 13.
  if (lvl >= 13) then
    add_spell_castings(creature_id, "p_05_chaos_aura", get_primordial_castings(creature_id, lvl))
  end

  -- Start adding castings of Nightfire at level 20.
  if (lvl >= 20) then
    add_spell_castings(creature_id, "p_06_nightfire", get_primordial_castings(creature_id, lvl / 2))
  end

  -- Start adding castings of Umbra at level 26.
  if (lvl >= 26) then
    add_spell_castings(creature_id, "p_07_umbra", get_primordial_castings(creature_id, lvl / 2))
  end
 
  -- Start adding castings of Veil of Shadows at level 35.
  if (lvl >= 35) then
    add_spell_castings(creature_id, "p_08_veil_of_shadows", get_primordial_castings(creature_id, lvl / 2))
  end
end

-- Set up the class level function for Witchlings.
local w_fn = witchling_level_fn
local w_stat_fn = witchling_stat_gain_fn

level.set_class_level_fn("witchling", w_fn)
level.set_class_stat_gain_level_fn("witchling", w_stat_fn)


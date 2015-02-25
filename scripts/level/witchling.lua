require('level')

local function witchling_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_int(creature_id, is_player(creature_id))
  end
end

local function witchling_level_fn(creature_id, lvl)
  -- Always add castings of Shadow Flame
  add_spell_castings(creature_id, "p_01_shadow_flame", 4 * lvl)

  -- Always add castings of Curse of Shadows
  add_spell_castings(creature_id, "p_02_curse_of_shadows", 3 * lvl)

  -- Add Cloak of Shadows at level 3.
  if (lvl >= 3) then
    add_spell_castings(creature_id, "p_03_cloak_of_shadows", 3 * lvl)
  end

  -- Start adding castings of Nether Bolt at level 5.
  if (lvl >= 5) then
    add_spell_castings(creature_id, "p_04_nether_bolt", 2 * lvl)
  end

  -- Start adding castings of Chaos Aura at level 13.
  if (lvl >= 13) then
    add_spell_castings(creature_id, "p_05_chaos_aura", 2 * lvl)
  end

  -- Start adding castings of Nightfire at level 20.
  if (lvl >= 20) then
    add_spell_castings(creature_id, "p_06_nightfire", lvl)
  end

  -- Start adding castings of Veil of Shadows at level 35.
  if (lvl >= 35) then
    add_spell_castings(creature_id, "p_07_veil_of_shadows", lvl)
  end
end

-- Set up the class level function for Witchlings.
local w_fn = witchling_level_fn
local w_stat_fn = witchling_stat_gain_fn

level.set_class_level_fn("witchling", w_fn)
level.set_class_stat_gain_level_fn("witchling", w_stat_fn)


require('level')

-- Sages require intelligence and willpower to command all spheres of
-- magic.
local function sage_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 5 == 0 then
    incr_int(creature_id, is_pl)
    incr_wil(creature_id, is_pl)
  end
end

-- Sages learn primordial spells, but at a slower rate than witchlings,
-- and don't have access to the most powerful spells. 
local function sage_level_fn(creature_id, lvl)
  
  -- Sages start with shadow flame, and gain fewer castings.
  add_spell_castings(creature_id, "p_01_shadow_flame", 2 * lvl)

  -- Start adding castings of Nether Bolt at level 10.
  if (lvl >= 10) then
    add_spell_castings(creature_id, "p_02_nether_bolt", lvl)
  end

  -- Start adding castings of Chaos Aura at level 25.
  if (lvl >= 25) then
    add_spell_castings(creature_id, "p_03_chaos_aura", lvl)
  end

  -- Start adding castings of Nightfire at level 40.
  if (lvl >= 40) then
    add_spell_castings(creature_id, "p_04_nightfire", lvl * 0.5)
  end
end

-- Set up the sage functions.
local sage_class_stat_fn = sage_stat_gain_fn
local sage_fn = sage_level_fn

level.set_class_stat_gain_level_fn("sage", sage_class_stat_fn)
level.set_class_level_fn("sage", sage_fn)

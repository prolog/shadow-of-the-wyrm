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
  add_spell_castings(creature_id, "p_01_shadow_flame", get_primordial_castings(creature_id, 1.5 * lvl))

  -- Sages can protect themselves against shadow damage at level 6.
  if (lvl >= 6) then
    add_spell_castings(creature_id, "p_03_cloak_of_shadows", get_primordial_castings(creature_id, lvl))
  end

  -- Sages don't get Curse of Shadows - that's only for Witchlings, to
  -- make them most effective at dealing shadow damage.

  -- Start adding castings of Nether Bolt at level 10.
  if (lvl >= 10) then
    add_spell_castings(creature_id, "p_04_nether_bolt", get_primordial_castings(creature_id, lvl * 0.75))
  end

  -- Start adding castings of Chaos Aura at level 25.
  if (lvl >= 25) then
    add_spell_castings(creature_id, "p_05_chaos_aura", get_primordial_castings(creature_id, lvl * 0.75))
  end

  -- Start adding castings of Nightfire at level 40.
  if (lvl >= 40) then
    add_spell_castings(creature_id, "p_06_nightfire", get_primordial_castings(creature_id, lvl * 0.5))
  end
end

-- Set up the sage functions.
local sage_class_stat_fn = sage_stat_gain_fn
local sage_fn = sage_level_fn

level.set_class_stat_gain_level_fn("sage", sage_class_stat_fn)
level.set_class_level_fn("sage", sage_fn)

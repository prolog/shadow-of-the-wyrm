require('class_level')

local function witchling_level_fn(creature_id, level)
  -- Always add castings of Shadow Flame
  add_spell_castings(creature_id, "p_01_shadow_flame", 4 * level)

  -- Start adding castings of Nether Bolt at level 5.
  if (level >= 5) then
    add_spell_castings(creature_id, "p_02_nether_bolt", 2 * level)
  end

  -- Start adding castings of Chaos Aura at level 13.
  if (level >= 13) then
    add_spell_castings(creature_id, "p_03_chaos_aura", 2 * level)
  end

  -- Start adding castings of Nightfire at level 20.
  if (level >= 20) then
    add_spell_castings(creature_id, "p_04_nightfire", level)
  end

  -- Start adding castings of Veil of Shadows at level 35.
  if (level >= 35) then
    add_spell_castings(creature_id, "p_05_veil_of_shadows", level)
  end
end

-- Set up the class level function for Witchlings.
local w_fn = witchling_level_fn
class_level.set_class_level_fn("witchling", w_fn)


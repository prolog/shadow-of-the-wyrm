require('level')

-- Creatures get an extra d2 damage per level
local function npc_gain_damage(creature_id)
  local ndice, dsides, modifier = get_creature_base_damage(creature_id)
  dsides = dsides + 2
  set_creature_base_damage(creature_id, ndice, dsides, modifier)
end

local function npc_level_gain_fn(creature_id, level)
  if level > 1 then
    npc_gain_damage(creature_id)
    add_npc_level_message(creature_id)
  end
end

local npc_lvl_fn = npc_level_gain_fn

level.set_misc_gain_level_fn("_npc", npc_lvl_fn)


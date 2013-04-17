require('class_level')

local function witchling_level_fn(creature_id, level)
  -- Always add castings of Shadow Flame
  add_spell_castings(creature_id, "p_01_shadow_flame", 4 * level)
end

-- Set up the class level function for Witchlings.
local w_fn = witchling_level_fn
class_level.set_class_level_fn("witchling", w_fn)


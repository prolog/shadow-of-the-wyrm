require('class_level')

local function pugilist_level_fn(creature_id, level)
  set_creature_base_damage(creature_id, 1, 2 * level)
end

-- Set up the pugilist class function.
local pugilist_fn = pugilist_level_fn
class_level.set_class_level_fn("pugilist", pugilist_fn)


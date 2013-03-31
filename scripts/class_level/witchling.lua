require('class_level')

local function witchling_level_fn(creature_id, level)
  if level == 1 then
    -- For testing only - change this once magic is implemented!
    -- set_skill_value(creature_id, 31, 50)
  end
end

-- Set up the class level function for Witchlings.
local w_fn = witchling_level_fn
class_level.set_class_level_fn("witchling", w_fn)


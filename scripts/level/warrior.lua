require('level')

-- Weak warriors don't live long.
local function warrior_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_str(creature_id, is_player(creature_id))
  end
end

-- Set up the warrior functions.
local warrior_class_stat_fn = warrior_stat_gain_fn

level.set_class_stat_gain_level_fn("warrior", warrior_class_stat_fn)


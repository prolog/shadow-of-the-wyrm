require('level')

-- Rovers live off the land, and gain a sixth sense about danger that
-- keeps them alive.
local function rover_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_agi(creature_id, is_player(creature_id))
  end
end

-- Set up the rover functions.
local rover_class_stat_fn = rover_stat_gain_fn

level.set_class_stat_gain_level_fn("rover", rover_class_stat_fn)


require('class_level')

-- -1 speed for every 5 lvls
local function thief_level_fn(creature_id, level)
  if level % 5 == 0 then
    set_creature_speed(creature_id, get_creature_speed(creature_id) - 1)
    
    if is_player(creature_id) then
      add_message("STATISTIC_GAIN_SPEED")
    end
  end
end

-- Set up the levelling fn for thieves.
local thief_fn = thief_level_fn
class_level.set_class_level_fn("thief", thief_fn)


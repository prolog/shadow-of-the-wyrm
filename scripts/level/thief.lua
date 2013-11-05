require('level')

local function thief_class_stat_gain_fn(creature_id, lvl)
  if lvl % 5 == 0 then
    incr_agi(creature_id, is_player(creature_id))
  end
end

-- -1 speed for every 5 lvls
local function thief_level_fn(creature_id, lvl)
  if lvl % 5 == 0 then
    set_creature_speed(creature_id, get_creature_speed(creature_id) - 1)
    
    if is_player(creature_id) then
      add_message("STATISTIC_GAIN_SPEED")
    end
  end
end

-- Set up the levelling fns for thieves.
local thief_fn = thief_level_fn
local thief_class_stat_fn = thief_class_stat_gain_fn

level.set_class_level_fn("thief", thief_fn)
level.set_class_stat_gain_level_fn("thief", thief_class_stat_fn)


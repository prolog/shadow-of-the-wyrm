require('level')

-- Hardy men and women of the sea, they are able to weather storms better
-- than most.
local function seafarer_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_hea(creature_id, is_player(creature_id))
  end
end

-- Set up the seafarer functions.
local seafarer_class_stat_fn = seafarer_stat_gain_fn

level.set_class_stat_gain_level_fn("seafarer", seafarer_class_stat_fn)


require('level')

-- Devotion to their deity under arduous conditions grants pilgrims
-- an ever-increasing source of will.
local function pilgrim_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_wil(creature_id, is_player(creature_id))
  end
end

-- Set up the pilgrim functions.
local pilgrim_class_stat_fn = pilgrim_stat_gain_fn

level.set_class_stat_gain_level_fn("pilgrim", pilgrim_stat_gain_fn)


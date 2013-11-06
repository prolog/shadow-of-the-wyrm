require('level')

-- Shepherds are able to make the most of their small lot in life.
local function shepherd_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_wil(creature_id, is_player(creature_id))
  end
end

-- Set up the shepherd functions.
local shepherd_class_stat_fn = shepherd_stat_gain_fn

level.set_class_stat_gain_level_fn("shepherd", shepherd_class_stat_fn)


require('level')

local function giant_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
      incr_str(creature_id, is_pl)
  end
end

local giant_race_stat_fn = giant_stat_gain_fn

level.set_race_stat_gain_level_fn("09_giant", giant_race_stat_fn)


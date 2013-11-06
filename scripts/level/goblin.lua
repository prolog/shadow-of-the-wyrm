require('level')

local function goblin_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
      incr_agi(creature_id, is_pl)
  end
end

local goblin_race_stat_fn = goblin_stat_gain_fn

level.set_race_stat_gain_level_fn("07_goblin", goblin_race_stat_fn)


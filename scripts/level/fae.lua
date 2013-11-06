require('level')

local function fae_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
      incr_int(creature_id, is_pl)
      incr_wil(creature_id, is_pl)
  end
end

local fae_race_stat_fn = fae_stat_gain_fn

level.set_race_stat_gain_level_fn("05_fae", fae_race_stat_fn)


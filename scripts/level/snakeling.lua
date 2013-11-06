require('level')

local function snakeling_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
    if RNG_percent_chance(50) then
      incr_int(creature_id, is_pl)
    else
      incr_agi(creature_id, is_pl)
    end
  end
end

local snakeling_race_stat_fn = snakeling_stat_gain_fn

level.set_race_stat_gain_level_fn("04_snakeling", snakeling_race_stat_fn)


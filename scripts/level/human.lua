require('level')

local function human_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
    local stat = RNG_range(1, 3)

    -- One of str, dex, agi
    if stat == 1 then
      incr_str(creature_id, is_pl)
    elseif stat == 2 then
      incr_dex(creature_id, is_pl)
    else
      incr_agi(creature_id, is_pl)
    end

    stat = RNG_range(1, 3)

    -- One of int, wil, cha
    if stat == 1 then
      incr_int(creature_id, is_pl)
    elseif stat == 2 then
      incr_wil(creature_id, is_pl)
    else
      incr_cha(creature_id, is_pl)
    end
  end
end

local human_race_stat_fn = human_stat_gain_fn

level.set_race_stat_gain_level_fn("01_human", human_race_stat_fn)


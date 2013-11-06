require('level')

local function gnome_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)
  local stat = RNG_range(1, 3)

  if level % 7 == 0 then
    if stat == 1 then
      incr_int(creature_id, is_pl)
    elseif stat == 2 then
      incr_wil(creature_id, is_pl)
    else
      incr_agi(creature_id, is_pl)
    end
  end
end

local gnome_race_stat_fn = gnome_stat_gain_fn

level.set_race_stat_gain_level_fn("10_gnome", gnome_race_stat_fn)


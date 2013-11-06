require('level')

local function dwarf_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
      if RNG_percent_chance(50) then
        incr_str(creature_id, is_pl)
      else
        incr_hea(creature_id, is_pl)
      end
  end
end

local dwarf_race_stat_fn = dwarf_stat_gain_fn

level.set_race_stat_gain_level_fn("06_dwarf", dwarf_race_stat_fn)


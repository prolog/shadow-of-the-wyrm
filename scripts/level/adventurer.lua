require('level')

-- Adventurers aren't as specialized as other classes, such as warriors,
-- witchlings, etc.  This is a real disadvantage in some aspects, but is
-- made up for slightly by the fact that, ceteris parabus, the adventurer
-- is expected to have higher stats at game's end.
local function adventurer_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 5 == 0 then
    if RNG_percent_chance(50) then
      incr_str(creature_id, is_pl)
    end

    if RNG_percent_chance(50) then
      incr_hea(creature_id, is_pl)
    end

    incr_dex(creature_id, is_pl)
  end
end

-- Set up the adventurer class functions.
local adventurer_class_stat_fn = adventurer_stat_gain_fn

level.set_class_stat_gain_level_fn("adventurer", adventurer_class_stat_fn)


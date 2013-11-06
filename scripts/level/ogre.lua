require('level')

local function ogre_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 7 == 0 then
      incr_str(creature_id, is_pl)
  end
end

local ogre_race_stat_fn = ogre_stat_gain_fn

level.set_race_stat_gain_level_fn("08_ogre", ogre_race_stat_fn)


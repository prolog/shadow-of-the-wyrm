require('level')

local function pugilist_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_str(creature_id, is_player(creature_id))
  end
end

local function pugilist_level_fn(creature_id, level)
  set_creature_base_damage(creature_id, 1, 2 * level)
end

-- Set up the pugilist class functions.
local pugilist_fn = pugilist_level_fn
local pugilist_class_stat_fn = pugilist_stat_gain_fn

level.set_class_stat_gain_level_fn("pugilist", pugilist_stat_gain_fn)
level.set_class_level_fn("pugilist", pugilist_fn)


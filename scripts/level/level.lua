module(..., package.seeall)

-- The class functions, used to add new abilities, etc.
class_fns = {}

-- Class-based stat gain functions.
class_stat_gain_fns = {}

-- Race-based stat gain functions.
race_stat_gain_fns = {}

-- Other gain fns
misc_gain_fns = {}

local npc_fn_key = "_npc"

-- Set a particular level function - this is called by the class-specific
-- .lua scripts.
function set_class_level_fn(class_id, fn)
  class_fns[class_id] = fn
end

-- Set the class-based stat gain level function.
function set_class_stat_gain_level_fn(class_id, fn)
  class_stat_gain_fns[class_id] = fn
end

-- Set the race-based stat gain level function.
function set_race_stat_gain_level_fn(race_id, fn)
  race_stat_gain_fns[race_id] = fn
end

-- Set a miscellaneous level gain function.
function set_misc_gain_level_fn(id, fn)
  misc_gain_fns[id] = fn
end

-- level is a function that is called each level, whenever a creature
-- levels up and has a class-specific level function defined.  It also
-- calls race- and class-based stat gain functions.
function level(race_id, class_id, creature_id, new_level)
  local fn = class_fns[class_id]
  local class_stat_fn = class_stat_gain_fns[class_id]
  local race_stat_fn = race_stat_gain_fns[race_id]
  local npc_fn = misc_gain_fns[npc_fn_key]

  if fn ~= nil then
    fn(creature_id, new_level)
  end

  if race_stat_fn ~= nil then
      race_stat_fn(creature_id, new_level)
  end

  if class_stat_fn ~= nil then
    class_stat_fn(creature_id, new_level)
  end

  if creature_id ~= PLAYER_ID and npc_fn ~= nil then
    npc_fn(creature_id, new_level)
  end
end


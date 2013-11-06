require('level')

-- Nobles are charismatic, able to command fear and respect in the
-- lower-born and easily-impressed.
local function noble_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_cha(creature_id, is_player(creature_id))
  end
end

-- Set up the noble functions.
local noble_class_stat_fn = noble_stat_gain_fn

level.set_class_stat_gain_level_fn("noble", noble_class_stat_fn)


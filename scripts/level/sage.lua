require('level')

-- Sages require intelligence and willpower to command all spheres of
-- magic.
local function sage_stat_gain_fn(creature_id, level)
  local is_pl = is_player(creature_id)

  if level % 5 == 0 then
    incr_int(creature_id, is_pl)
    incr_wil(creature_id, is_pl)
  end
end

-- Set up the sage functions.
local sage_class_stat_fn = sage_stat_gain_fn

level.set_class_stat_gain_level_fn("sage", sage_class_stat_fn)


require('level')

-- The scrying and meditation practiced by oracles requires intense focus
-- and force of will.
local function oracle_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_wil(creature_id, is_player(creature_id))
  end
end

-- Set up the oracle functions.
local oracle_class_stat_fn = oracle_stat_gain_fn

level.set_class_stat_gain_level_fn("oracle", oracle_class_stat_fn)


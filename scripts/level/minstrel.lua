require('level')

-- Some bards are dumb, or weak of will,
-- any many aren't too strong.
-- But if a minstrel's got no smile,
-- he's not a minstrel long.
local function minstrel_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_cha(creature_id, is_player(creature_id))
  end
end

-- Set up the minstrel functions.
local minstrel_class_stat_fn = minstrel_stat_gain_fn

level.set_class_stat_gain_level_fn("minstrel", minstrel_class_stat_fn)


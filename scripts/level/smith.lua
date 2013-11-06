require('level')

-- Smiths toil all day by a fiery forge, shaping metal into many forms.
local function smith_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_str(creature_id, is_player(creature_id))
  end
end

-- Set up the smith functions.
local smith_class_stat_fn = smith_stat_gain_fn

level.set_class_stat_gain_level_fn("smith", smith_class_stat_fn)


require('level')

-- For an archer to live long, he or she requires great accuracy, which
-- is driven by dexterity.
local function archer_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_dex(creature_id, is_player(creature_id))
  end
end

-- Set up the archer functions.
local archer_class_stat_fn = archer_stat_gain_fn

level.set_class_stat_gain_level_fn("archer", archer_class_stat_fn)


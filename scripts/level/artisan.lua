require('level')

-- Artisans have excellent hand-eye coordination, required for making
-- beautiful objects.
local function artisan_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_dex(creature_id, is_player(creature_id))
  end
end

-- Set up the artisan functions.
local artisan_class_stat_fn = artisan_stat_gain_fn

level.set_class_stat_gain_level_fn("artisan", artisan_class_stat_fn)


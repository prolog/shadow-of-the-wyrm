require('level')

-- The study of arcane magic is driven by intelligence.
local function wizard_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_int(creature_id, is_player(creature_id))
  end
end

-- Set up the wizard functions.
local wizard_class_stat_fn = wizard_stat_gain_fn

level.set_class_stat_gain_level_fn("wizard", wizard_class_stat_fn)


require('level')

-- Merchants tend towards the charismatic, travelling from town to town,
-- selling their wares.
local function merchant_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_cha(creature_id, is_player(creature_id))
  end
end

-- Set up the merchant functions.
local merchant_class_stat_fn = merchant_stat_gain_fn

level.set_class_stat_gain_level_fn("merchant", merchant_class_stat_fn)


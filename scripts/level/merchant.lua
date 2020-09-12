require('level')

-- Merchants tend towards the charismatic, travelling from town to town,
-- selling their wares.  They start off with an encyclopedic knowledge of
-- all items.
local function merchant_stat_gain_fn(creature_id, level)
  if level == 1 then
    identify_item_type(creature_id, -1)
  end

  if level % 5 == 0 then
    incr_cha(creature_id, is_player(creature_id))
  end
end

-- Set up the merchant functions.
local merchant_class_stat_fn = merchant_stat_gain_fn

level.set_class_stat_gain_level_fn("merchant", merchant_class_stat_fn)


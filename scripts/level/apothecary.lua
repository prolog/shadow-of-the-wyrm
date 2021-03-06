require('level')

-- Apothecaries are learned men and women, who ground their knowledge in
-- a study of the elements.  As a result, they gain intelligence as they
-- become more experienced.
local function apothecary_stat_gain_fn(creature_id, level)
  if level == 1 then
    identify_item_type(creature_id, CITEM_TYPE_POTION)
  end

  if level % 5 == 0 then
    incr_int(creature_id, is_player(creature_id))
  end
end

-- Set up the apothecary functions.
local apothecary_class_stat_fn = apothecary_stat_gain_fn

level.set_class_stat_gain_level_fn("apothecary", apothecary_class_stat_fn)


require('level')

-- Identify an initial set of items for the merchant.
-- 
-- Each merchant starts off knowing everything about wands, potions, rings
-- and amulet, or scrolls and spellbooks.
local function identify_random_item_types()
  local merc_item_types = { {CITEM_TYPE_WAND},
                            {CITEM_TYPE_POTION},
                            {CITEM_TYPE_RING, CITEM_TYPE_AMULET},
                            {CITEM_TYPE_SCROLL, CITEM_TYPE_SPELLBOOK} }

  -- Pick an item type, and then identify all items of that type.
  local merc_item_type = merc_item_types[math.random(#merc_item_types)]

  for i,itype in ipairs(merc_item_type) do
    identify_item_type(itype)
  end
end

-- Merchants tend towards the charismatic, travelling from town to town,
-- selling their wares.  They start off with a wealth of knowledge about
-- a particular rare and magical class of items.
local function merchant_stat_gain_fn(creature_id, level)
  if level == 1 then
    identify_random_item_types()
  end

  if level % 5 == 0 then
    incr_cha(creature_id, is_player(creature_id))
  end
end

-- Set up the merchant functions.
local merchant_class_stat_fn = merchant_stat_gain_fn

level.set_class_stat_gain_level_fn("merchant", merchant_class_stat_fn)


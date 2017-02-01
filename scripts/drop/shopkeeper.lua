require('drop')
require('fn')

local function shopkeeper_buy(dropping_creature_id, shopkeeper_id, item_base_id, drop_y, drop_x)
  local item_type = get_item_type(item_base_id)
  local shop_id = get_shop_id(shopkeeper_id)
  local stocked_item_types = get_stocked_item_types(shop_id)

  if fn.contains(stocked_item_types, item_type) then
    -- Determine the price
      -- If < 1, not interested.
      -- Price is an actual amount of ivory: interested
        -- Price is greater than currency on hand: apologize
        -- Otherwise, make the offer
          -- Offer accepted: thank, set item unpaid transfer money
          -- Offer rejected: rueful
  else 
    -- Not interested.
  end
end

local shopkeeper_buy_fn = shopkeeper_buy

drop.set_drop_fn("shopkeeper", shopkeeper_buy_fn)


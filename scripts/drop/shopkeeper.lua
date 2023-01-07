require('constants')
require('drop')
require('fn')

local function shopkeeper_uninterested()
  add_message("SHOPKEEPER_UNINTERESTED_SID")
end

-- Thank the creature, but inform them that the shopkeeper can't afford
-- that item.
local function shopkeeper_lacks_funds(dropping_creature_id)
  add_message("SHOPKEEPER_INSUFFICIENT_FUNDS_DROP_SID", {get_name(dropping_creature_id)})
end

local function purchase_item(price, cash_on_hand, dropping_creature_id, shopkeeper_id, item_id, coords)
  local purchased = false

  -- Make the offer
  local confirm = add_confirmation_message("SHOPKEEPER_DROP_BUY_OFFER_SID", {tostring(price)})

  local final_price = price

  if confirm == true then
    -- Offer accepted
    add_message("SHOPKEEPER_THANKS_SID")

    -- See if the creature can wheedle some extra cash
    local bargain, prem = bargain_premium(dropping_creature_id)

    if bargain == true then
      final_price = math.floor(final_price + (final_price * (prem / 100)))

      if final_price > cash_on_hand then
        final_price = cash_on_hand
      end

      -- Add a message about the deal
      add_message("SHOPKEEPER_PREMIUM_AMOUNT_SID", {tostring(final_price)})
    end

    -- The item now belongs to the shopkeeper.  Transfer the money, and
    -- set the item to be unpaid.
    set_item_unpaid(coords[1], coords[2], item_id)
    transfer_item(dropping_creature_id, shopkeeper_id, CURRENCY_ID, final_price)
    purchased = true
  else
    -- Offer rejected.
    clear_and_add_message("SHOPKEEPER_DROP_BUY_DECLINE_SID")
  end

  return purchased
end

local function shopkeeper_buy(dropping_creature_id, shopkeeper_id, item_id, item_base_id, drop_y, drop_x)
  local shop_id = get_shop_id(shopkeeper_id)
  local readd_to_dropping_creature = true

  -- Ignore any shop items that the creature has picked up, and then
  -- dropped again.
  if is_item_unpaid(drop_y, drop_x, item_id) == true then
    return
  end

  -- Make sure the creature's in the shop before triggering item-buying
  -- behaviour from the shopkeeper.
  if is_in_shop(drop_y, drop_x, shop_id) then
    if fn.contains(get_stocked_item_types(shop_id), get_item_type(item_base_id)) then
      local price = get_sale_price(drop_y, drop_x, item_id)

      if price < 0 then
        shopkeeper_uninterested()
      else
        local cash_on_hand = count_currency(shopkeeper_id)

        if price > cash_on_hand then
          shopkeeper_lacks_funds(dropping_creature_id)
        else
          local purchased = purchase_item(price, cash_on_hand, dropping_creature_id, shopkeeper_id, item_id, {drop_y, drop_x})
          readd_to_dropping_creature = (purchased == false)
        end
      end
    else 
      -- Shop doesn't sell that sort of thing.
      shopkeeper_uninterested()
    end
  end

  if readd_to_dropping_creature == true then
    add_object_on_tile_to_creature(drop_y, drop_x, item_id, dropping_creature_id)
  end
end

local shopkeeper_buy_fn = shopkeeper_buy

drop.set_drop_fn("_shopkeeper", shopkeeper_buy_fn)


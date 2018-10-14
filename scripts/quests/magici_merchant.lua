require('constants')

-- Magici merchants sell the stuff at hugely inflated prices.
local magici_cost = 500
local currency_amount = count_currency(PLAYER_ID)

if currency_amount > magici_cost then
  if add_confirmation_message("MAGICI_MERCHANT_OFFER_SID") then
    remove_object_from_player(CURRENCY_ID, magici_cost)
    add_object_to_player_tile(MAGICI_SHARD_ID)

    clear_and_add_message("MAGICI_MERCHANT_ACCEPT_SID")
  else
    clear_and_add_message("MAGICI_MERCHANT_DECLINE_SID")
  end
else
  clear_and_add_message("MAGICI_MERCHANT_INSUFFICIENT_FUNDS_SID")
end

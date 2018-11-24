module(..., package.seeall)

-- Function that handles single-item buy/sell without requiring a shop
-- to be present.
function chat(creature_id, sold_item_id, cost, offer_sid, accept_sid, decline_sid, nsf_sid)
  local currency_amount = count_currency(creature_id)
  if currency_amount > cost then
    if add_confirmation_message(offer_sid) then
      remove_object_from_player(CURRENCY_ID, cost)
      add_object_to_player_tile(sold_item_id)

      clear_and_add_message(accept_sid)
    else
      clear_and_add_message(decline_sid)
    end
  else
    clear_and_add_message(nsf_sid)
  end
end


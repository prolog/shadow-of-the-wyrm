require('constants')

module(..., package.seeall)

-- Attempt to buy into a game, adjusting the player's ivory accordingly.
function buy_in(buy_in_msg, nsf_msg, decline_msg, amount)
  if count_currency(PLAYER_ID) >= amount then
    if add_confirmation_message(buy_in_msg, {tostring(amount)}) then
      remove_object_from_player(CURRENCY_ID, amount)
      return true
    else
      clear_and_add_message(decline_msg)
    end
  else
    clear_and_add_message(nsf_message)
  end

  return false
end


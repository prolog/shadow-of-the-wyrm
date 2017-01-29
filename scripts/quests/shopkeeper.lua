require('constants')

-- Is there an amount owing?
local unpaid_amount = get_unpaid_amount(PLAYER_ID)

if unpaid_amount > 0 then
  -- Does the player have enough ivory to cover it?
  local currency_amount = count_currency(PLAYER_ID)

  if (currency_amount >= unpaid_amount) then
    -- Confirm the purchase
    if add_confirmation_message("SHOPKEEPER_CONFIRM_PURCHASE_SID", {tostring(unpaid_amount)}) then
      -- Set all unpaid items on the player to paid
      set_items_paid(PLAYER_ID)
      clear_and_add_message("SHOPKEEPER_THANKS_SID")
    else
      clear_and_add_message("SHOPKEEPER_WARNING_SID")
    end
  else
    clear_and_add_message("SHOPKEEPER_INSUFFICIENT_FUNDS_SID")
  end
else
  -- Nothing owed.  Add a standard greeting.
  clear_and_add_message("SHOPKEEPER_SPEECH_TEXT_SID")
end

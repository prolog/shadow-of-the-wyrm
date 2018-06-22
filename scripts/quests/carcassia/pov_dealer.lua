require('dealer')
require('constants')

if dealer.buy_in("POV_DEALER_SPEECH_TEXT_SID", "POV_DEALER_NSF_MESSAGE_SID", "POV_DEALER_DECLINE_MESSAGE_SID", 2) then
  local bet_val = tonumber(add_char_message("POV_DEALER_WHICH_NUMBER_SID"))

  if bet_val >= 1 and bet_val <= 6 then
    add_message_with_pause("POV_DEALER_ROLLING_SID")

    local actual_val = RNG_range(1, 6)
    add_message_direct(tostring(actual_val) .. "!")
    
    if bet_val == actual_val then
      add_message("DEALER_WIN_SID")
      add_object_to_player_tile(CURRENCY_ID, 6)
    else
      add_message("DEALER_LOSE_SID")
    end
  else
    clear_and_add_message("POV_DEALER_INVALID_VALUE_SID")
    add_object_to_player_tile(CURRENCY_ID, 2)
  end
end


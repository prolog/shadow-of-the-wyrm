require('constants')

-- Check to see if the player has any unidentified items.
--
-- If he or she does, Idem will offer to identify a particular item,
-- for a fee.
if get_unidentified_item_count(PLAYER_ID) > 0 then
  add_message_with_pause("IDEM_SPEECH_TEXT_SID")
  local selected, item_id, item_base_id = select_item(PLAYER_ID, CITEM_FILTER_UNIDENTIFIED)

  if selected == true then
    -- Check the base ID to see if that type of item has already been
    -- identified.
    if is_item_identified(item_base_id) then
      clear_and_add_message("IDEM_ALREADY_IDENTIFIED_SPEECH_TEXT_SID")
    else
      -- The item hasn't been identified yet.  Offer to identify it, for
      -- a fee...
      local item_value = get_item_value(item_base_id)
      local currency_amount = get_item_count(PLAYER_ID, CURRENCY_ID)

      if currency_amount >= item_value then
        -- Prompt the player to see if he or she wants to pay.
        if add_confirmation_message("IDEM_IDENTIFY_QUERY_TEXT_SID", {tostring(item_value)}) then
          clear_and_add_message("IDEM_IDENTIFY_SPEECH_TEXT_SID")
          identify_item(item_base_id)
          remove_object_from_player(CURRENCY_ID, item_value)
        else
          clear_and_add_message("IDEM_ANOTHER_DAY_SPEECH_TEXT_SID")
        end
      else
        clear_and_add_message("IDEM_NOT_ENOUGH_IVORY_SPEECH_TEXT_SID")
      end
    end
  else
    clear_and_add_message("IDEM_ANOTHER_DAY_SPEECH_TEXT_SID")
  end
else
  add_message("IDEM_NO_UNID_SPEECH_TEXT_SID")
end


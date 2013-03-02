if is_item_generated("kew_key") == true then
  add_message("KEW_SPEECH_TEXT_SID")
else
  add_message("KEW_SUPPLIES_SPEECH_SID")
  add_object_to_player_tile("kew_key")
end


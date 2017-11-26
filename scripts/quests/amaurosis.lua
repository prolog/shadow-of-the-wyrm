require('constants')

if player_has_item("hearts_needle") then
  if get_num_deities() == 0 then
    add_message_with_pause("EVIL_WIN_MESSAGE_GODSLAYER")
    clear_and_add_message("EVIL_WIN_MESSAGE_GODSLAYER2")

    -- If Amaurosis is friendly, for whatever reason, he sure isn't
    -- anymore...
    set_hostility("end_boss", PLAYER_ID)
  else    
    remove_object_from_player("hearts_needle")

    add_message_with_pause("EVIL_WIN_MESSAGE")
    add_message_with_pause("EVIL_WIN_MESSAGE2")
    add_message_with_pause("EVIL_WIN_MESSAGE3")
    add_message_with_pause("EVIL_WIN_MESSAGE4")
    add_message_with_pause("EVIL_WIN_MESSAGE5")
    clear_and_add_message("EVIL_WIN_MESSAGE6")

    set_winner(PLAYER_ID, CCREATURE_WIN_EVIL)

    -- Always stop playing after an evil win (since the world has been
    -- destroyed)
    stop_playing_game(PLAYER_ID, true)
  end
else
  clear_and_add_message("AMAUROSIS_SPEECH_TEXT_SID")
end


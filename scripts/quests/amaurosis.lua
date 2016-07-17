if player_has_item("hearts_needle") then
  remove_object_from_player("hearts_needle")

  add_message_with_pause("EVIL_WIN_MESSAGE")
  add_message_with_pause("EVIL_WIN_MESSAGE2")
  add_message_with_pause("EVIL_WIN_MESSAGE3")
  add_message_with_pause("EVIL_WIN_MESSAGE4")
  add_message_with_pause("EVIL_WIN_MESSAGE5")
  clear_and_add_message("EVIL_WIN_MESSAGE6")

  set_winner("player", 2) -- evil win

  -- Always stop playing after an evil win (since the world has been
  -- destroyed)
  stop_playing_game("player", true)
else
  clear_and_add_message("AMAUROSIS_SPEECH_TEXT_SID")
end


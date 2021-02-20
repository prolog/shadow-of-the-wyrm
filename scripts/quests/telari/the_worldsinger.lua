if get_num_deities() == 0 then
  clear_and_add_message("THE_WORLDSINGER_GODSLAYER_SPEECH_TEXT_SID")
else
  add_message_with_pause("THE_WORLDSINGER_SPEECH_TEXT_SID")
  add_message_with_pause("THE_WORLDSINGER_SPEECH_TEXT2_SID")
  clear_and_add_message("THE_WORLDSINGER_SPEECH_TEXT3_SID")
end

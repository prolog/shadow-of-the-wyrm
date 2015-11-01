if get_unidentified_item_count("player") > 0 then
  add_message_with_pause("IDEM_SPEECH_TEXT_SID")
else
  add_message("IDEM_NO_UNID_SPEECH_TEXT_SID")
end


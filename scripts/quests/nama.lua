add_message_with_pause("NAMA_RENAME_SPEECH_TEXT_SID")
add_message_with_pause("NAMA_RENAME_SPEECH2_TEXT_SID")
add_message_with_pause("NAMA_RENAME_SPEECH3_TEXT_SID")

local rename_confirm = add_confirmation_message("NAMA_RENAME_QUERY_SID")

if rename_confirm == true then
  local new_name = add_prompt_message("NAMA_RENAME_QUERY_NEW_NAME_SID")
  local changed = set_creature_name("player", new_name)

  if changed == true then
    clear_and_add_message("NAMA_RENAME_QUERY_AFFIRM_SID")
  else
    clear_and_add_message("NAMA_RENAME_QUERY_DENY_SID")
  end
else
  clear_and_add_message("NAMA_RENAME_QUERY_DENY_SID")
end

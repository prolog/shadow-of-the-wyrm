if is_music_enabled() then
  -- ...
  
  -- If nothing else is selected, play something generic.
  clear_and_add_message("MUSICIAN_NO_MUSIC_SELECTED")
else
  clear_and_add_message("MUSICIAN_MUSIC_DISABLED")
end

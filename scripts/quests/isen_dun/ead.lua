require('constants')

-- If the player has slain the Nine, the magics that allow teleportation
-- between the worlds are gone.
if get_num_deities() == 0 then
  clear_and_add_message("EAD_TELARI_GODSLAYER_TEXT_SID")
elseif get_creature_additional_property(PLAYER_ID, "TELARI_THE_SORCEROR_DEAD") == tostring(true) then
  clear_and_add_message("EAD_TELARI_THE_SORCEROR_DEAD_SID")
else
  -- If the player has a source of water breathing, Ead will offer to send
  -- him or her elsewhere...
  if creature_has_status(PLAYER_ID, "_wb") then
    add_message_with_pause("EAD_TELARI_TEXT1_SID")
    add_message_with_pause("EAD_TELARI_TEXT2_SID")
    add_message_with_pause("EAD_TELARI_TEXT3_SID")
    add_message_with_pause("EAD_TELARI_TEXT4_SID")
    add_message_with_pause("EAD_TELARI_TEXT5_SID")
    add_message_with_pause("EAD_TELARI_TEXT6_SID")
    add_message_with_pause("EAD_TELARI_TEXT7_SID")
    add_message_with_pause("EAD_TELARI_TEXT8_SID")

    clear_messages()

    if add_confirmation_message("EAD_TELARI_TEXT9_SID") then
      play_music_event(CMUSIC_EVENT_PLANETARY_TELEPORT, false)
      add_message_with_pause("EAD_TELARI_CONFIRM_SID")
      load_map(PLAYER_ID, "telari")
    else
      clear_and_add_message("EAD_TELARI_DENY_SID")
    end
  else
    -- Ead will give silverweed to the player the first time they talk.
    local silverweed_prop = "ead_given_silverweed"
    local given_silverweed = get_creature_additional_property(PLAYER_ID, silverweed_prop)

    add_message_with_pause("EAD_SPEECH_TEXT1_SID")
    add_message_with_pause("EAD_SPEECH_TEXT2_SID")
    add_message_with_pause("EAD_SPEECH_TEXT3_SID")
    add_message_with_pause("EAD_SPEECH_TEXT4_SID")
    add_message_with_pause("EAD_SPEECH_TEXT5_SID")
    add_message_with_pause("EAD_SPEECH_TEXT6_SID")
    add_message_with_pause("EAD_SPEECH_TEXT7_SID")
    add_message_with_pause("EAD_SPEECH_TEXT8_SID")
    add_message_with_pause("EAD_SPEECH_TEXT9_SID")
    add_message_with_pause("EAD_SPEECH_TEXT10_SID")

    if string.len(given_silverweed) == 0 then
      -- Give the player some silverweed, and add some additional chat text.
      add_object_to_player_tile("silverweed", 3)
      set_creature_additional_property(PLAYER_ID, silverweed_prop, tostring(true))

      add_message_with_pause("EAD_SPEECH_TEXT11_SID")
      add_message_with_pause("EAD_SPEECH_TEXT12_SID")
      add_message_with_pause("EAD_SPEECH_TEXT13_SID")
      clear_and_add_message("EAD_SPEECH_TEXT14_SID")  
    else
      clear_and_add_message("EAD_SPEECH_TEXT11_SID")
    end
  end
end

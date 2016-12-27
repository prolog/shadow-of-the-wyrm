require('constants')

-- Ead doesn't actually have a quest, but will give silverweed to the
-- player the first time they talk.
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


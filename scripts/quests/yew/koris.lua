add_message_with_pause("KORIS_SPEECH_TEXT_SID")
add_message_with_pause("KORIS_SPEECH_TEXT2_SID")
add_message_with_pause("KORIS_SPEECH_TEXT3_SID")
add_message_with_pause("KORIS_SPEECH_TEXT4_SID")
add_message_with_pause("KORIS_SPEECH_TEXT5_SID")
clear_and_add_message("KORIS_SPEECH_TEXT6_SID")

set_creature_additional_property(PLAYER_ID, QUEST_SEA_CAPTAIN_KORIS_COMPLETE, "1")

if RNG_percent_chance(50) then
  add_object_to_player_tile(AMULET_OF_THE_SEA_ID)
end

remove_creature_from_map("koris")


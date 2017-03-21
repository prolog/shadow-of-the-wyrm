require('constants')

local ns_prop = "namer_given_namking_stone"
local given_ns = get_creature_additional_property(PLAYER_ID, ns_prop) == tostring(true)

if given_ns == false then
  add_message_with_pause("THE_NAMER_STONE_TEXT_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT2_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT3_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT4_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT5_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT6_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT7_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT8_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT9_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT10_SID")
  clear_and_add_message("THE_NAMER_STONE_TEXT11_SID")

  add_object_to_player_tile("naming_stone")
  set_creature_additional_property(PLAYER_ID, ns_prop, tostring(true))
else
  clear_and_add_message("THE_NAMER_SPEECH_TEXT_SID")
end



require('constants')

local emperor_amulet_key = "emperor_gift_generated"
local amulet_generated = get_creature_additional_property(PLAYER_ID, emperor_amulet_key)

if string.len(amulet_generated) == 0 then
  if player_has_item("ironsword") then
    add_message_with_pause("EMPEROR_TITUS_IRONSWORD_SID")
    add_message_with_pause("EMPEROR_TITUS_IRONSWORD2_SID")
    add_message_with_pause("EMPEROR_TITUS_IRONSWORD3_SID")
    clear_and_add_message("EMPEROR_TITUS_IRONSWORD4_SID")

    add_object_to_player_tile("amulet_carcassian_emperor")
    remove_object_from_player("ironsword")

    set_creature_additional_property(PLAYER_ID, emperor_amulet_key, "1")
  else
    clear_and_add_message("EMPEROR_TITUS_SPEECH_TEXT_SID")
  end
else
  clear_and_add_message("EMPEROR_TITUS_SPEECH_TEXT_ACK_SID")
end

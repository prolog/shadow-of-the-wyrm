require('constants')

if player_has_item(WIZARD_ROBES_ID) and player_has_item(WIZARD_STAFF_ID) then
  remove_object_from_player(WIZARD_ROBES_ID)
  remove_object_from_player(WIZARD_STAFF_ID)

  set_creature_additional_property(PLAYER_ID, QUEST_GOLGOA_WIZARD_COMPLETE, "1")
  clear_and_add_message("NEW_WIZARD_THANKS_SID")
else
  clear_and_add_message("NEW_WIZARD_SPEECH_TEXT_SID")
end

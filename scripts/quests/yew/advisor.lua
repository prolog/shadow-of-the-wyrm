require('constants')

if player_has_item(ISEN_DUN_WHISKY_ID) and creature_has_humanoid_followers(PLAYER_ID) then
  clear_and_add_message("YEW_ADVISOR_WHISKY_SID")

  remove_object_from_player(ISEN_DUN_WHISKY_ID)
  set_creature_additional_property(PLAYER_ID, QUEST_ISEN_DUN_YEW_COMPLETE, "1")
else
  clear_and_add_message("YEW_ADVISOR_SPEECH_TEXT_SID")
end

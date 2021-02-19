require('constants')

if player_has_item(STOLEN_GOODS_ID) then
  if creature_has_humanoid_followers(PLAYER_ID) then
    clear_and_add_message("SNAKES_STOLEN_GOODS_SID")

    remove_object_from_player(STOLEN_GOODS_ID)
    set_creature_additional_property(PLAYER_ID, QUEST_ACEY_STOLEN_GOODS_COMPLETE, "1")
  else
    clear_and_add_message("SNAKES_NO_PARTY_SID")
  
    set_hostility(args[SPEAKING_CREATURE_ID], PLAYER_ID)
    summon_monsters_around_creature({SNAKELING_THUG_ID, SNAKELING_MERCENARY_ID, SNAKELING_ASSASSIN_ID}, PLAYER_ID, RNG_range(3, 6), true)
  end
else
  clear_and_add_message("SNAKES_SPEECH_TEXT_SID")
end


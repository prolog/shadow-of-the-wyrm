require('constants')

-- After talking to the new wizard, the goblins come back...
local function setup_raid()
  add_message_with_pause("NEW_WIZARD_RAID_SID")
  clear_and_add_message("NEW_WIZARD_RAID2_SID")

  local creature_ids = {GOBLIN_TRAPPER_ID, GOBLIN_ID, GOBLIN_CHAMPION_ID, GOBLIN_IMPALER_ID, GOBLIN_RAIDER_ID, GOBLIN_PELTER_ID}

  for i = 1, 60 do
    local y = RNG_range(1, 18)
    local x = RNG_range(1, 79)
    add_creature_to_map(creature_ids[RNG_range(1, #creature_ids)], y, x)
  end

  set_creature_additional_property(PLAYER_ID, QUEST_STONEHEIM_RAID, "1")
end

if player_has_item(WIZARD_ROBES_ID) and player_has_item(WIZARD_STAFF_ID) then
  remove_object_from_player(WIZARD_ROBES_ID)
  remove_object_from_player(WIZARD_STAFF_ID)

  set_creature_additional_property(PLAYER_ID, QUEST_GOLGOA_WIZARD_COMPLETE, "1")
  add_message_with_pause("NEW_WIZARD_THANKS_SID")

  setup_raid()
else
  clear_and_add_message("NEW_WIZARD_SPEECH_TEXT_SID")
end
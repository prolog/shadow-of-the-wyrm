require('quest')
require('constants')

-- Wyrmeswraec quest details
local function skaal_wyrmeswraec_start_fn()
  add_message_with_pause("SKAAL_WYRMESWRAEC_QUEST_START_SID")
  add_message_with_pause("SKAAL_WYRMESWRAEC_QUEST_START2_SID")
  clear_and_add_message("SKAAL_WYRMESWRAEC_QUEST_START3_SID")
  add_object_to_player_tile("wyrmeswraec_gate_key")
end

local function skaal_wyrmeswraec_completion_condition_fn()
  return player_has_item("handful_gleaming_wyrm_scales") == true
end

local function skaal_wyrmeswraec_completion_fn()
  add_message_with_pause("SKAAL_WYRMESWRAEC_QUEST_COMPLETE_SID")
  clear_and_add_message("SKAAL_WYRMESWRAEC_QUEST_COMPLETE2_SID")
  add_object_to_player_tile("wyrm_ward")
  return true
end

-- Skaal's first quest is to investigate the destruction of Wyrmeswraec
skaal_quest = Quest:new("skaal_wyrmeswraec_quest", 
                        "SKAAL_WYRMESWRAEC_QUEST_TITLE_SID", 
                        "SKAAL_SHORT_DESCRIPTION_SID", 
                        "SKAAL_WYRMESWRAEC_DESCRIPTION_SID", 
                        "SKAAL_WYRMESWRAEC_QUEST_COMPLETE_SID", 
                        "SKAAL_WYRMESWRAEC_QUEST_REMINDER_SID", 
                        truefn,
                        skaal_wyrmeswraec_start_fn, 
                        skaal_wyrmeswraec_completion_condition_fn, 
                        skaal_wyrmeswraec_completion_fn)

local function check_defense()
  local def = false

  if count_creatures_with_race(GOBLIN_RACE_ID) == 0 then
    remove_creature_additional_property(PLAYER_ID, QUEST_STONEHEIM_RAID)

    add_message_with_pause("SKAAL_RAID_SID")
    clear_and_add_message("SKAAL_RAID2_SID")

    add_object_to_player_tile("protector")
  else
    clear_and_add_message("SKAAL_RAID_IN_PROGRESS_SID")
  end
end

local raid_in_progress = get_creature_additional_property(PLAYER_ID, QUEST_STONEHEIM_RAID)

if raid_in_progress == "1" then
  check_defense()
else
  if skaal_quest:execute() == false then
    add_message("SKAAL_SPEECH_TEXT_SID")
  end
end


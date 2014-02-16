require('quest')

-- Find the black orb in Wyrmeswraec
local function gildi_orb_start_fn()
  add_message_with_pause("GILDI_ORB_QUEST_START_SID")
  add_message_with_pause("GILDI_ORB_QUEST_START2_SID")
  clear_and_add_message("GILDI_ORB_QUEST_START3_SID")
end

local function gildi_orb_completion_condition_fn()
  -- Did the player bring back the black orb?
  return player_has_item("black_orb") == true
end

local function gildi_orb_completion_fn()
  add_message_with_pause("GILDI_ORB_QUEST_COMPLETE_SID")
  clear_and_add_message("GILDI_ORB_QUEST_COMPLETE2_SID")
  
  remove_object_from_player("black_orb")  
  add_object_to_player_tile("gildis_cloak")

  return true
end

gildi_orb_quest = Quest:new("gildi_orb",
                            "GILDI_ORB_QUEST_TITLE_SID",
                            "GILDI_DESCRIPTION_SID",
                            "GILDI_ORB_DESCRIPTION_SID",
                            "GILDI_ORB_QUEST_COMPLETE_SID",
                            "GILDI_ORB_QUEST_REMINDER_SID",
                            truefn,
                            gildi_orb_start_fn,
                            gildi_orb_completion_condition_fn,
                            gildi_orb_completion_fn)

if gildi_orb_quest:execute() == false then
  add_message("GILDI_SPEECH_TEXT_SID")
end


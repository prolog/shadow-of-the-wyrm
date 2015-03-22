require('quest')

-- Thengil is looking for the Cosmos Stone...
local function thengil_cosmos_start_fn()
  add_message_with_pause("THENGIL_COSMOS_QUEST_START_SID")
  add_message_with_pause("THENGIL_COSMOS_QUEST_START2_SID")
  clear_and_add_message("THENGIL_COSMOS_QUEST_START3_SID")
end

-- Quest ends when the player has the Cosmos Stone in his or her
-- inventory.
local function thengil_cosmos_completion_condition_fn()
  return player_has_item("cosmos_stone") == true
end

-- Thengil forges the world-sword with the cosmos stone.
local function thengil_cosmos_completion_fn()  
  add_message_with_pause("THENGIL_COSMOS_QUEST_COMPLETE_SID")
  add_message_with_pause("THENGIL_COSMOS_QUEST_COMPLETE2_SID")
  add_message_with_pause("THENGIL_COSMOS_QUEST_COMPLETE3_SID")
  clear_and_add_message("THENGIL_COSMOS_QUEST_COMPLETE4_SID") 

  remove_object_from_player("cosmos_stone")
  add_object_to_player_tile("worldsword")

  return true
end

thengil_quest = Quest:new("thengil_cosmos",
                          "THENGIL_COSMOS_QUEST_TITLE_SID",
                          "THENGIL_SHORT_DESCRIPTION_SID",
                          "THENGIL_COSMOS_QUEST_DESCRIPTION_SID",
                          "THENGIL_COSMOS_QUEST_COMPLETE_SID",
                          "THENGIL_COSMOS_QUEST_REMINDER_SID",
                          truefn,
                          thengil_cosmos_start_fn,
                          thengil_cosmos_completion_condition_fn,
                          thengil_cosmos_completion_fn)

if thengil_quest:execute() == false then
  add_message("THENGIL_SPEECH_TEXT_SID")
end


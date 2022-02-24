require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Fisherman quest details
local function fisherman_start_fn()
  add_message_with_pause("FISHERMAN_QUEST_START_SID")
  add_message_with_pause("FISHERMAN_QUEST_START2_SID")
  clear_and_add_message("FISHERMAN_QUEST_START3_SID")
end

local function fisherman_completion_condition_fn()
  return (player_has_item(HEAVY_CLOAK_ID) and
          player_has_item(LEATHER_BOOTS_ID))
end

local function fisherman_completion_fn()
  remove_object_from_player(HEAVY_CLOAK_ID)
  remove_object_from_player(LEATHER_BOOTS_ID)
  
  add_message_with_pause("FISHERMAN_QUEST_COMPLETE_SID")
  clear_and_add_message("FISHERMAN_QUEST_COMPLETE2_SID")

  add_object_to_player_tile(AMULET_OF_THE_SEA_ID, 1, "", 0, RNG_range(1, 5))

return true
end

local q_id = "fisherman_" .. cr_id

fisherman_quest = Quest:new(q_id, 
                            "FISHERMAN_QUEST_TITLE_SID", 
                            "FISHERMAN_SHORT_DESCRIPTION_SID", 
                            "FISHERMAN_QUEST_DESCRIPTION_SID", 
                            "FISHERMAN_QUEST_COMPLETE_SID", 
                            "FISHERMAN_QUEST_REMINDER_SID", 
                            truefn,
                            fisherman_start_fn, 
                            fisherman_completion_condition_fn, 
                            fisherman_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, q_id, 20)

if do_quest == true then
  do_quest = fisherman_quest:execute()
end

if do_quest == false then
  clear_and_add_message("FISHERMAN_SPEECH_TEXT_SID")
end

require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Tanner quest details
local function tanner_start_fn()
  add_message_with_pause("TANNER_QUEST_START_SID")
  add_message_with_pause("TANNER_QUEST_START2_SID")
  clear_and_add_message("TANNER_QUEST_START3_SID")
end

local function tanner_completion_condition_fn()
  return (get_item_count(PLAYER_ID, SKIN_ID) >= 12)
end

local function tanner_completion_fn()
  remove_object_from_player(SKIN_ID, 12)
  
  add_message("TANNER_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(100, 200))
  add_object_to_player_tile(LEATHER_HELM_ID, 1, "", RNG_range(1,3))
  Quest:try_additional_quest_reward()
  
  return true
end

tanner_quest = Quest:new("tanner_" .. cr_id, 
                         "TANNER_QUEST_TITLE_SID", 
                         "TANNER_SHORT_DESCRIPTION_SID", 
                         "TANNER_QUEST_DESCRIPTION_SID", 
                         "TANNER_QUEST_COMPLETE_SID", 
                         "TANNER_QUEST_REMINDER_SID", 
                         truefn,
                         tanner_start_fn, 
                         tanner_completion_condition_fn, 
                         tanner_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 20)

if do_quest == true then
  do_quest = tanner_quest:execute()
end

if do_quest == false then
  clear_and_add_message("TANNER_SPEECH_TEXT_SID")
end

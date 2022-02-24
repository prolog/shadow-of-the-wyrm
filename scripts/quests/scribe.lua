require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Scribe quest details
local function scribe_start_fn()
  add_message_with_pause("SCRIBE_QUEST_START_SID")
  add_message_with_pause("SCRIBE_QUEST_START2_SID")
  clear_and_add_message("SCRIBE_QUEST_START3_SID")
end

local function scribe_completion_condition_fn()
  return ((get_item_count(PLAYER_ID, INKPOT_ID) >= 4) and
          (get_item_count(PLAYER_ID, QUILL_ID) >= 12))
end

local function scribe_completion_fn()
  remove_object_from_player(INKPOT_ID, 4)
  remove_object_from_player(QUILL_ID, 12)
  
  add_message("SCRIBE_QUEST_COMPLETE_SID")
  add_object_to_player_tile(ENCHANTING_SCROLL_ID, 2)
  Quest:try_additional_quest_reward()
  
  return true
end

local q_id = "scribe_" .. cr_id

scribe_quest = Quest:new(q_id, 
                         "SCRIBE_QUEST_TITLE_SID", 
                         "SCRIBE_SHORT_DESCRIPTION_SID", 
                         "SCRIBE_QUEST_DESCRIPTION_SID", 
                         "SCRIBE_QUEST_COMPLETE_SID", 
                         "SCRIBE_QUEST_REMINDER_SID", 
                         truefn,
                         scribe_start_fn, 
                         scribe_completion_condition_fn, 
                         scribe_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, q_id, 20)

if do_quest == true then
  do_quest = scribe_quest:execute()
end

if do_quest == false then
  clear_and_add_message("SCRIBE_SPEECH_TEXT_SID")
end

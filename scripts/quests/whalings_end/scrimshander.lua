require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Scrimshander quest details
local function scrimshander_start_fn()
  add_message_with_pause("SCRIMSHANDER_QUEST_START_SID")
  add_message_with_pause("SCRIMSHANDER_QUEST_START2_SID")
  clear_and_add_message("SCRIMSHANDER_QUEST_START3_SID")
end

local function scrimshander_completion_condition_fn()
  return get_item_count(PLAYER_ID, IVORY_TUSK_ID) >= 6
end

local function scrimshander_completion_fn()
  remove_object_from_player(IVORY_TUSK_ID, 6)
  
  add_message("SCRIMSHANDER_QUEST_COMPLETE_SID")
  local rewards = {GAIN_ATTRIBUTES_POTION_ID, ENCHANTING_SCROLL_ID}
  add_object_to_player_tile(rewards[RNG_range(1, #rewards)])
  
  return true
end

scrimshander_quest = Quest:new("scrimshander_ivory_quest", 
                               "SCRIMSHANDER_QUEST_TITLE_SID", 
                               "SCRIMSHANDER_SHORT_DESCRIPTION_SID", 
                               "SCRIMSHANDER_QUEST_DESCRIPTION_SID", 
                               "SCRIMSHANDER_QUEST_COMPLETE_SID", 
                               "SCRIMSHANDER_QUEST_REMINDER_SID", 
                               truefn,
                               scrimshander_start_fn, 
                               scrimshander_completion_condition_fn, 
                               scrimshander_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 20)

if scrimshander_quest:execute() == false then
  clear_and_add_message("SCRIMSHANDER_SPEECH_TEXT_SID")
end

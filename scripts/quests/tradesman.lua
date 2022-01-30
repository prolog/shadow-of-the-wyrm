require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Tradesman quest details
local function tradesman_start_fn()
  add_message_with_pause("TRADESMAN_QUEST_START_SID")
  clear_and_add_message("TRADESMAN_QUEST_START2_SID")
end

local function tradesman_completion_condition_fn()
  return (get_item_count(PLAYER_ID, STONE_BLOCK_ID) >= 4)
end

local function tradesman_completion_fn()
  remove_object_from_player(STONE_BLOCK_ID, 4)
  
  add_message("TRADESMAN_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(100, 200))
  Quest:try_additional_quest_reward()
  
  return true
end

trades_quest = Quest:new("tradesman_" .. cr_id, 
                         "TRADESMAN_QUEST_TITLE_SID", 
                         "TRADESMAN_SHORT_DESCRIPTION_SID", 
                         "TRADESMAN_QUEST_DESCRIPTION_SID", 
                         "TRADESMAN_QUEST_COMPLETE_SID", 
                         "TRADESMAN_QUEST_REMINDER_SID", 
                         truefn,
                         tradesman_start_fn, 
                         tradesman_completion_condition_fn, 
                         tradesman_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 15)

if do_quest == true then
  do_quest = trades_quest:execute()
end

if do_quest == false then
  clear_and_add_message("TRADESMAN_SPEECH_TEXT_SID")
end

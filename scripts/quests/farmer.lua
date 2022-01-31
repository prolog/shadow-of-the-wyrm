require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Farmer quest details
local function farmer_start_fn()
  add_message_with_pause("FARMER_QUEST_START_SID")
  add_message_with_pause("FARMER_QUEST_START2_SID")
  clear_and_add_message("FARMER_QUEST_START3_SID")
end

local function farmer_completion_condition_fn()
  return ((get_item_count(PLAYER_ID, PEACH_PIT_ID) >= 6) and
          (get_item_count(PLAYER_ID, CHERRY_PIT_ID) >= 6))
end

local function farmer_completion_fn()
  remove_object_from_player(PEACH_PIT_ID, 6)
  remove_object_from_player(CHERRY_PIT_ID, 6)
  
  add_message("FARMER_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(30, 50))
  add_object_to_player_tile(SILVERWEED_ID, RNG_range(2, 4))
  add_object_to_player_tile(STONEFLOWER_ID, RNG_range(1, 2))
  Quest:try_additional_quest_reward()
  
  return true
end

farmer_quest = Quest:new("farmer_" .. cr_id, 
                         "FARMER_QUEST_TITLE_SID", 
                         "FARMER_SHORT_DESCRIPTION_SID", 
                         "FARMER_QUEST_DESCRIPTION_SID", 
                         "FARMER_QUEST_COMPLETE_SID", 
                         "FARMER_QUEST_REMINDER_SID", 
                         truefn,
                         farmer_start_fn, 
                         farmer_completion_condition_fn, 
                         farmer_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 20)

if do_quest == true then
  do_quest = farmer_quest:execute()
end

if do_quest == false then
  clear_and_add_message("FARMER_SPEECH_TEXT_SID")
end

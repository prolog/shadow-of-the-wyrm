require('common_quests')
require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Thatcher quest details
local function thatcher_start_fn()
  add_message_with_pause("THATCHER_QUEST_START_SID")
  clear_and_add_message("THATCHER_QUEST_START2_SID")
end

local function thatcher_completion_condition_fn()
  local item_ids = {RED_WILDFLOWER_ID, YELLOW_WILDFLOWER_ID, BLUE_WILDFLOWER_ID, MAGENTA_WILDFLOWER_ID, CYAN_WILDFLOWER_ID, CREAM_WILDFLOWER_ID}
  
  for i,v in ipairs(item_ids) do
    if player_has_item(v) == false then
      return false
    end
  end

  return true
end

local function thatcher_completion_fn()
  local item_ids = {RED_WILDFLOWER_ID, YELLOW_WILDFLOWER_ID, BLUE_WILDFLOWER_ID, MAGENTA_WILDFLOWER_ID, CYAN_WILDFLOWER_ID, CREAM_WILDFLOWER_ID}

  for i,v in ipairs(item_ids) do
    remove_object_from_player(v)
  end
  
  add_message("THATCHER_QUEST_COMPLETE_SID")
  add_object_to_player_tile(GOLDEN_APPLE_ID)
  add_object_to_player_tile(SILVER_APPLE_ID)
  Quest:try_additional_quest_reward()
  
  return true
end

local q_id = "thatcher_" .. cr_id

thatcher_quest = Quest:new(q_id, 
                           "THATCHER_QUEST_TITLE_SID", 
                           "THATCHER_SHORT_DESCRIPTION_SID", 
                           "THATCHER_QUEST_DESCRIPTION_SID", 
                           "THATCHER_QUEST_COMPLETE_SID", 
                           "THATCHER_QUEST_REMINDER_SID", 
                           truefn,
                           thatcher_start_fn, 
                           thatcher_completion_condition_fn, 
                           thatcher_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, q_id, 20)

if do_quest == true then
  do_quest = thatcher_quest:execute()
end

if do_quest == false then
  do_quest = CommonQuests:do_quests(cr_id)
end

if do_quest == false then
  clear_and_add_message(get_creature_speech_text_sid(cr_id))
end

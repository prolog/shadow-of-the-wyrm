require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Weaver quest details
local function weaver_start_fn()
  add_message_with_pause("WEAVER_QUEST_START_SID")
  add_message_with_pause("WEAVER_QUEST_START2_SID")
  clear_and_add_message("WEAVER_QUEST_START3_SID")
end

local function weaver_completion_condition_fn()
  return ((get_item_count(PLAYER_ID, WHITEFLOWER_ID) >= 5) and
          (get_item_count(PLAYER_ID, CYAN_WILDFLOWER_ID) >= 5))
end

local function weaver_completion_fn()
  remove_object_from_player(WHITEFLOWER_ID, 5)
  remove_object_from_player(CYAN_WILDFLOWER_ID, 5)

  add_message("WEAVER_QUEST_COMPLETE_SID")
  local ids = {LIGHTNING_WAND_ID, TELEPORT_WAND_ID, GAIN_ATTRIBUTES_POTION_ID}
  local idx = RNG_range(1, #ids)
  local id = ids[idx]
  log(CLOG_ERROR, "Idx is " .. tostring(idx))
  add_object_to_player_tile(id)
  add_object_to_player_tile(STONEFLOWER_ID)

  Quest:try_additional_quest_reward()
  
  return true
end

local q_id = "weaver_" .. cr_id

weaver_quest = Quest:new(q_id, 
                         "WEAVER_QUEST_TITLE_SID", 
                         "WEAVER_SHORT_DESCRIPTION_SID", 
                         "WEAVER_QUEST_DESCRIPTION_SID", 
                         "WEAVER_QUEST_COMPLETE_SID", 
                         "WEAVER_QUEST_REMINDER_SID", 
                         truefn,
                         weaver_start_fn, 
                         weaver_completion_condition_fn, 
                         weaver_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, q_id, 20)

if do_quest == true then
  do_quest = weaver_quest:execute()
end

if do_quest == false then
  clear_and_add_message("WEAVER_SPEECH_TEXT_SID")
end

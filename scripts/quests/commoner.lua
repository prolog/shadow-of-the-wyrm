require('common_quests')
require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Commoner quest details
local function commoner_start_fn()
  add_message_with_pause("COMMONER_QUEST_START_SID")
  clear_and_add_message("COMMONER_QUEST_START2_SID")
end

local function commoner_completion_condition_fn()
  return (player_has_item(BREAD_ID))
end

local function commoner_completion_fn()
  remove_object_from_player(BREAD_ID)
  add_piety(PLAYER_ID, 1000)
  
  add_message("COMMONER_QUEST_COMPLETE_SID")
  return true
end

local q_id = "commoner_" .. cr_id

commoner_quest = Quest:new(q_id, 
                           "COMMONER_QUEST_TITLE_SID", 
                           "COMMONER_SHORT_DESCRIPTION_SID", 
                           "COMMONER_QUEST_DESCRIPTION_SID", 
                           "COMMONER_QUEST_COMPLETE_SID", 
                           "COMMONER_QUEST_REMINDER_SID", 
                           truefn,
                           commoner_start_fn, 
                           commoner_completion_condition_fn, 
                           commoner_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, q_id, 20)

if do_quest == true then
  do_quest = commoner_quest:execute()
end

if do_quest == false then
  do_quest = CommonQuests:do_quests(cr_id)
end

if do_quest == false then
  clear_and_add_message("COMMONER_SPEECH_TEXT_SID")
end

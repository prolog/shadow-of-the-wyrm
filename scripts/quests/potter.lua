require('common_quests')
require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Potter quest details
local function potter_start_fn()
  add_message_with_pause("POTTER_QUEST_START_SID")
  add_message_with_pause("POTTER_QUEST_START2_SID")
  clear_and_add_message("POTTER_QUEST_START3_SID")
end

local function potter_completion_condition_fn()
  return (get_item_count(PLAYER_ID, CLAY_ID) >= 12)
end

local function potter_completion_fn()
  remove_object_from_player(CLAY_ID, 12)
  
  add_message("POTTER_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(30, 50))
  add_object_to_player_tile(FIRE_BOMB_ID, RNG_range(3, 5))
  add_object_to_player_tile(SHADOW_BOMB_ID, RNG_range(3, 5))
  Quest:try_additional_quest_reward()
  
  return true
end

potter_quest = Quest:new("potter_" .. cr_id, 
                         "POTTER_QUEST_TITLE_SID", 
                         "POTTER_SHORT_DESCRIPTION_SID", 
                         "POTTER_QUEST_DESCRIPTION_SID", 
                         "POTTER_QUEST_COMPLETE_SID", 
                         "POTTER_QUEST_REMINDER_SID", 
                         truefn,
                         potter_start_fn, 
                         potter_completion_condition_fn, 
                         potter_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 15)

if do_quest == true then
  do_quest = potter_quest:execute()
end

if do_quest == false then
  do_quest = CommonQuests:do_quests(cr_id)
end

if do_quest == false then
  clear_and_add_message(get_creature_speech_text_sid(cr_id))
end

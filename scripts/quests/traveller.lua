require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Traveller quest details
local function traveller_start_fn()
  add_message_with_pause("TRAVELLER_QUEST_START_SID")
  add_message_with_pause("TRAVELLER_QUEST_START2_SID")
  clear_and_add_message("TRAVELLER_QUEST_START3_SID")
end

local function traveller_completion_condition_fn()
  return player_has_item(IRON_HELM_ID)
end

local function traveller_completion_fn()
  remove_object_from_player(IRON_HELM_ID)
  add_message("TRAVELLER_QUEST_COMPLETE_SID")

  local objs = {UNCURSING_SCROLL_ID, SPEED_POTION_ID, RAGE_POTION_ID, ETHER_POTION_ID}
  local cnt = 0

  for i,v in ipairs(objs) do
    local amount = RNG_range(0, 2)
    cnt = cnt + amount

    if amount > 0 then
      add_object_to_player_tile(v, amount)
    end
  end

  if cnt == 0 then
    add_object_to_player_tile(ENCHANTING_SCROLL_ID, 2)
  end
  
  Quest:try_additional_quest_reward()
  
  return true
end

traveller_quest = Quest:new("traveller_" .. cr_id, 
                            "TRAVELLER_QUEST_TITLE_SID", 
                            "TRAVELLER_SHORT_DESCRIPTION_SID", 
                            "TRAVELLER_QUEST_DESCRIPTION_SID", 
                            "TRAVELLER_QUEST_COMPLETE_SID", 
                            "TRAVELLER_QUEST_REMINDER_SID", 
                            truefn,
                            traveller_start_fn, 
                            traveller_completion_condition_fn, 
                            traveller_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 30)

if do_quest == true then
  do_quest = traveller_quest:execute()
end

if do_quest == false then
  clear_and_add_message("TRAVELLER_SPEECH_TEXT_SID")
end

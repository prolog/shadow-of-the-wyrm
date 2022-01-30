require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

function add_additional_quest_reward()
  local item_id = nil
  
  if RNG_percent_chance(10) then
    if RNG_percent_chance(80) then
      if RNG_percent_chance(50) then
        item_id = GOLDEN_APPLE_ID
      else
        item_id = SILVER_APPLE_ID
      end
    else
      if RNG_percent_chance(50) then
        item_id = ENCHANTING_SCROLL_ID
      else
        item_id = GAIN_ATTRIBUTES_POTION_ID
      end
    end
  end

  if item_id ~= nil then
    add_object_to_player_tile(item_id)
  end
end

function run_probabilistic_quest(cr_id, quest_p)
  local cr_qid = get_creature_additional_property(cr_id, CREATURE_QUEST_GUID)
  local run_quest = false
  local chance = 15

  if quest_p ~= nil then
    chance = quest_p
  end

  if cr_qid == "" then
    if RNG_percent_chance(chance) then
      set_creature_additional_property(cr_id, CREATURE_QUEST_GUID, "1")
      run_quest = true
    else
      set_creature_additional_property(cr_id, CREATURE_QUEST_GUID, "0")
    end
  else
    run_quest = (cr_qid == "1")
  end

  return run_quest
end

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
  add_additional_quest_reward()
  
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

local do_quest = run_probabilistic_quest(cr_id, 15)

if do_quest == true then
  do_quest = trades_quest:execute()
end

if do_quest == false then
  clear_and_add_message("TRADESMAN_SPEECH_TEXT_SID")
end


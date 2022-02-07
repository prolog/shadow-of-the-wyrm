require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Jeweler quest details
local function jeweler_start_fn()
  add_message_with_pause("JEWELER_QUEST_START_SID")
  add_message_with_pause("JEWELER_QUEST_START2_SID")
  clear_and_add_message("JEWELER_QUEST_START3_SID")
end

local function jeweler_completion_condition_fn()
  return ((player_has_item(LUMP_GOLD_ID)) and
          (player_has_item(MAGICI_SHARD_ID)))
end

local function jeweler_completion_fn()
  remove_object_from_player(LUMP_GOLD_ID)
  remove_object_from_player(MAGICI_SHARD_ID)

  add_message("JEWELER_QUEST_COMPLETE_SID")

  local rewards = {RING_FLAME_ID, RING_ICE_ID, RING_ACID_ID, RING_HOLINESS_ID}
  add_object_to_player_tile(rewards[RNG_range(1, #rewards)], 1, "", RNG_range(2, 3))
  Quest:try_additional_quest_reward()
  
  return true
end

jeweler_quest = Quest:new("jeweler_" .. cr_id, 
                          "JEWELER_QUEST_TITLE_SID", 
                          "JEWELER_SHORT_DESCRIPTION_SID", 
                          "JEWELER_QUEST_DESCRIPTION_SID", 
                          "JEWELER_QUEST_COMPLETE_SID", 
                          "JEWELER_QUEST_REMINDER_SID", 
                          truefn,
                          jeweler_start_fn, 
                          jeweler_completion_condition_fn, 
                          jeweler_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, 20)

if do_quest == true then
  do_quest = jeweler_quest:execute()
end

if do_quest == false then
  clear_and_add_message("JEWELER_SPEECH_TEXT_SID")
end

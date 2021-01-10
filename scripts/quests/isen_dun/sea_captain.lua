require('constants')
require('quest')

-- All of the sea-captain's quests require a companion. Animals/dragons/
-- etc don't count!
local function sea_captain_precondition_fn()
  local h_foll = creature_has_humanoid_followers(PLAYER_ID)

  if h_foll == false then
    add_message_with_pause("SEA_CAPTAIN_NO_COMPANION_SID")
  end

  return h_foll
end

-- First quest: gold to whaling's end for ivory
local function whaling_start_fn()
  add_message_with_pause("SEA_CAPTAIN_WHALING_QUEST_START_SID")
  add_message_with_pause("SEA_CAPTAIN_WHALING_QUEST_START2_SID")
  clear_and_add_message("SEA_CAPTAIN_WHALING_QUEST_START3_SID")

  add_object_to_player_tile(LUMP_GOLD_ID, 4)
end

local function whaling_completion_condition_fn()
  local tusks = get_item_count(PLAYER_ID, IVORY_TUSK_ID)
  return (tusks >= 6)
end

local function whaling_completion_fn()
  remove_object_from_player(IVORY_TUSK_ID, 6)
  add_message("SEA_CAPTAIN_WHALING_QUEST_COMPLETE_SID")

  add_object_to_player_tile(UNSTONING_POTION_ID, RNG_range(2,3))
  add_object_to_player_tile(ANTIDOTE_POTION_ID, RNG_range(2,3))

  return true
end

whaling_quest = Quest:new("sea_captain_whalings_end",
                          "SEA_CAPTAIN_WHALING_QUEST_TITLE_SID",
                          "SEA_CAPTAIN_SHORT_DESCRIPTION_SID",
                          "SEA_CAPTAIN_WHALING_QUEST_DESCRIPTION_SID",
                          "SEA_CAPTAIN_WHALING_QUEST_COMPLETE_SID",
                          "SEA_CAPTAIN_WHALING_QUEST_REMINDER_SID",
                          sea_captain_precondition_fn,
                          whaling_start_fn,
                          whaling_completion_condition_fn,
                          whaling_completion_fn)

if whaling_quest:execute() == false then
  clear_and_add_message("SEA_CAPTAIN_SPEECH_TEXT_SID")
end


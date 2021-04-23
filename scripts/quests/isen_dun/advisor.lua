require('constants')
require('quest')

-- Edgar's quests require companions; envoys from Isen Dun are always
-- sent in groups.
local function edgar_precondition_fn()
  local has_fol = false
  local cnt = count_creature_humanoid_followers(PLAYER_ID)

  if cnt == 0 then
    add_message_with_pause("ADVISOR_NOT_ENOUGH_COMPANIONS_SID")
  else
    has_fol = true
  end

  return has_fol
end

-- First quest: deliver a cask of whisky to Yew
local function edgar_yew_start_fn()
  add_message_with_pause("HRIMGAR_ADVISOR_YEW_QUEST_START_SID")
  add_message_with_pause("HRIMGAR_ADVISOR_YEW_QUEST_START2_SID")
  clear_and_add_message("HRIMGAR_ADVISOR_YEW_QUEST_START3_SID")
  
  add_object_to_player_tile("isen_dun_whisky")
end

local function edgar_yew_completion_condition_fn()
  return (get_creature_additional_property(PLAYER_ID, QUEST_ISEN_DUN_YEW_COMPLETE) == "1")
end

local function edgar_yew_completion_fn()
  remove_creature_additional_property(PLAYER_ID, QUEST_ISEN_DUN_YEW_COMPLETE)
  
  add_message("HRIMGAR_ADVISOR_YEW_QUEST_COMPLETE_SID")

  add_object_to_player_tile(GOLDEN_APPLE_ID, RNG_range(1,2))
  add_object_to_player_tile(SILVER_APPLE_ID, RNG_range(1,2))

  return true
end

yew_quest = Quest:new("hrimgar_advisor_yew",
                      "HRIMGAR_ADVISOR_YEW_QUEST_TITLE_SID",
		      "ADVISOR_SHORT_DESCRIPTION_SID",
		      "HRIMGAR_ADVISOR_YEW_QUEST_DESCRIPTION_SID",
		      "HRIMGAR_ADVISOR_YEW_QUEST_COMPLETE_SID",
		      "HRIMGAR_ADVISOR_YEW_QUEST_REMINDER_SID",
		      edgar_precondition_fn,
		      edgar_yew_start_fn,
		      edgar_yew_completion_condition_fn,
		      edgar_yew_completion_fn)

if yew_quest:execute() == false then
  clear_and_add_message("ADVISOR_SPEECH_TEXT_SID")
end
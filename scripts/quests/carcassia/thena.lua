require('constants')
require('quest')

local function thena_selrin_start_fn()
  add_message_with_pause("THENA_SELRIN_QUEST_START_SID")
  add_message_with_pause("THENA_SELRIN_QUEST_START2_SID")
  add_message_with_pause("THENA_SELRIN_QUEST_START3_SID")
  add_message_with_pause("THENA_SELRIN_QUEST_START4_SID")
  clear_and_add_message("THENA_SELRIN_QUEST_START5_SID")
end

local function thena_selrin_completion_condition_fn()
  return player_has_item(SELRIN_BANDANA_ID)
end

local function thena_selrin_completion_fn()
  add_message_with_pause("THENA_SELRIN_QUEST_COMPLETE_SID")
  add_message_with_pause("THENA_SELRIN_QUEST_COMPLETE2_SID")
  clear_and_add_message("THENA_SELRIN_QUEST_COMPLETE3_SID")

  remove_object_from_player(SELRIN_BANDANA_ID)
  add_object_to_player_tile(GOLDEN_APPLE_ID, RNG_range(1,3))
  add_object_to_player_tile(SILVER_APPLE_ID, RNG_range(1,3))
  add_object_to_player_tile(ENCHANTING_SCROLL_ID, RNG_range(1,3))

  return true
end

thena_selrin_quest = Quest:new("thena_selrin",
                               "THENA_SELRIN_QUEST_TITLE_SID",
			       "THENA_SHORT_DESCRIPTION_SID",
			       "THENA_SELRIN_QUEST_DESCRIPTION_SID",
			       "THENA_SELRIN_QUEST_COMPLETE_SID",
			       "THENA_SELRIN_QUEST_REMINDER_SID",
			       truefn,
			       thena_selrin_start_fn,
			       thena_selrin_completion_condition_fn,
			       thena_selrin_completion_fn)

if thena_selrin_quest:execute() == false then
  clear_and_add_message("THENA_SPEECH_TEXT_SID")
end

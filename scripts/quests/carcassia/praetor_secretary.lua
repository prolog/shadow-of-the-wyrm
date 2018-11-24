require('constants')
require('quest')

local function secretary_writing_start_fn()
  add_message_with_pause("PRAETOR_SECRETARY_WRITING_QUEST_START_SID")
  add_message_with_pause("PRAETOR_SECRETARY_WRITING_QUEST_START2_SID")
  clear_and_add_message("PRAETOR_SECRETARY_WRITING_QUEST_START3_SID")
end

local function secretary_writing_completion_condition_fn()
  return (get_item_count(PLAYER_ID, QUILL_ID) >= 6 and get_item_count(PLAYER_ID, INKPOT_ID) >= 3)
end

local function secretary_writing_completion_fn()
  add_message_with_pause("PRAETOR_SECRETARY_WRITING_QUEST_COMPLETE_SID")
  clear_and_add_message("PRAETOR_SECRETARY_WRITING_QUEST_COMPLETE2_SID")

  remove_object_from_player(QUILL_ID, 6)
  remove_object_from_player(INKPOT_ID, 3)
  add_object_to_player_tile(CURRENCY_ID, RNG_range(200, 300))
  add_object_to_player_tile("carcassia_praetor_key")

  return true
end

secretary_writing_quest = Quest:new("secretary_writing",
                                    "PRAETOR_SECRETARY_WRITING_QUEST_TITLE_SID",
                                    "PRAETOR_SECRETARY_SHORT_DESCRIPTION_SID",
                                    "PRAETOR_SECRETARY_WRITING_QUEST_DESCRIPTION_SID",
                                    "PRAETOR_SECRETARY_WRITING_QUEST_COMPLETE_SID",
                                    "PRAETOR_SECRETARY_WRITING_QUEST_REMINDER_SID",
                                    truefn,
                                    secretary_writing_start_fn,
                                    secretary_writing_completion_condition_fn,
                                    secretary_writing_completion_fn)

if secretary_writing_quest:execute() == false then
  clear_and_add_message("PRAETOR_SECRETARY_SPEECH_TEXT_SID")
end


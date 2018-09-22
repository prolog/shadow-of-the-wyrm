require('constants')
require('quest')

local function scullerymaid_booze_start_fn()
  add_message_with_pause("PRAETOR_SCULLERYMAID_BOOZE_QUEST_START_SID")
  clear_and_add_message("PRAETOR_SCULLERYMAID_BOOZE_QUEST_START2_SID")
end

local function scullerymaid_booze_completion_condition_fn()
  return player_has_item(ELVEN_BRANDY_ID) == true
end

local function scullerymaid_booze_completion_fn()
  add_message_with_pause("PRAETOR_SCULLERYMAID_BOOZE_QUEST_COMPLETE_SID")
  clear_and_add_message("PRAETOR_SCULLERYMAID_BOOZE_QUEST_COMPLETE2_SID")

  remove_object_from_player(ELVEN_BRANDY_ID)
  add_object_to_player_tile(SILVER_APPLE_ID)
  add_object_to_player_tile("carcassia_scullerymaid_key")

  return true
end

scullerymaid_booze_quest = Quest:new("scullerymaid_booze",
                                     "PRAETOR_SCULLERYMAID_BOOZE_QUEST_TITLE_SID",
                                     "PRAETOR_SCULLERYMAID_SHORT_DESCRIPTION_SID",
                                     "PRAETOR_SCULLERYMAID_BOOZE_QUEST_DESCRIPTION_SID",
                                     "PRAETOR_SCULLERYMAID_BOOZE_QUEST_COMPLETE_SID",
                                     "PRAETOR_SCULLERYMAID_BOOZE_QUEST_REMINDER_SID",
                                     truefn,
                                     scullerymaid_booze_start_fn,
                                     scullerymaid_booze_completion_condition_fn,
                                     scullerymaid_booze_completion_fn)

if scullerymaid_booze_quest:execute() == false then
  clear_and_add_message("PRAETOR_SCULLERYMAID_SPEECH_TEXT_SID")
end


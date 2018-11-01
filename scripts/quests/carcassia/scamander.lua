require('constants')
require('quest')

local function scamander_start_fn()
  add_message_with_pause("SCAMANDER_QUEST_START_SID")
  add_message_with_pause("SCAMANDER_QUEST_START2_SID")
  clear_and_add_message("SCAMANDER_QUEST_START3_SID")
end

local function scamander_completion_condition_fn()
  return (get_num_uniques_killed_global() >= 3)
end

local function scamander_completion_fn()
  clear_and_add_message("SCAMANDER_QUEST_COMPLETE_SID")

  add_object_to_player_tile("carcassia_armory_key")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(10, 30))

  return true
end

scamander_quest = Quest:new("scamander_uniques",
                            "SCAMANDER_QUEST_TITLE_SID",
                            "SCAMANDER_SHORT_DESCRIPTION_SID",
                            "SCAMANDER_QUEST_DESCRIPTION_SID",
                            "SCAMANDER_QUEST_COMPLETE_SID",
                            "SCAMANDER_QUEST_REMINDER_SID",
                            truefn,
                            scamander_start_fn,
                            scamander_completion_condition_fn,
                            scamander_completion_fn)

if scamander_quest:execute() == false then
  clear_and_add_message("SCAMANDER_SPEECH_TEXT_SID")
end

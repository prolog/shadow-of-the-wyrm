require('constants')
require('quest')

local function dantus_ironsword_start_fn()
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_START_SID")
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_START2_SID")
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_START3_SID")
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_START4_SID")
  clear_and_add_message("PRAETOR_DANTUS_IRONSWORD_QUEST_START5_SID")
end

local function dantus_ironsword_completion_condition_fn()
  local player_emp_gift = get_creature_additional_property(PLAYER_ID, "emperor_gift_generated")

  return player_emp_gift == "1"
end

local function dantus_ironsword_completion_fn()
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_COMPLETE_SID")
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_COMPLETE2_SID")
  add_message_with_pause("PRAETOR_DANTUS_IRONSWORD_QUEST_COMPLETE3_SID")
  clear_and_add_message("PRAETOR_DANTUS_IRONSWORD_QUEST_COMPLETE4_SID")

  add_object_to_player_tile(GOLDEN_APPLE_ID, RNG_range(1,3))
  add_object_to_player_tile(SILVER_APPLE_ID, RNG_range(1,3))
  add_object_to_player_tile(GAIN_ATTRIBUTES_POTION_ID, RNG_range(1,3))

  return true
end

dantus_ironsword_quest = Quest:new("dantus_ironsword",
                                   "PRAETOR_DANTUS_IRONSWORD_QUEST_TITLE_SID",
                                   "PRAETOR_DANTUS_SHORT_DESCRIPTION_SID",
                                   "PRAETOR_DANTUS_IRONSWORD_QUEST_DESCRIPTION_SID",
                                   "PRAETOR_DANTUS_IRONSWORD_QUEST_COMPLETE_SID",
                                   "PRAETOR_DANTUS_IRONSWORD_QUEST_REMINDER_SID",
                                   truefn,
                                   dantus_ironsword_start_fn,
                                   dantus_ironsword_completion_condition_fn,
                                   dantus_ironsword_completion_fn)

if dantus_ironsword_quest:execute() == false then
  clear_and_add_message("PRAETOR_DANTUS_SPEECH_TEXT_SID")
end

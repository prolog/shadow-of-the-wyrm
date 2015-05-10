require('quest')

-- Quest to kill at least four uniques.
local function wispe_uniques_start_fn()
  add_message_with_pause("WISPE_UNIQUES_QUEST_START_SID")
  add_message_with_pause("WISPE_UNIQUES_QUEST_START2_SID")
  clear_and_add_message("WISPE_UNIQUES_QUEST_START3_SID")
end

local function wispe_uniques_completion_condition_fn()
  return (get_num_uniques_killed_global() >= 3)
end

local function wispe_uniques_completion_fn()
  add_message_with_pause("WISPE_UNIQUES_QUEST_COMPLETE_SID")
  add_message_with_pause("WISPE_UNIQUES_QUEST_COMPLETE2_SID")
  clear_and_add_message("WISPE_UNIQUES_QUEST_COMPLETE3_SID")
  add_object_to_player_tile("bloodsinger")

  return true
end

uniques_quest = Quest:new("wispe_uniques_quest",
                           "WISPE_UNIQUES_QUEST_TITLE_SID",
                           "WISPE_DESCRIPTION_SID",
                           "WISPE_UNIQUES_QUEST_DESCRIPTION_SID",
                           "WISPE_UNIQUES_QUEST_COMPLETE_SID",
                           "WISPE_UNIQUES_QUEST_REMINDER_SID",
                           truefn,
                           wispe_uniques_start_fn,
                           wispe_uniques_completion_condition_fn,
                           wispe_uniques_completion_fn)

if uniques_quest:execute() == false then
  add_message("WISPE_SPEECH_TEXT_SID")
end


require('quest')

-- Wintersea Keep quest details
local function cynwise_wintersea_start_fn()
  add_message_with_pause("CYNWISE_WINTERSEA_QUEST_START_SID")
  add_message_with_pause("CYNWISE_WINTERSEA_QUEST_START2_SID")
  add_message("CYNWISE_WINTERSEA_QUEST_START3_SID")
end

local function cynwise_wintersea_completion_condition_fn()
  return player_has_item("silver_branch") == true
end

local function cynwise_wintersea_completion_fn()
  add_message("CYNWISE_WINTERSEA_QUEST_COMPLETE_SID")
  -- Add new item here!
  remove_object_from_player("silver_branch")
end

cynwise_quest = Quest:new("cynwise_wintersea",
                         "CYNWISE_WINTERSEA_QUEST_TITLE_SID",
                         "CYNWISE_DESCRIPTION_SID",
                         "CYNWISE_WINTERSEA_DESCRIPTION_SID",
                         "CYNWISE_WINTERSEA_QUEST_COMPLETE_SID",
                         "CYNWISE_WINTERSEA_QUEST_REMINDER_SID",
                         truefn,
                         cynwise_wintersea_start_fn,
                         cynwise_wintersea_completion_condition_fn,
                         cynwise_wintersea_completion_fn)

if cynwise_quest:execute() == false then
  add_message("CYNWISE_SPEECH_TEXT_SID")
end

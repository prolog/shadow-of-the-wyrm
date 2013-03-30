require('quest')

-- Sun Gem quest details
local function sun_gem_start_fn()
  add_message_with_pause("PLOUGHMAN_SUNGEM_QUEST_START_SID")
  add_message_with_pause("PLOUGHMAN_SUNGEM_QUEST_START2_SID")
  add_message("PLOUGHMAN_SUNGEM_QUEST_START3_SID")
end

local function sun_gem_completion_condition_fn()
  return player_has_item("sun_gem") == true
end

local function sun_gem_completion_fn()
  add_message("PLOUGHMAN_SUNGEM_QUEST_COMPLETE_SID")
  add_object_to_player_tile("silverweed", 15)
  remove_object_from_player("sun_gem")
  remove_active_quest("blacksmith_sungem")
end

sungem_quest = Quest:new("ploughman_sungem",
                         "PLOUGHMAN_SUNGEM_QUEST_TITLE_SID",
                         "THE_PLOUGHMAN_DESCRIPTION_SID",
                         "PLOUGHMAN_SUNGEM_DESCRIPTION_SID",
                         "PLOUGHMAN_SUNGEM_QUEST_COMPLETE_SID",
                         "PLOUGHMAN_SUNGEM_QUEST_REMINDER_SID",
                         truefn,
                         sun_gem_start_fn,
                         sun_gem_completion_condition_fn,
                         sun_gem_completion_fn)

if sungem_quest:execute() == false then
  add_message("THE_PLOUGHMAN_SPEECH_TEXT_SID")
end

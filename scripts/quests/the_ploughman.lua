require('quest')
require('constants')

-- Sun Gem quest details
local function sun_gem_start_fn()
  add_message_with_pause("PLOUGHMAN_SUNGEM_QUEST_START_SID")
  add_message_with_pause("PLOUGHMAN_SUNGEM_QUEST_START2_SID")
  clear_and_add_message("PLOUGHMAN_SUNGEM_QUEST_START3_SID")
end

-- Don't allow the ploughman's quest to be requested if the corresponding
-- quest from the blacksmith has already been completed.
local function plough_sun_gem_precond_fn()
  return not ((is_quest_completed("blacksmith_sungem")) or
              (is_quest_completed("cynwise_sungem")))
end

local function sun_gem_completion_condition_fn()
  return player_has_item(SUN_GEM_ID) == true
end

local function sun_gem_completion_fn()
  add_message("PLOUGHMAN_SUNGEM_QUEST_COMPLETE_SID")
  add_object_to_player_tile("silverweed", 15)
  remove_object_from_player(SUN_GEM_ID)
  remove_active_quest("blacksmith_sungem")
  remove_active_quest("cynwise_sungem")
  return true
end

sungem_quest = Quest:new("ploughman_sungem",
                         "PLOUGHMAN_SUNGEM_QUEST_TITLE_SID",
                         "THE_PLOUGHMAN_DESCRIPTION_SID",
                         "PLOUGHMAN_SUNGEM_DESCRIPTION_SID",
                         "PLOUGHMAN_SUNGEM_QUEST_COMPLETE_SID",
                         "PLOUGHMAN_SUNGEM_QUEST_REMINDER_SID",
                         plough_sun_gem_precond_fn,
                         sun_gem_start_fn,
                         sun_gem_completion_condition_fn,
                         sun_gem_completion_fn)

if sungem_quest:execute() == false then
  add_message("THE_PLOUGHMAN_SPEECH_TEXT_SID")
end

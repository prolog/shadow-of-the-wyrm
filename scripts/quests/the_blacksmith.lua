require('quest')

-- Sun Gem quest details
--
-- The blacksmith's sun gem quest is inaccessible once the ploughman's
-- quest has been completed.  The player can actually get both quests
-- if both are requested prior to completion, but only one can actually
-- be completed.
local function blacksmith_sun_gem_precond_fn()
  return not is_quest_completed("ploughman_sungem")
end

local function sun_gem_start_fn()
  add_message_with_pause("BLACKSMITH_SUNGEM_QUEST_START_SID")
  add_message_with_pause("BLACKSMITH_SUNGEM_QUEST_START2_SID")
  clear_and_add_message("BLACKSMITH_SUNGEM_QUEST_START3_SID")
end

local function sun_gem_completion_condition_fn()
  return ((player_has_item("sun_gem") == true) or (get_num_creature_killed_global("the_ploughman") > 0))
end

local function sun_gem_completion_fn()
  if (player_has_item("sun_gem")) then
    -- Player did the quest
    add_message("BLACKSMITH_SUNGEM_QUEST_COMPLETE_SID")
  else
    -- Player murdered the ploughman!
    add_message_with_pause("BLACKSMITH_SUNGEM_QUEST_COMPLETE_MURDER_SID")
    clear_and_add_message("BLACKSMITH_SUNGEM_QUEST_COMPLETE_MURDER2_SID")
  end

  add_object_to_player_tile("forger")
  remove_object_from_player("sun_gem")
  remove_active_quest("ploughman_sungem")

  if creature_is_class("player", "smith") == true then
    add_object_to_player_tile("_iron_ingot", 2)
    add_object_to_player_tile("_steel_ingot")
    add_message("BLACKSMITH_SUNGEM_QUEST_COMPLETE_SMITH_SID")
  end

  return true
end

sungem_quest = Quest:new("blacksmith_sungem",
                         "BLACKSMITH_SUNGEM_QUEST_TITLE_SID",
                         "THE_BLACKSMITH_DESCRIPTION_SID",
                         "BLACKSMITH_SUNGEM_DESCRIPTION_SID",
                         "BLACKSMITH_SUNGEM_QUEST_COMPLETE_SID",
                         "BLACKSMITH_SUNGEM_QUEST_REMINDER_SID",
                         blacksmith_sun_gem_precond_fn,
                         sun_gem_start_fn,
                         sun_gem_completion_condition_fn,
                         sun_gem_completion_fn)

if sungem_quest:execute() == false then
  add_message("THE_BLACKSMITH_SPEECH_TEXT_SID")
end

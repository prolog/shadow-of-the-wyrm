require('quest')

-- A quest to clear Stonewall of the goblin sea-captain.
local function kirin_goblin_start_fn()
  add_message_with_pause("KIRIN_GOBLIN_QUEST_START_SID")
  add_message_with_pause("KIRIN_GOBLIN_QUEST_START2_SID")
  clear_and_add_message("KIRIN_GOBLIN_QUEST_START3_SID")
  add_object_to_player_tile("goblincrusher")
end

local function kirin_goblin_completion_condition_fn()
  return (get_num_creature_killed_global("akojo") > 0)
end

local function kirin_goblin_completion_fn()
  add_message_with_pause("KIRIN_GOBLIN_QUEST_COMPLETE_SID")
  add_message_with_pause("KIRIN_GOBLIN_QUEST_COMPLETE2_SID")
  clear_and_add_message("KIRIN_GOBLIN_QUEST_COMPLETE3_SID")
  add_object_to_player_tile("silari")
  return true
end

kirin_goblin_quest = Quest:new("kirin_goblin",
                               "KIRIN_GOBLIN_QUEST_TITLE_SID",
                               "KIRIN_DESCRIPTION_SID",
                               "KIRIN_GOBLIN_DESCRIPTION_SID",
                               "KIRIN_GOBLIN_QUEST_COMPLETE_SID",
                               "KIRIN_GOBLIN_QUEST_REMINDER_SID",
                               truefn,
                               kirin_goblin_start_fn,
                               kirin_goblin_completion_condition_fn,
                               kirin_goblin_completion_fn)

if kirin_goblin_quest:execute() == false then
  add_message("KIRIN_SPEECH_TEXT_SID")
end


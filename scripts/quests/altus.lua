require('quest')

-- Quest to retrieve the rune stone and defeat the sorceror Zaeda.
local function altus_quest_start_fn()
  add_message_with_pause("ALTUS_QUEST_START_SID")
  add_message_with_pause("ALTUS_QUEST_START2_SID")
  clear_and_add_message("ALTUS_QUEST_START3_SID")
end

local function altus_quest_completion_condition_fn()
  -- JCD FIXME: At some point, it would be nice to have the victory
  -- condition require that Zaeda be defeated within some sort of time
  -- frame - maybe a day or two - before Altus succumbs to the poison.
  return (get_num_creature_killed_global("zaeda") > 0)
end

local function altus_quest_completion_fn()
  add_message_with_pause("ALTUS_QUEST_COMPLETE_SID")
  clear_and_add_message("ALTUS_QUEST_COMPLETE2_SID")

  add_object_to_player_tile("lora")
  return true
end

altus_tower_quest = Quest:new("altus_quest",
                              "ALTUS_QUEST_TITLE_SID",
                              "ALTUS_DESCRIPTION_SID",
                              "ALTUS_QUEST_DESCRIPTION_SID",
                              "ALTUS_QUEST_COMPLETE_SID",
                              "ALTUS_QUEST_REMINDER_SID",
                              truefn,
                              altus_quest_start_fn,
                              altus_quest_completion_condition_fn,
                              altus_quest_completion_fn)

if altus_tower_quest:execute() == false then
  add_message("ALTUS_SPEECH_TEXT_SID")
end


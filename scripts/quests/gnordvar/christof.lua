require('quest')

-- Mine-clearing quest details
local function christof_mine_start_fn()
  add_message_with_pause("CHRISTOF_MINE_QUEST_START_SID")
  add_message_with_pause("CHRISTOF_MINE_QUEST_START2_SID")
  clear_and_add_message("CHRISTOF_MINE_QUEST_START3_SID")
end

local function christof_mine_completion_condition_fn()
  return (get_num_creature_killed_global("black_manticore") > 0)
end

local function christof_mine_completion_fn()
  add_message_with_pause("CHRISTOF_MINE_QUEST_COMPLETE_SID")
  clear_and_add_message("CHRISTOF_MINE_QUEST_COMPLETE2_SID")
  add_object_to_player_tile("stonespear")
  add_object_to_player_tile("shockwave_spellbook")
  return true
end

christof_mine_quest = Quest:new("christof_mine",
                                "CHRISTOF_MINE_QUEST_TITLE_SID",
                                "CHRISTOF_DESCRIPTION_SID",
                                "CHRISTOF_MINE_DESCRIPTION_SID",
                                "CHRISTOF_MINE_QUEST_COMPLETE_SID",
                                "CHRISTOF_MINE_QUEST_REMINDER_SID",
                                truefn,
                                christof_mine_start_fn,
                                christof_mine_completion_condition_fn,
                                christof_mine_completion_fn)

if christof_mine_quest:execute() == false then
  add_message("CHRISTOF_SPEECH_TEXT_SID")
end


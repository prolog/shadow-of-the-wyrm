require('quest')

-- Bandit quest details
local function bandit_start_fn()
  add_message_with_pause("HRIMGAR_SPEECH_TEXT_SID")
  add_message_with_pause("HRIMGAR_BANDIT_QUEST_START_SID")
  add_message_with_pause("HRIMGAR_BANDIT_QUEST_START2_SID")
  add_message("HRIMGAR_BANDIT_QUEST_START3_SID")
end

local function bandit_completion_condition_fn()
  return (get_num_creature_killed_global("garros") > 0)
end

local function bandit_completion_fn()
  add_message("HRIMGAR_BANDIT_QUEST_COMPLETE_SID")
  add_object_to_player_tile("boathouse_key")
end

-- Create the first quest: Bandits in the Barrow
bandit_quest = Quest:new("hrimgar_bandits", 
                         "HRIMGAR_BANDIT_QUEST_TITLE_SID", 
                         "HRIMGAR_SHORT_DESCRIPTION_SID", 
                         "HRIMGAR_BANDIT_DESCRIPTION_SID", 
                         "HRIMGAR_BANDIT_QUEST_COMPLETE_SID", 
                         "HRIMGAR_BANDIT_QUEST_REMINDER_SID", 
                         truefn,
                         bandit_start_fn, 
                         bandit_completion_condition_fn, 
                         bandit_completion_fn)

-- Wyrm quest details.
local function wyrm_start_fn()
  add_message_with_pause("HRIMGAR_WYRM_QUEST_START_SID")
  add_message_with_pause("HRIMGAR_WYRM_QUEST_START2_SID")
  add_message("HRIMGAR_WYRM_QUEST_START3_SID")
end

wyrm_quest = Quest:new("wyrm_quest",
                       "HRIMGAR_WYRM_QUEST_TITLE_SID",
                       "HRIMGAR_SHORT_DESCRIPTION_SID",
                       "HRIMGAR_WYRM_DESCRIPTION_SID",
                       "", -- Can't actually return after slaying the wyrm
                       "HRIMGAR_WYRM_QUEST_REMINDER_SID",
                       truefn,
                       wyrm_start_fn,
                       true_fn,
                       true_fn)

if bandit_quest:execute() == false then
  if wyrm_quest:execute() == false then
    add_message("HRIMGAR_SPEECH_TEXT_SID")
  end
end


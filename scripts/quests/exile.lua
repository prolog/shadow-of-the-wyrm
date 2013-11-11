require('quest')

-- Details for the exile's quest: figure out where his sister went.
local function exile_sister_start_fn()
  add_message_with_pause("EXILE_SISTER_QUEST_START_SID")
  add_message_with_pause("EXILE_SISTER_QUEST_START2_SID")
  add_message_with_pause("EXILE_SISTER_QUEST_START3_SID")
  clear_and_add_message("EXILE_SISTER_QUEST_START4_SID")
end

local function exile_sister_completion_condition_fn()
  return player_has_item("two_moon_amulet") == true
end

local function exile_sister_completion_fn()
  -- Ask the player for the amulet
  if add_confirmation_message("EXILE_SISTER_QUEST_REQUEST_AMULET_SID") then
    remove_object_from_player("two_moon_amulet")
    add_object_to_player_tile("brightblade")
    add_message_with_pause("EXILE_SISTER_QUEST_REWARD_SID")
    clear_and_add_message("EXILE_SISTER_QUEST_REWARD2_SID")
  else
    add_message("EXILE_SISTER_QUEST_RECONSIDER_SID")
    return false
  end

  return true
end

exile_quest = Quest:new("exile_sister",
                         "EXILE_SISTER_QUEST_TITLE_SID",
                         "EXILE_DESCRIPTION_SID",
                         "EXILE_SISTER_DESCRIPTION_SID",
                         "EXILE_SISTER_QUEST_COMPLETE_SID",
                         "EXILE_SISTER_QUEST_REMINDER_SID",
                         truefn,
                         exile_sister_start_fn,
                         exile_sister_completion_condition_fn,
                         exile_sister_completion_fn)

if exile_quest:execute() == false then
  add_message("EXILE_SPEECH_TEXT_SID")
end


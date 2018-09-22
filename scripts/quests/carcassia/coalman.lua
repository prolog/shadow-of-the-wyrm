require('constants')
require('quest')

local function coalman_coal_start_fn()
  add_message_with_pause("COALMAN_COAL_QUEST_START_SID")
  clear_and_add_message("COALMAN_COAL_QUEST_START2_SID")
end

local function coalman_coal_completion_condition_fn()
  return (get_item_count(PLAYER_ID, COAL_ID) >= 10)
end

local function coalman_coal_completion_fn()
  add_message_with_pause("COALMAN_COAL_QUEST_COMPLETE_SID")
  clear_and_add_message("COALMAN_COAL_QUEST_COMPLETE2_SID")

  remove_object_from_player(COAL_ID, 10)
  add_object_to_player_tile(MAGICI_SHARD_ID, 2)
  add_object_to_player_tile("carcassia_coalman_key")

  return true
end

coalman_coal_quest = Quest:new("coalman_coal",
                               "COALMAN_COAL_QUEST_TITLE_SID",
                               "COALMAN_SHORT_DESCRIPTION_SID",
                               "COALMAN_COAL_QUEST_DESCRIPTION_SID",
                               "COALMAN_COAL_QUEST_COMPLETE_SID",
                               "COALMAN_COAL_QUEST_REMINDER_SID",
                               truefn,
                               coalman_coal_start_fn,
                               coalman_coal_completion_condition_fn,
                               coalman_coal_completion_fn)

if coalman_coal_quest:execute() == false then
  clear_and_add_message("COALMAN_SPEECH_TEXT_SID")
end


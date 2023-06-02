require('constants')
require('quest')

local function varra_fae_start_fn()
  add_message_with_pause("VARRA_FAE_QUEST_START_SID")
  add_message_with_pause("VARRA_FAE_QUEST_START2_SID")
  clear_and_add_message("VARRA_FAE_QUEST_START3_SID")

  local varra_id = args[SPEAKING_CREATURE_ID]
  set_leader(varra_id, PLAYER_ID)
  order_follow(varra_id, PLAYER_ID)
end

local function varra_fae_completion_condition_fn()
  local map_id = get_current_map_id()
  return (map_id == MAP_ID_FAE_CARAVAN)
end

local function varra_fae_completion_fn()
  local num_apples = 5
  local num_golden = RNG_range(1, 4)
  local num_silver = num_apples - num_golden

  add_message_with_pause("VARRA_FAE_QUEST_COMPLETE_SID")
  clear_and_add_message("VARRA_FAE_QUEST_COMPLETE2_SID")

  add_object_to_player_tile(GOLDEN_APPLE_ID, num_golden)
  add_object_to_player_tile(SILVER_APPLE_ID, num_silve)

  local varra_id = args[SPEAKING_CREATURE_ID]
  remove_leader(varra_id)

  return true
end

varra_fae_quest = Quest:new("varra_fae",
                            "VARRA_FAE_QUEST_TITLE_SID",
                            "VARRA_SHORT_DESCRIPTION_SID",
                            "VARRA_FAE_QUEST_DESCRIPTION_SID",
                            "VARRA_FAE_QUEST_COMPLETE_SID",
                            "VARRA_FAE_QUEST_REMINDER_SID",
                            truefn,
                            varra_fae_start_fn,
                            varra_fae_completion_condition_fn,
                            varra_fae_completion_fn)

if varra_fae_quest:execute() == false then
  clear_and_add_message("VARRA_FAE_QUEST_COMPLETE_SID")
end


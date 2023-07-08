require('constants')
require('quest')

local function athel_isen_dun_start_fn()
  add_message_with_pause("ATHEL_ISEN_DUN_QUEST_START_SID")
  add_message_with_pause("ATHEL_ISEN_DUN_QUEST_START2_SID")
  clear_and_add_message("ATHEL_ISEN_DUN_QUEST_START3_SID")

  local athel_id = args[SPEAKING_CREATURE_ID]
  set_leader(athel_id, PLAYER_ID)
  order_follow(athel_id, PLAYER_ID)
end

local function athel_isen_dun_completion_condition_fn()
  local map_id = get_current_map_id()
  return (map_id == MAP_ID_ISEN_DUN)
end

local function athel_isen_dun_completion_fn()
  add_message_with_pause("ATHEL_ISEN_DUN_QUEST_COMPLETE_SID")
  clear_and_add_message("ATHEL_ISEN_DUN_QUEST_COMPLETE2_SID")

  add_object_to_player_tile(CURRENCY_ID, RNG_range(400, 700))
  add_object_to_player_tile(LONG_SPEAR_ID, 1, "", 0, 3)

  local athel_id = args[SPEAKING_CREATURE_ID]
  remove_leader(athel_id)

  return true
end

athel_id_quest = Quest:new("athel_isen_dun",
                           "ATHEL_ISEN_DUN_QUEST_TITLE_SID",
                           "ATHEL_SHORT_DESCRIPTION_SID",
                           "ATHEL_ISEN_DUN_QUEST_DESCRIPTION_SID",
                           "ATHEL_ISEN_DUN_QUEST_COMPLETE_SID",
                           "ATHEL_ISEN_DUN_QUEST_REMINDER_SID",
                           truefn,
                           athel_isen_dun_start_fn,
                           athel_isen_dun_completion_condition_fn,
                           athel_isen_dun_completion_fn)

if athel_id_quest:execute() == false then
  clear_and_add_message("ATHEL_SPEECH_TEXT_SID")
end


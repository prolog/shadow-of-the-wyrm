require('quest')

-- Quest to clear the ancient underground fortress of Cithriel.
local function caravan_master_cithriel_start_fn()
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START_SID")
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START2_SID")
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START3_SID")
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START4_SID")
  clear_and_add_message("CARAVAN_MASTER_CITHRIEL_QUEST_START5_SID")

  local pl_y, pl_x = get_creature_yx("player")
  local cur_map_id = get_current_map_id()
  
  -- 23 == TILE_TYPE_DOWN_STAIRCASE
  map_transform_tile(cur_map_id, pl_y, pl_x, 23)

  -- Add the necessary properties to the tile.
  -- ...
end

local function caravan_master_cithriel_completion_condition_fn()
  return (get_num_creature_killed_global("cithriel_summoner") == 5)
end

local function caravan_mater_cithriel_completion_fn()
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_COMPLETE_SID")
  clear_and_add_message("CARAVAN_MASTER_CITHRIEL_QUEST_COMPLETE2_SID")
  add_object_to_player_tile("erandu")
  return true
end

cithriel_quest = Quest:new("cithriel_quest",
                           "CARAVAN_MASTER_CITHRIEL_QUEST_TITLE_SID",
                           "CARAVAN_MASTER_DESCRIPTION_SID",
                           "CARAVAN_MASTER_CITHRIEL_DESCRIPTION_SID",
                           "CARAVAN_MASTER_CITHRIEL_QUEST_COMPLETE_SID",
                           "CARAVAN_MASTER_CITHRIEL_QUEST_REMINDER_SID",
                           truefn,
                           caravan_master_cithriel_start_fn,
                           caravan_master_cithriel_completion_condition_fn,
                           caravan_master_cithriel_completion_fn)

if cithriel_quest:execute() == false then
  add_message("CARAVAN_MASTER_SPEECH_TEXT_SID")
end


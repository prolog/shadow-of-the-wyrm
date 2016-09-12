require('constants')
require('quest')

local creature = require('creature')

-- Quest to clear the ancient underground fortress of Cithriel.
local function caravan_master_cithriel_start_fn()
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START_SID")
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START2_SID")
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START3_SID")
  add_message_with_pause("CARAVAN_MASTER_CITHRIEL_QUEST_START4_SID")
  clear_and_add_message("CARAVAN_MASTER_CITHRIEL_QUEST_START5_SID")

  local pl_y, pl_x = get_creature_yx(PLAYER_ID)
  local cur_map_id = get_current_map_id()
  
  -- Add the necessary properties to the tile.
  -- 23 == TILE_TYPE_DOWN_STAIRCASE
  map_transform_tile(cur_map_id, pl_y, pl_x, 23)
  map_add_tile_exit(cur_map_id, pl_y, pl_x, CDIRECTION_DOWN, "cithriel")

  -- Additional creatures should be added to Cithriel: these wander the
  -- halls, and aren't part of the creatures surrounding each summoner.
  local creatures = {{"voidling", 5, 9},
                     {"tentacled_horror", 3, 6},
                     {"demon_lord", 6, 8},
                     {"fox_maiden", 3, 5},
                     {"chaos_beast", 6, 8}}

  local creatures_csv = creature.to_csv(creatures)
  map_set_additional_property(cur_map_id, pl_y, pl_x, "MAP_PROPERTIES_INITIAL_CREATURES", creatures_csv)
end

local function caravan_master_cithriel_completion_condition_fn()
  return (get_num_creature_killed_global("black_summoner") == 5)
end

local function caravan_master_cithriel_completion_fn()
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

-- Quest to slay the four avernal giants.
local function caravan_master_caldera_start_fn()
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_START_SID")
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_START2_SID")
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_START3_SID")
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_START4_SID")
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_START5_SID")
  clear_and_add_message("CARAVAN_MASTER_CALDERA_QUEST_START6_SID")
end

local function caravan_master_caldera_completion_condition_fn()
  local weyg_killed = (get_num_creature_killed_global("weyg") > 0)
  local rhone_killed = (get_num_creature_killed_global("rhone") > 0)
  local phole_killed = (get_num_creature_killed_global("phole") > 0)
  local carne_killed = (get_num_creature_killed_global("carne") > 0)

  return (weyg_killed and rhone_killed and phole_killed and carne_killed)
end

local function caravan_master_caldera_completion_fn()
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_COMPLETE_SID")
  add_message_with_pause("CARAVAN_MASTER_CALDERA_QUEST_COMPLETE2_SID")
  clear_and_add_message("CARAVAN_MASTER_CALDERA_QUEST_COMPLETE3_SID")
  add_object_to_player_tile("eunoia")
  return true
end

caldera_quest = Quest:new("caldera_quest",
                          "CARAVAN_MASTER_CALDERA_QUEST_TITLE_SID",
                          "CARAVAN_MASTER_DESCRIPTION_SID",
                          "CARAVAN_MASTER_CALDERA_DESCRIPTION_SID",
                          "CARAVAN_MASTER_CALDERA_QUEST_COMPLETE_SID",
                          "CARAVAN_MASTER_CALDERA_QUEST_REMINDER_SID",
                          truefn,
                          caravan_master_caldera_start_fn,
                          caravan_master_caldera_completion_condition_fn,
                          caravan_master_caldera_completion_fn)


if cithriel_quest:execute() == false then
  if caldera_quest:execute() == false then
    add_message("CARAVAN_MASTER_SPEECH_TEXT_SID")
  end
end


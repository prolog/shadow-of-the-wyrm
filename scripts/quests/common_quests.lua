require('constants')
require('fn')
require('quest')

-- Common quests for various NPCs.
local function add_common_quest_reward()
  local reward_ids = {}
  
  if RNG_percent_chance(75) then
    reward_ids = {{LIGHTNING_WAND_ID, 1}, {MAGICI_SHARD_ID, RNG_range(2, 4)}, {STONEFLOWER_ID, RNG_range(2, 4)}, {CURRENCY_ID, RNG_range(20, 30)}, {UNCURSING_SCROLL_ID, RNG_range(2,3)}, {SPEED_POTION_ID, RNG_range(2, 4)}, {ETHER_POTION_ID, RNG_range(2, 4)}, {HEALING_POTION_ID, RNG_range(2,4)}}
  else
    reward_ids = {{GOLDEN_APPLE_ID, 1}, {SILVER_APPLE_ID, 1}, {ENCHANTING_SCROLL_ID, 1}, {GAIN_ATTRIBUTES_POTION_ID, 1}}
  end

  local reward = reward_ids[RNG_range(1, #reward_ids)]
  add_object_to_player_tile(reward[1], reward[2])
end

-- Long day/thirsty quest
local function thirsty_start_fn()
  clear_and_add_message("THIRSTY_QUEST_START_SID")
end

local function thirsty_completion_condition_fn()
  return player_has_item(GNOMISH_STOUT_ID)
end

local function thirsty_completion_fn()
  remove_object_from_player(GNOMISH_STOUT_ID)
  
  add_message("THIRSTY_QUEST_COMPLETE_SID")
  add_common_quest_reward()
  Quest:try_additional_quest_reward()
  
  return true
end

-- New rowboat to visit family quest.
local function rowboat_start_fn()
  add_message_with_pause("ROWBOAT_QUEST_START_SID")
  clear_and_add_message("ROWBOAT_QUEST_START2_SID")
end

local function rowboat_completion_condition_fn()
  return player_has_item(ROWBOAT_ID)
end

local function rowboat_completion_fn()
  remove_object_from_player(ROWBOAT_ID)
  
  add_message("ROWBOAT_QUEST_COMPLETE_SID")
  add_object_to_player_tile(SPEED_POTION_ID)
  add_object_to_player_tile(CURRENCY_ID, RNG_range(50, 60))
  Quest:try_additional_quest_reward()

  return true
end

-- Fish for feast quest
local function fishfeast_start_fn()
  add_message_with_pause("FISHFEAST_QUEST_START_SID")
  add_message_with_pause("FISHFEAST_QUEST_START2_SID")
  clear_and_add_message("FISHFEAST_QUEST_START3_SID")
end

local function fishfeast_completion_condition_fn()
  return (player_has_item(SALMON_ID) and player_has_item(TROUT_ID))
end

local function fishfeast_completion_fn()
  remove_object_from_player(SALMON_ID)
  remove_object_from_player(TROUT_ID)
  
  add_message("FISHFEAST_QUEST_COMPLETE_SID")
  add_object_to_player_tile(SILVERWEED_ID, RNG_range(2,4))
  
  Quest:try_additional_quest_reward()
  
  return true
end

-- Escort to a village from when they were young...
local function villagevisit_start_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local q_id = "villagevisit"
  local v_name = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_NAME_" .. q_id)
  local v_loc = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_LOCATION_" .. q_id)
  
  add_message_with_pause("VILLAGEVISIT_QUEST_START_SID", {v_name, get_sid(v_loc)})
  add_message_with_pause("VILLAGEVISIT_QUEST_START2_SID")
  clear_and_add_message("VILLAGEVISIT_QUEST_START3_SID")

  -- Follow the player
  set_leader(cr_id, PLAYER_ID)
  order_follow(cr_id, PLAYER_ID)
end

local function villagevisit_completion_condition_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local pc_y, pc_x = get_player_world_map_coords()
  local coords, name, location = Quest:get_escort_details(cr_id, "villagevisit")

  coords = tokenize(coords, "-")
  local cr_y = tonumber(coords[1])
  local cr_x = tonumber(coords[2])

  return (pc_y == cr_y and pc_x == cr_x)
end

local function villagevisit_completion_fn()
  local objs = {ENCHANTING_SCROLL_ID, GAIN_ATTRIBUTES_POTION_ID}
  local cr_id = args[SPEAKING_CREATURE_ID]

  Quest:remove_escort_details(cr_id, "villagevisit")
  remove_leader(cr_id)

  local obj = objs[RNG_range(1, #objs)]
  add_object_to_player_tile(obj)
  add_object_to_player_tile(CURRENCY_ID, RNG_range(500, 600))

  clear_and_add_message("VILLAGEVISIT_QUEST_COMPLETE_SID")
  set_creature_speech_text_sid(cr_id, "VILLAGEVISIT_SPEECH_RETURN_SID")

  return true
end

-- Escort to one of the major settlements for a job.
local function newjob_start_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local q_id = "newjob"
  local v_name = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_NAME_" .. q_id)
  local v_loc = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_LOCATION_" .. q_id)
  
  add_message_with_pause("NEWJOB_QUEST_START_SID")
  add_message_with_pause("NEWJOB_QUEST_START2_SID")
  clear_and_add_message("NEWJOB_QUEST_START3_SID", {v_name, get_sid(v_loc)})

  -- Follow the player
  set_leader(cr_id, PLAYER_ID)
  order_follow(cr_id, PLAYER_ID)
end

local function newjob_completion_condition_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local pc_y, pc_x = get_player_world_map_coords()
  local coords, name, location = Quest:get_escort_details(cr_id, "newjob")

  coords = tokenize(coords, "-")
  local cr_y = tonumber(coords[1])
  local cr_x = tonumber(coords[2])

  return (pc_y == cr_y and pc_x == cr_x)
end

local function newjob_completion_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]  
  Quest:remove_escort_details(cr_id, "newjob")

  remove_leader(cr_id)

  add_object_to_player_tile(CURRENCY_ID, RNG_range(400, 900))
  add_common_quest_reward()
  
  clear_and_add_message("NEWJOB_QUEST_COMPLETE_SID")
  set_creature_speech_text_sid(cr_id, "NEWJOB_SPEECH_RETURN_SID")

  return true
end

-- Bored, time for an adventure!  A forest! (orchards allowed)
local function adventure_forest_start_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]

  add_message_with_pause("ADVENTURE_FOREST_QUEST_START_SID")
  add_message_with_pause("ADVENTURE_FOREST_QUEST_START2_SID")
  clear_and_add_message("ADVENTURE_FOREST_QUEST_START3_SID")

  add_object_to_creature(get_current_map_id(), cr_id, SPEAR_ID)
  add_object_to_creature(get_current_map_id(), cr_id, WAYFARER_CLOTHES_ID)

  set_leader(cr_id, PLAYER_ID)
  order_follow(cr_id, PLAYER_ID)
end

local function adventure_forest_completion_condition_fn()
  local y, x = get_player_world_map_coords()
  local tile_table = map_get_tile(WORLD_MAP_ID, y, x)
  local map_type = tile_table["tile_type"]

  return (map_type == CTILE_TYPE_FOREST or map_type == CTILE_TYPE_ORCHARD)
end

local function adventure_forest_completion_fn()
  local apples = {GOLDEN_APPLE_ID, SILVER_APPLE_ID}
  local cr_id = args[SPEAKING_CREATURE_ID]

  remove_leader(cr_id)

  local apple = apples[RNG_range(1, #apples)]
  add_object_to_player_tile(apple)

  clear_and_add_message("ADVENTURE_FOREST_QUEST_COMPLETE_SID")
  set_creature_speech_text_sid(cr_id, "ADVENTURE_FOREST_SPEECH_RETURN_SID")

  return true
end

-- Bored, time for an adventure!  Somewhere underground!
local function adventure_start_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  
  add_message_with_pause("ADVENTURE_QUEST_START_SID")
  add_message_with_pause("ADVENTURE_QUEST_START2_SID")
  clear_and_add_message("ADVENTURE_QUEST_START3_SID")

  add_object_to_creature(get_current_map_id(), cr_id, SHORT_SWORD_ID)
  add_object_to_creature(get_current_map_id(), cr_id, CHAIN_SCRAPS_ID)

  -- Follow the player
  set_leader(cr_id, PLAYER_ID)
  order_follow(cr_id, PLAYER_ID)
end

local function adventure_completion_condition_fn()
  local y, x = get_creature_yx(args[SPEAKING_CREATURE_ID])
  local tile_table = map_get_tile(get_current_map_id(), y, x)
  local map_type = tile_table["map_type"]

  return map_type == CMAP_TYPE_UNDERWORLD
end

local function adventure_completion_fn()
  local objs = {SPEED_POTION_ID, SHADOW_AMULET_ID, DRAGON_BREATH_WAND_ID, LIGHTNING_WAND_ID, TELEPORT_WAND_ID, FLAME_WAND_ID, IDENTIFY_SCROLL_ID, WARPING_SCROLL_ID, ENCHANTING_SCROLL_ID, GAIN_ATTRIBUTES_POTION_ID}
  local apples = {GOLDEN_APPLE_ID, SILVER_APPLE_ID}
  local cr_id = args[SPEAKING_CREATURE_ID]

  remove_leader(cr_id)

  local obj = objs[RNG_range(1, #objs)]
  local apple = apples[RNG_range(1, #apples)]
  add_object_to_player_tile(obj)
  add_object_to_player_tile(apple)

  clear_and_add_message("ADVENTURE_QUEST_COMPLETE_SID")
  set_creature_speech_text_sid(cr_id, "ADVENTURE_SPEECH_RETURN_SID")

  return true
end

-- On the lam, being chased by Carcassian guards
local function carcassia_lam_precondition_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local qp_prop = "CARCASSIA_LAM_PRECONDITION_" .. cr_id
  local agree_quest = get_creature_additional_property(PLAYER_ID, qp_prop)
  local confirm = false

  if agree_quest ~= "1" then
    local desc = get_creature_description(PLAYER_ID, cr_id)
    confirm = add_confirmation_message("CARCASSIA_LAM_CONFIRMATION", {desc})

    if confirm == true then
      set_creature_additional_property(PLAYER_ID, qp_prop, "1")
    end
  else
    return true
  end

  return confirm
end

local function carcassia_lam_start_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local cr_desc = get_creature_description(PLAYER_ID, cr_id)
  add_message_with_pause("CARCASSIA_LAM_QUEST_START_SID", {cr_desc})
  add_message_with_pause("CARCASSIA_LAM_QUEST_START2_SID")
  add_message_with_pause("CARCASSIA_LAM_QUEST_START3_SID")
  clear_and_add_message("CARCASSIA_LAM_QUEST_START4_SID")

  -- Generate the guards
  local num_guards = RNG_range(6,15)
  local map_id = get_current_map_id()
  local cnt = 0

  while cnt < num_guards do
    local y = RNG_range(0,19)
    local x = RNG_range(0,79)

    local grd_id = add_creature_to_map(CARCASSIAN_GUARD_ID, y, x, map_id, true)
    
    if string.len(grd_id) > 0 then
      set_creature_additional_property(grd_id, QUEST_CARCASSIA_LAM_GUARD, "1")
    end

    cnt = cnt + 1
  end
end

local function carcassia_lam_completion_condition_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  local cr_prop = get_creature_additional_property(cr_id, QUEST_IN_PROGRESS)

  return cr_prop == "1" and count_creatures_with_property(QUEST_CARCASSIA_LAM_GUARD, "1", get_current_map_id()) == 0
end

local function carcassia_lam_completion_fn()
  local cr_id = args[SPEAKING_CREATURE_ID]
  clear_and_add_message("CARCASSIA_LAM_QUEST_COMPLETE_SID")
  remove_creature_additional_property(PLAYER_ID, "CARCASSIA_LAM_PRECONDITION_" .. cr_id)

  -- Create the ring, then add it to the player's tile.
  local main_dam_type = RNG_range(CDAMAGE_TYPE_SLASH, CDAMAGE_TYPE_LIGHTNING)
  local sec_dam_type = RNG_range(CDAMAGE_TYPE_SLASH, CDAMAGE_TYPE_LIGHTNING)
  local resists = fn.array_to_csv(fn.stringify_array({main_dam_type, 0.20, sec_dam_type, 0.10}))
  
  add_object_with_resists_to_player_tile(FILIGREED_RING_ID, resists)
  return true
end

-- CommonQuest module.  Used to quests that can be used by a variety of
-- NPCs.
CommonQuests = {}
CommonQuests.__index = CommonQuests

local function get_quests(cr_id, sdesc_sid)
  local thirsty_quest = Quest:new("thirsty_" .. cr_id, 
                                  "THIRSTY_QUEST_TITLE_SID", 
                                  sdesc_sid,
                                  "THIRSTY_QUEST_DESCRIPTION_SID", 
                                  "THIRSTY_QUEST_COMPLETE_SID", 
                                  "THIRSTY_QUEST_REMINDER_SID", 
                                  truefn,
                                  thirsty_start_fn, 
                                  thirsty_completion_condition_fn, 
                                  thirsty_completion_fn)

  local rowboat_quest = Quest:new("rowboat_" .. cr_id, 
                                  "ROWBOAT_QUEST_TITLE_SID", 
                                  sdesc_sid,
                                  "ROWBOAT_QUEST_DESCRIPTION_SID", 
                                  "ROWBOAT_QUEST_COMPLETE_SID", 
                                  "ROWBOAT_QUEST_REMINDER_SID", 
                                  truefn,
                                  rowboat_start_fn, 
                                  rowboat_completion_condition_fn, 
                                  rowboat_completion_fn)

  local fishfeast_quest = Quest:new("fishfeast_" .. cr_id, 
                                    "FISHFEAST_QUEST_TITLE_SID", 
                                    sdesc_sid,
                                    "FISHFEAST_QUEST_DESCRIPTION_SID", 
                                    "FISHFEAST_QUEST_COMPLETE_SID", 
                                    "FISHFEAST_QUEST_REMINDER_SID", 
                                    truefn,
                                    fishfeast_start_fn, 
                                    fishfeast_completion_condition_fn, 
                                    fishfeast_completion_fn)

  -- Get the village details
  local c, name, location = Quest:get_escort_details(cr_id, "villagevisit")
  local v_y = -1
  local v_x = -1

  if #c > 0 and #name > 0 and #location > 0 then
    local coords = tokenize(c, "-")
    v_y = coords[1]
    v_x = coords[2]
  else
    v_y, v_x, name, location = get_random_village(get_current_map_id())
    Quest:set_escort_details(cr_id, v_y, v_x, name, location, "villagevisit")
  end
  
  local villagevisit_quest = Quest:new("villagevisit_" .. cr_id, 
                                       "VILLAGEVISIT_QUEST_TITLE_SID", 
                                       sdesc_sid,
                                       {"VILLAGEVISIT_QUEST_DESCRIPTION_SID", fn.array_to_csv({name, location})}, 
                                       "VILLAGEVISIT_QUEST_COMPLETE_SID", 
                                       {"VILLAGEVISIT_QUEST_REMINDER_SID", fn.array_to_csv({name, location})}, 
                                       truefn,
                                       villagevisit_start_fn, 
                                       villagevisit_completion_condition_fn, 
                                       villagevisit_completion_fn)

  -- Get the job location details
  local c, name, location = Quest:get_escort_details(cr_id, "newjob")
  local v_y = -1
  local v_x = -1

  if #c > 0 and #name > 0 and #location > 0 then
    local coords = tokenize(c, "-")
    v_y = coords[1]
    v_x = coords[2]
  else
    v_y, v_x, name, location = get_random_preset_village(get_current_map_id())
    Quest:set_escort_details(cr_id, v_y, v_x, name, location, "newjob")
  end

  local newjob_quest = Quest:new("newjob_" .. cr_id, 
                                 "NEWJOB_QUEST_TITLE_SID", 
                                 sdesc_sid,
                                 {"NEWJOB_QUEST_DESCRIPTION_SID", fn.array_to_csv({name, location})}, 
                                 "NEWJOB_QUEST_COMPLETE_SID", 
                                 {"NEWJOB_QUEST_REMINDER_SID", fn.array_to_csv({name, location})}, 
                                 truefn,
                                 newjob_start_fn, 
                                 newjob_completion_condition_fn, 
                                 newjob_completion_fn)
  
  local fadventure_quest = Quest:new("adventure_forest_" .. cr_id, 
                                     "ADVENTURE_FOREST_QUEST_TITLE_SID", 
                                     sdesc_sid,
                                     {"ADVENTURE_FOREST_QUEST_DESCRIPTION_SID", fn.array_to_csv({name, location})}, 
                                     "ADVENTURE_FOREST_QUEST_COMPLETE_SID", 
                                     {"ADVENTURE_FOREST_QUEST_REMINDER_SID", fn.array_to_csv({name, location})}, 
                                     truefn,
                                     adventure_forest_start_fn, 
                                     adventure_forest_completion_condition_fn, 
                                     adventure_forest_completion_fn)

  local adventure_quest = Quest:new("adventure_" .. cr_id, 
                                    "ADVENTURE_QUEST_TITLE_SID", 
                                    sdesc_sid,
                                    {"ADVENTURE_QUEST_DESCRIPTION_SID", fn.array_to_csv({name, location})}, 
                                    "ADVENTURE_QUEST_COMPLETE_SID", 
                                    {"ADVENTURE_QUEST_REMINDER_SID", fn.array_to_csv({name, location})}, 
                                    truefn,
                                    adventure_start_fn, 
                                    adventure_completion_condition_fn, 
                                    adventure_completion_fn)

  local carcassia_lam_quest = Quest:new("carcassia_lam_" .. cr_id,
                                        "CARCASSIA_LAM_QUEST_TITLE_SID",
					sdesc_sid,
					{"CARCASSIA_LAM_QUEST_DESCRIPTION_SID", fn.array_to_csv({name, location})},
					"CARCASSIA_LAM_QUEST_COMPLETE_SID",
					{"CARCASSIA_LAM_QUEST_REMINDER_SID", fn.array_to_csv({name, location})},
                                        carcassia_lam_precondition_fn,
                                        carcassia_lam_start_fn,
                                        carcassia_lam_completion_condition_fn,
                                        carcassia_lam_completion_fn)

  local quests = {{thirsty_quest, 2},
                  {rowboat_quest, 2},
		  {fishfeast_quest, 2},
                  {villagevisit_quest, 2},
		  {newjob_quest, 2},
		  {fadventure_quest, 2},
		  {adventure_quest, 2},
                  {carcassia_lam_quest, 2}}
		  
  return quests
end

function CommonQuests:do_quests(creature_id)
  local sdesc_sid = get_creature_short_description_sid(creature_id)
  local quests = get_quests(creature_id, sdesc_sid)
  
  for i,v in ipairs(quests) do
    local do_quest = Quest:check_probabilistic_quest(creature_id, v[1].quest_id, v[2])
    
    if do_quest and v[1]:execute() then
      return true
    end
  end

  return false
end


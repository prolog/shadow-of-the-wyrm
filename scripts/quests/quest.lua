-- Quest module.  Used for creating new quests for the player.
require('constants')

Quest = {}
Quest.__index = Quest

function truefn()
  return true
end

function falsefn()
  return false
end

function emptyfn()
end

function Quest:get_escort_details(cr_id)
  local coords = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION")
  local name = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_NAME")
  local location = get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_LOCATION")

  return coords, name, location
end

function Quest:set_escort_details(cr_id, v_y, v_x, name, location)
  -- Set the coordinates on the speaker
  set_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION", fn.make_coordinate_key(v_y, v_x))
  set_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_NAME", name)
  set_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_LOCATION", location)
end

function Quest:remove_escort_details(cr_id)
  remove_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION")
  remove_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_NAME")
  remove_creature_additional_property(cr_id, "CREATURE_PROPERTIES_ESCORT_DESTINATION_LOCATION")
end

-- Must be overridden on the table
function Quest:quest_completion_condition_fn()
  return false
end

-- Does nothing.  Must be overridden on the table.
function Quest:quest_completion_fn()
end

-- Create a new quest
function Quest:new(quest_id, quest_title_sid_or_table, questmaster_name_sid, quest_description_sid_or_table, quest_completion_text_sid, quest_reminder_text_sid_or_table, quest_precond_fn, quest_start_fn, quest_completion_condition_fn, quest_completion_fn)
  local obj = {}

  -- Look up the current map name instead of forcing every quest to
  -- have to specify it.
  --
  -- The assumption here is that quests are always given to the player
  -- on the map they're currently on.  If this ever needs to change,
  -- make the map name SID a parameter to this function.
  local map_name_sid = map_get_name_sid()

  setmetatable(obj, self)

  obj.quest_id = quest_id

  if type(quest_title_sid_or_table) == "table" then
    local t_size = #quest_title_sid_or_table

    if t_size == 2 then
      obj.quest_title_sid = quest_title_sid_or_table[1]
      obj.quest_title_parameter_sids = quest_title_sid_or_table[2]
    end
  else
    obj.quest_title_sid = quest_title_sid_or_table
    obj.quest_title_parameter_sids = ""
  end

  obj.questmaster_id = args[SPEAKING_CREATURE_ID]
  obj.questmaster_name_sid = questmaster_name_sid
  obj.map_name_sid = map_name_sid

  if type(quest_description_sid_or_table) == "table" then
    local t_size = #quest_description_sid_or_table

    if t_size == 2 then
      obj.quest_description_sid = quest_description_sid_or_table[1]
      obj.quest_description_parameter_sids = quest_description_sid_or_table[2]
    end
  else
    obj.quest_description_sid = quest_description_sid_or_table
    obj.quest_description_parameter_sids = ""
  end

  obj.quest_completion_text_sid = quest_completion_text_sid

  if type(quest_reminder_text_sid_or_table) == "table" then
    local t_size = #quest_reminder_text_sid_or_table

    if t_size == 2 then
      obj.quest_reminder_text_sid = quest_reminder_text_sid_or_table[1]
      obj.quest_reminder_text_parameter_sids = quest_reminder_text_sid_or_table[2]
    end
  else
    obj.quest_reminder_text_sid = quest_reminder_text_sid_or_table
    obj.quest_reminder_text_parameter_sids = ""
  end

  obj.quest_precond_fn = truefn
  obj.quest_start_fn = emptyfn
  obj.quest_completion_condition_fn = falsefn
  obj.quest_completion_fn = falsefn

  if (quest_precond_fn ~= nil) then
    obj.quest_precond_fn = quest_precond_fn
  else
    log(CLOG_ERROR, "nil precondition fn for quest ID " .. quest_id)
  end

  if (quest_start_fn ~= nil) then
    obj.quest_start_fn = quest_start_fn
  else
    log(CLOG_ERROR, "nil start fn for quest ID " .. quest_id)
  end

  if (quest_completion_condition_fn ~= nil) then
    obj.quest_completion_condition_fn = quest_completion_condition_fn
  else
    log(CLOG_ERROR, "nil completion condition fn for quest ID " .. quest_id)
  end

  if (quest_completion_fn ~= nil) then
    obj.quest_completion_fn = quest_completion_fn
  else
    log(CLOG_ERROR, "nil completion fn for quest ID " .. quest_id)
  end

  return obj
end

function Quest:execute()
  -- Quest is complete
  if is_quest_completed(self.quest_id) then
    return false
 
  -- Preconditions met?
  elseif self.quest_precond_fn() == false then
    return false
  
  -- Quest is not complete, but condition is met.
  elseif self.quest_completion_condition_fn() == true then
    local should_mark_complete = self.quest_completion_fn()

    -- May not be on the quest.  Silently add the quest if not.
    if is_on_quest(self.quest_id) == false then
      add_new_quest(self.quest_id, self)
    end

    -- Guaranteed to have a quest at this point.  Mark it as complete
    -- if the completion function has indicated this.
    if should_mark_complete == true then
      mark_quest_completed(self.quest_id)

      -- Adventurers who complete lots of quest are kind of by definition
      -- charismatic.
      for i = 1, RNG_range(3, 6) do
        mark_cha(PLAYER_ID)
      end 
    end


  -- Quest is in progress, condition is not met.
  elseif is_on_quest(self.quest_id) then
    if quest_reminder_text_parameter_sids ~= "" then
      local params = {}
      for p in string.gmatch(self.quest_reminder_text_parameter_sids, "([^,]+)") do
        table.insert(params, get_sid(p))
      end

      add_message(self.quest_reminder_text_sid, params)
    else
      add_message(self.quest_reminder_text_sid)
    end

  -- Quest is not in progress, condition is not met.
  else
    local quest_started = self.quest_start_fn()

    -- Some quests may bail out in the start function by returning
    -- false.  In this case, we want to make sure we don't add the
    -- quest to the player's list.
    if quest_started ~= false then
      add_new_quest(self.quest_id, self)
    end
    
    -- Starting a quest gets the player a few marks in Charisma.
    for i = 1, RNG_range(2,4) do
      mark_cha(PLAYER_ID)
    end
  end

  return true
end

-- Try to add some nice additional quest rewards. Most of the time this
-- will do nothing.
function Quest:try_additional_quest_reward()
  local item_id = nil
  
  if RNG_percent_chance(10) then
    if RNG_percent_chance(80) then
      if RNG_percent_chance(50) then
        item_id = GOLDEN_APPLE_ID
      else
        item_id = SILVER_APPLE_ID
      end
    else
      if RNG_percent_chance(50) then
        item_id = ENCHANTING_SCROLL_ID
      else
        item_id = GAIN_ATTRIBUTES_POTION_ID
      end
    end
  end

  if item_id ~= nil then
    add_object_to_player_tile(item_id)
  end
end

-- Quest:try_probabilistic_quest checks to see if a probabilistic quest
-- has been run for the given creature. If it hasn't, it checks the given
-- probability to see if it should be fun. The outcome of this (true or
-- false) is saved as a property on the creature.
function Quest:check_probabilistic_quest(cr_id, quest_id, quest_p)
  local cr_q_guid = CREATURE_QUEST_GUID .. "_" .. quest_id
  local cr_qid = get_creature_additional_property(cr_id, cr_q_guid)
  local run_quest = false
  local chance = 15

  if quest_p ~= nil then
    chance = quest_p
  end

  if cr_qid == "" then
    if RNG_percent_chance(chance) then
      set_creature_additional_property(cr_id, cr_q_guid, "1")
      run_quest = true
    else
      set_creature_additional_property(cr_id, cr_q_guid, "0")
    end
  else
    run_quest = (cr_qid == "1")
  end

  return run_quest
end

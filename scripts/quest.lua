-- Quest module.  Used for creating new quests for the player.

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

-- Must be overridden on the table
function Quest:quest_completion_condition_fn()
  return false
end

-- Does nothing.  Must be overridden on the table.
function Quest:quest_completion_fn()
end

-- Create a new quest
function Quest:new(quest_id, quest_title_sid, questmaster_name_sid, quest_description_sid, quest_completion_text_sid, quest_reminder_text_sid, quest_precond_fn, quest_start_fn, quest_completion_condition_fn, quest_completion_fn)
  local obj = {}

  setmetatable(obj, self)

  obj.quest_id = quest_id
  obj.quest_title_sid = quest_title_sid
  obj.questmaster_name_sid = questmaster_name_sid
  obj.quest_description_sid = quest_description_sid
  obj.quest_completion_text_sid = quest_completion_text_sid
  obj.quest_reminder_text_sid = quest_reminder_text_sid

  obj.quest_precond_fn = truefn
  obj.quest_start_fn = emptyfn
  obj.quest_completion_condition_fn = falsefn
  obj.quest_completion_fn = falsefn

  if (quest_precond_fn ~= nil) then
    obj.quest_precond_fn = quest_precond_fn
  end

  if (quest_start_fn ~= nil) then
    obj.quest_start_fn = quest_start_fn
  end

  if (quest_completion_condition_fn ~= nil) then
    obj.quest_completion_condition_fn = quest_completion_condition_fn
  end

  if (quest_completion_fn ~= nil) then
    obj.quest_completion_fn = quest_completion_fn
  end

  return obj
end

function Quest:execute()
  -- Quest is complete
  if is_quest_completed(self.quest_id) then
    return false
  
  -- Quest is not complete, but condition is met.
  elseif self.quest_completion_condition_fn() == true then
    self.quest_completion_fn()

    -- May not be on the quest.  Silently add the quest if not.
    if is_on_quest(self.quest_id) == false then
      add_new_quest(self.quest_id, self)
      -- Guaranteed to have a quest at this point.  Mark it as complete.
      mark_quest_completed(self.quest_id)
    end

  -- Quest is in progress, condition is not met.
  elseif is_on_quest(self.quest_id) then
    add_message(quest_reminder_text_sid)

  -- Quest is not in progress, condition is not met.
  else
    add_new_quest(self.quest_id, self)
    self.quest_start_fn()
  end

  return true
end

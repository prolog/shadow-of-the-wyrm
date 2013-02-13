-- Quest module.  Used for creating new quests for the player.

local Quest = {}

-- Create a new quest
function Quest.create(quest_id, quest_title_sid, questmaster_name_sid, quest_description_sid)
  local obj = {}
  obj.quest_id = quest_id
  obj.quest_title_sid = quest_title_sid
  obj.questmaster_name_sid = questmaster_name_sid
  obj.quest_description_sid = quest_description_sid

  return obj
end

return Quest

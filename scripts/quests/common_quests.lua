require('quest')

-- CommonQuest module.  Used to quests that can be used by a variety of
-- NPCs.
CommonQuests = {}
CommonQuests.__index = CommonQuests

local function get_quests()
  local quests = {}
  return quests
end

function CommonQuests:do_quests(creature_id)
  local quests = get_quests()
  for i,v in ipairs(quests) do
    local qid = cr_id .. "_" .. v[1]
    local do_quest = Quest:check_probabilistic_quest(qid, v[2])
    if v[3]:execute() then
      return true
    end
  end

  return false
end


require('kill')

-- Oracles get +5% experience if the killed creature had any statuses
-- in force.
local function oracle_kill_fn(att_cr_id, kill_cr_id)
  local statuses = {get_creature_statuses(kill_cr_id)}

  if table.getn(statuses) > 0 then
    -- Take 5% of the xp value (or 1 XP, if the value is sufficiently
    -- low), and add it to the attacking creature.
    local xp_val = get_experience_value(kill_cr_id) * 0.05
    xp_val = math.max(xp_val, 1)

    gain_experience(att_cr_id, xp_val)
  end
end

-- Set up the oracle kill function
local oracle_class_kill_fn = oracle_kill_fn

kill.set_class_kill_fn("oracle", oracle_class_kill_fn)


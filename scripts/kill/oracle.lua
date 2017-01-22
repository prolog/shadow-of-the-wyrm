require('kill')

-- Oracles get +5% experience if the killed creature had a status
-- ailment.
local function oracle_kill_fn(att_cr_id, kill_cr_id)
  -- ...
end

-- Set up the oracle kill function
local oracle_class_kill_fn = oracle_kill_fn

kill.set_class_kill_fn(oracle_class_kill_fn)


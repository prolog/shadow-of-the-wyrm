module(..., package.seeall)

-- Class-based functions that are fired when a creature of that class
-- kills another creature.
class_kill_fns = {}

function set_class_kill_fn(class_id, fn)
  class_kill_fns[class_id] = fn
end

function kill(att_cr_id, att_class_id, kill_cr_id)
  local fn = class_kill_fns[att_class_id]

  if fn ~= nil then
    fn(att_cr_id, kill_cr_id)
  end
end


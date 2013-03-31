module(..., package.seeall)

class_fns = {}

-- Set a particular level function - this is called by the class-specific
-- .lua scripts.
function set_class_level_fn(class_id, fn)
  class_fns[class_id] = fn
end

-- level is a function that is called each level, whenever a creature
-- levels up and has a class-specific level function defined.
function level(class_id, creature_id, new_level)
  local fn = class_fns[class_id]
  fn(creature_id, new_level)
end

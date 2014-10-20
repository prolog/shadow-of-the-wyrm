-- All the deity anger functions.  Contains a common function with key
-- "__default__" (so, this can't be used as a deity ID) which will be
-- called if the lookup for the given deity ID fails.
deity_anger_fns = {}

-- Blue-bolt the worthless!
local function deity_anger_blast(creature_id, deity_id)
  set_creature_current_hp(creature_id, 1)
  set_creature_current_ap(creature_id, 1)

  add_message("DEITY_ACTION_DISPLEASED_BLUE_LIGHTNING")
end

-- Destroy the items of the impious!
local function deity_anger_destroy_items(creature_id, deity_id)
  destroy_creature_equipment(creature_id)
  destroy_creature_inventory(creature_id)

  add_message("DEITY_ACTION_DISPLEASED_DESTROY_ITEMS")
end

-- Summon a bunch of nasties!
local function deity_anger_summon_creatures(creature_id, deity_id)
  local monsters = get_deity_summons(deity_id)
  summon_monsters_around_creature(monsters, creature_id, 3)

  add_message("DEITY_ACTION_DISPLEASED_SUMMON")
end

-- Handle deity anger, generally as a result of praying when the
-- deity dislikes you.
function deity_anger_default(creature_id, deity_id)
  -- Equal chance of blue-bolting, equipment destruction, or nasties.
  local val = RNG_range(1, 3)
  local deity_actions = {deity_anger_blast, deity_anger_destroy_items, deity_anger_summon_creatures}
  
  local action_fn = deity_actions[val]
  action_fn(creature_id, deity_id)
end

-- Attempts to look up the anger function, given the deity ID, and then
-- call it.  If there was no anger function found for the given deity ID,
-- then try the default.
function anger(creature_id, deity_id)
  local deity_fn = deity_anger_fns[deity_id]

  if deity_fn == nil then
    deity_fn = deity_anger_default
  end

  -- Call the anger function.
  deity_fn(creature_id, deity_id)
end


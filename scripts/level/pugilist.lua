require('level')

local function pugilist_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_str(creature_id, is_player(creature_id))
  end

  -- Add a race slay to the creature's unarmed damage
  if level % 20 == 0 then
    -- Don't include user-playable races.  Revisit this later if there are
    -- ever a lot of any particular race.  Excluding these because
    -- otherwise the slays will not be particularly useful.
    local exist_unarm_slay = {get_unarmed_slays(creature_id)}
    local race_ids = {get_race_ids(false)}

    for i,v in ipairs(exist_unarm_slay) do
      local rem_idx = 0

      for j,v2 in ipairs(race_ids) do
        if v == v2 then
          rem_idx = j
          break
        end
      end

      if rem_idx > 0 then
        table.remove(race_ids, rem_idx)
      end
    end

    -- Pick a race_id not present in the existing unarmed slays.
    local sr_size = table.getn(race_ids)

    if sr_size > 0 then
      local new_race_slay = race_ids[RNG_range(1, sr_size)]
            
      -- Add the new slay to the creature's unarmed damage.
      add_unarmed_slay(creature_id, new_race_slay)

      -- Add a message about slaying this race.
      add_message("DAMAGE_NEW_SLAY", {get_race_name(new_race_slay)})
    end
  end
end

local function pugilist_level_fn(creature_id, level)
  set_creature_base_damage(creature_id, 1, 2 * level)
end

-- Set up the pugilist class functions.
local pugilist_fn = pugilist_level_fn
local pugilist_class_stat_fn = pugilist_stat_gain_fn

level.set_class_stat_gain_level_fn("pugilist", pugilist_class_stat_fn)
level.set_class_level_fn("pugilist", pugilist_fn)


require('level')
require('constants')

local function pugilist_stat_gain_fn(creature_id, level)
  if level % 5 == 0 then
    incr_str(creature_id, is_player(creature_id))
  end

  -- Add a race slay to the creature's unarmed damage
  if level % 20 == 0 then
    -- Don't include user-playable races.  Revisit this later if there are
    -- ever a lot of any particular race.  Excluding these because
    -- otherwise the slays will not be particularly useful.
    --
    -- Also, there are certain races (Elysian) where there are a trivial
    -- number of examples, and they only occur in a very optional
    -- branch of the game.  And they're friendly.  In general, getting
    -- "Slay Elysians!" would be pretty useless.
    --
    -- So, exclude them, too.
    local include_user_playable = false
    local include_non_slayable = false

    local exist_unarm_slay = {get_unarmed_slays(creature_id)}
    local race_ids = {get_race_ids(include_user_playable, include_non_slayable)}

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
      if is_player(creature_id) then
        add_message("DAMAGE_NEW_SLAY", {get_race_name(new_race_slay)})
      end
    end
  end
end

-- Pugilists do 1d(2 * level) up to level 25.
-- From level 26 on, they do 1d(50 + 3 * level)
local function pugilist_level_fn(creature_id, level)
  local damage_dice = 2 * level

  if level > 25 then
    damage_dice = 50 + ((level - 25) * 3)
  end

  set_creature_base_damage(creature_id, 1, damage_dice)
end

-- Set up the pugilist class functions.
local pugilist_fn = pugilist_level_fn
local pugilist_class_stat_fn = pugilist_stat_gain_fn

level.set_class_stat_gain_level_fn("pugilist", pugilist_class_stat_fn)
level.set_class_level_fn("pugilist", pugilist_fn)


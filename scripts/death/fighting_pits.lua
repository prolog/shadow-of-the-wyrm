require('death')
require('constants')

local pg_cur_q_complete = "pitmistress_ghara_current_quest_complete"

-- Always teleport the player out, regardless of whether or not they
-- killed the creature, as creatures can kill themselves via stunning
-- attacks, etc.
local function exit_pits(creature_id, attacking_creature_id, map_id)
  play_music_event(CMUSIC_EVENT_ARENA_VICTORY, false)
  add_message_with_pause("EXIT_FIGHTING_PITS_SID", false)
  set_map_music(get_current_map_id(), get_music_location_for_event(CMUSIC_EVENT_CARCASSIA), true)
  
teleported = teleport(PLAYER_ID, 9, 47)
  
  -- If we couldn't teleport to the usual place, teleport to the fortress
  -- entrance.
  if teleported == false then
    teleport(PLAYER_ID, 0, 19)
  end

  set_creature_additional_property(PLAYER_ID, pg_cur_q_complete, "1")

  clear_messages()
end

local exit_pits_fn = exit_pits
death.set_death_fn(args[DEAD_CREATURE_ID], exit_pits_fn)


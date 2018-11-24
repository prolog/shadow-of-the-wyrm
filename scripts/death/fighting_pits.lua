require('death')
require('constants')

local pg_cur_q_complete = "pitmistress_ghara_current_quest_complete"

local function exit_pits(creature_id, attacking_creature_id, map_id)
  add_message_with_pause("EXIT_FIGHTING_PITS_SID", false)
  teleport(attacking_creature_id, 9, 47)
  set_creature_additional_property(PLAYER_ID, pg_cur_q_complete, "1")

  clear_messages()
end

local exit_pits_fn = exit_pits
death.set_death_fn(args[DEAD_CREATURE_ID], exit_pits_fn)


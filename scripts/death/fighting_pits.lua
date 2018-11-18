require('death')

local function exit_pits(creature_id, attacking_creature_id, map_id)
  add_message_with_pause("EXIT_FIGHTING_PITS_SID")
  teleport(attacking_creature_id, 5, 47)

  clear_messages()
end

local exit_pits_fn = exit_pits
death.set_death_fn(args[DEAD_CREATURE_ID], exit_pits_fn)


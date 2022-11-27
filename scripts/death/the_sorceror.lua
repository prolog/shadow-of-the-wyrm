require('death')
require('constants')
require('fn')

local function teleport_back(creature_id, attacking_creature_id, map_id)
  fn.drain_hp_and_ap(attacking_creature_id)
  set_creature_additional_property(attacking_creature_id, "TELARI_THE_SORCEROR_DEAD", tostring(true))

  add_message_with_pause("THE_SORCEROR_DEATH_SID")
  add_message_with_pause("THE_SORCEROR_DEATH2_SID")
  add_message_with_pause("THE_SORCEROR_DEATH3_SID")

  load_map(PLAYER_ID, WORLD_MAP_ID)
end

local teleport_fn = teleport_back
death.set_death_fn("the_sorceror", teleport_fn)


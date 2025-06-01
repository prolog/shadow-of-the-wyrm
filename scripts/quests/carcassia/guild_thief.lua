require('constants')

-- The friendly thief in the SW "house" in Carcassia A1.
cr_id = args[SPEAKING_CREATURE_ID]
daggers_prop = "daggers_given"
message_sid = "CARCASSIA_THIEF_HOUSE2_SID"
daggers_given = get_creature_additional_property(cr_id, daggers_prop)
is_thief = creature_is_class(PLAYER_ID, CLASS_ID_THIEF)

if is_thief and daggers_given == "" then
  clear_and_add_message("CARCASSIA_THIEF_GIFT_SID")
  add_object_to_player_tile("dagger", RNG_range(6, 18))

  set_creature_additional_property(cr_id, daggers_prop, "1")
else
  if is_thief then
    clear_and_add_message("CARCASSIA_THIEF_WELCOME_SID")
  else
    clear_and_add_message("CARCASSIA_THIEF_HOUSE2_SID")
  end
end


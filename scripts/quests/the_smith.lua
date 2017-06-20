require('constants')
require('fn')

local divine_race_id = "_divine"
local smith_prop = "the_smith_gift_generated"
local given_gift = get_creature_additional_property(PLAYER_ID, smith_prop)

if string.len(given_gift) == 0 then
  local num_dice, num_sides, modifier = get_creature_base_damage(PLAYER_ID)
  local level = get_creature_level(PLAYER_ID)
  local class_id = get_class_id(PLAYER_ID)

  if class_id == "pugilist" then
    add_message_with_pause("THE_SMITH_SPEECH_UNARMED_SID")

    -- If the player is skilled at unarmed combat, then:
    --
    -- 1. Give a large damage increase
    modifier = modifier + 400
    --
    -- 2. If the player doesn't have slay divine, grant it.  If the player
    --    has that slay, grant an additional stack of damage.
    local slays = {get_unarmed_slays(PLAYER_ID)}

    if fn.contains(slays, divine_race_id) then
      modifier = modifier + 250
      clear_and_add_message("THE_SMITH_SPEECH_UNARMED_SLAY_SID")
    else
      add_unarmed_slay(PLAYER_ID, divine_race_id)
      clear_and_add_message("THE_SMITH_SPEECH_UNARMED_NO_SLAY_SID")
    end

    set_creature_base_damage(PLAYER_ID, num_dice, num_sides, modifier)
  else
    -- If the creature doesn't meet the unarmed combat requirements, then
    -- grant the God-Blade.
    add_message_with_pause("THE_SMITH_SPEECH_GODBLADE_SID")
    add_message_with_pause("THE_SMITH_SPEECH_GODBLADE2_SID")
    add_message_with_pause("THE_SMITH_SPEECH_GODBLADE3_SID")
    add_message_with_pause("THE_SMITH_SPEECH_GODBLADE4_SID")
    clear_and_add_message("THE_SMITH_SPEECH_GODBLADE5_SID")

    add_object_to_player_tile("godblade")
  end

  -- Set the gift property so that this'll be skipped next time.
  set_creature_additional_property(PLAYER_ID, smith_prop, "1")
else
  clear_and_add_message("THE_SMITH_SPEECH_TEXT_SID")
end


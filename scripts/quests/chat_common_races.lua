require('constants')

local offered_peace_property = "offered_peace"

-- Offer peace, for a price
local function offer_peace(creature_id)
  base_amount = get_creature_level(creature_id) * 10
  requested_amount = RNG_range(base_amount, base_amount * 1.25)

  if count_currency(PLAYER_ID) < requested_amount then
    add_message_with_pause("HOSTILE_CREATURE_NSF_SID", {get_creature_description(PLAYER_ID, creature_id)})
  else
    pay_for_peace = add_confirmation_message("HOSTILE_CREATURE_PEACE_OFFER_SID", {tostring(requested_amount), get_creature_description(PLAYER_ID, creature_id)})

    if pay_for_peace == true then
      add_message_with_pause("PAY_OFF_HOSTILE_CREATURE_SID")
      remove_object_from_player(CURRENCY_ID, requested_amount)
      transfer_item(PLAYER_ID, creature_id, CURRENCY_ID, requested_amount)
      set_hostility(creature_id, PLAYER_ID, get_current_map_id(), false)
      set_creature_additional_property(creature_id, offered_peace_property, tostring(true))
    end
  end
end

local function should_offer_peace(creature_id)
  -- For followers of the black horror, peace is never an option...
  local deity_isnt_sceadugenga = get_deity_id(creature_id) ~= DEITY_ID_SCEADUGENGA
  local hasnt_offered_peace_yet = get_creature_additional_property(creature_id, offered_peace_property) ~= tostring(true)

  return deity_isnt_sceadugenga and hasnt_offered_peace_yet
end

-- Humanoids, when hostile, will offer peace in exchange for a sum.
local function speak_humanoid(creature_id)
  if is_creature_hostile(creature_id, PLAYER_ID) and should_offer_peace(creature_id) then
    return offer_peace(creature_id)
  end

  return false
end

-- Call any race-specific speech functions before the creature's main chat
-- script is run
function racial_speech(creature_id, race_id)
  spoke = false

  if is_race_or_descendent(race_id, HUMANOID_RACE_ID) then
    spoke = speak_humanoid(creature_id)
  end

  return spoke
end


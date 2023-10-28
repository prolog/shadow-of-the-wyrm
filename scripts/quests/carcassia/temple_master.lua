require('constants')

local MIN_AMOUNT_BLESS_EQ = 1000
local MIN_AMOUNT_BLESS_INV = 2000
local PIETY_DIVISOR = 4

-- Add piety based on the player's donation, and check to see if any of the
-- minimums have been met to uncurse equipment, inventory, or to bless
-- equipment.
local function process_donation(amount)
  if amount >= MIN_AMOUNT_BLESS_EQ then
    bless_equipment(PLAYER_ID)
  end

  if amount >= MIN_AMOUNT_BLESS_INV then
    bless_inventory(PLAYER_ID)
  end

  add_piety(PLAYER_ID, amount / PIETY_DIVISOR)
end

add_message_with_pause("TEMPLE_MASTER_INTRODUCTION_SID")
add_message_with_pause("TEMPLE_MASTER_INTRODUCTION2_SID")
add_message_with_pause("TEMPLE_MASTER_INTRODUCTION3_SID")

local pl_ivory = get_item_count(PLAYER_ID, CURRENCY_ID)

if pl_ivory == 0 then
  clear_and_add_message("TEMPLE_MASTER_NO_IVORY_SID")
else
  local amount = tonumber(add_prompt_message("TEMPLE_MASTER_AMOUNT_SID"))

  if type(amount) ~= 'number' or amount <= 0 or amount > pl_ivory then
    clear_and_add_message("TEMPLE_MASTER_SPEECH_TEXT_SID")
  else
    remove_object_from_player(CURRENCY_ID, amount)
    process_donation(amount)

    clear_and_add_message("TEMPLE_MASTER_DONATION_MADE_SID")
  end
end

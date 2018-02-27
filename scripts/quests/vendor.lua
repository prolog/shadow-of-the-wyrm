require('constants')

local currency_amount = get_item_count(PLAYER_ID, CURRENCY_ID)

if (currency_amount > 1) then
  local sc_id = args[SPEAKING_CREATURE_ID]
  local foods = {get_creature_additional_property_csv(sc_id, "VENDOR_FOOD")}
  
  local food_size = table.getn(foods)
      
  if food_size > 0 then
    if add_confirmation_message("VENDOR_ACTION_OFFER_FOOD") then
      local food_id = foods[RNG_range(1, food_size)]  
    
      -- Provide it to the player and take his or her money.
      clear_and_add_message("VENDOR_ACTION_PROVIDE_MEAL")
      add_object_to_player_tile(food_id)

      remove_object_from_player(CURRENCY_ID, 1)
    else
      clear_and_add_message("VENDOR_ACTION_SAY_GOODBYE")
    end
  end
else
  clear_and_add_message("VENDOR_NO_MONEY")
end


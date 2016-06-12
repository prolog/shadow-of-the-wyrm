local currency_amount = get_item_count("player", "_currency")

if (currency_amount > 3) then
  local sc_id = args["speaking_creature_id"]
  local foods = {get_creature_additional_property_csv(sc_id, "BARKEEPER_FOOD")}
  local drinks = {get_creature_additional_property_csv(sc_id, "BARKEEPER_DRINK")}
  
  local food_size = table.getn(foods)
  local drinks_size = table.getn(drinks)
      
  if food_size > 0 and drinks_size > 0 then
    if add_confirmation_message("BARKEEPER_ACTION_OFFER_MEAL") then
      -- Pick food and drink.
      local food_id = foods[RNG_range(1, food_size)]  
      local drink_id = drinks[RNG_range(1, drinks_size)]
    
      -- Provide it to the player and take his or her money.
      clear_and_add_message("BARKEEPER_ACTION_PROVIDE_MEAL")
      add_object_to_player_tile(food_id)
      add_object_to_player_tile(drink_id)

      remove_object_from_player("_currency", 3)
    else
      clear_and_add_message("BARKEEPER_ACTION_SAY_GOODBYE")
    end
  end
else
  clear_and_add_message("BARKEEPER_UNFRIENDLY")
end


require('constants')

local sp_member_costs = {}
sp_member_costs[true] = {300, "PERN_COST_MEMBER_SID", "PERN_MEMBER_TRAIN_QUERY_SID"}
sp_member_costs[false] = {500, "PERN_COST_NOMEMBER_SID", "PERN_NOMEMBER_TRAIN_QUERY_SID"}

if has_trainable_skill(PLAYER_ID) == false then
  clear_and_add_message("PERN_NO_TRAINABLE_SKILLS_SID")
else
  local cost_info = sp_member_costs[has_membership(PLAYER_ID, ORDER_EX_GLADIATORES_GUILD_ID)]
  local cost = cost_info[1]
  local player_ivory = count_currency(PLAYER_ID)

  if player_ivory < cost then
    clear_and_add_message(cost_info[2])
  else
    local quantity = tonumber(add_prompt_message(cost_info[3]))
    
    if quantity == nil then
      quantity = 0
    end

    local total = cost * quantity

    if quantity > 0 and player_ivory >= total then
      remove_object_from_player(CURRENCY_ID, total)
      train_skills(PLAYER_ID, quantity)
      clear_messages()
    else
      clear_and_add_message("PERN_TRAIN_DECLINE_SID")
    end
  end
end


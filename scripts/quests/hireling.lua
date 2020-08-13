require('constants')

local function request_hire(this_cr_id, name)
  local currency = count_currency(PLAYER_ID)
  local hire_fee_s = get_creature_additional_property(this_cr_id, "CREATURE_PROPERTIES_HIRE_FEE")
  local hire_fee = tonumber(hire_fee_s)
  local hire_msg = get_creature_additional_property(this_cr_id, "CREATURE_PROPERTIES_HIRELING_CHAT_SID")

  if currency >= hire_fee then
    if add_confirmation_message(hire_msg, {name, hire_fee_s}) then
      remove_object_from_player(CURRENCY_ID, hire_fee)
      set_creature_additional_property(this_cr_id, "CREATURE_PROPERTIES_LEADER_ID", PLAYER_ID)

      clear_and_add_message("HIRELING_ORDERS_SID", {name})
    else
      clear_and_add_message("HIRELING_DECLINE_SID", {name})
    end
  else
    clear_and_add_message("HIRELING_HIRE_NSF_SID", {name, hire_fee_s})
  end
end

local this_cr_id = args[SPEAKING_CREATURE_ID]
local leader_id = get_leader_id(this_cr_id)
local name = get_name(this_cr_id)

if leader_id == PLAYER_ID then
  add_message("HIRELING_ORDERS_SID", {name})
else
  request_hire(this_cr_id, name)
end


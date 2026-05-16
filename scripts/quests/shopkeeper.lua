require('constants')
require('fn')

local function complete_purchase(purchase_amount, unpaid_amount, shopkeeper_id)
  -- Show how much was saved via Bargaining
  local savings = unpaid_amount - purchase_amount

  if savings > 0 then
    clear_and_add_message("SHOPKEEPER_SAVINGS_AMOUNT_SID", {tostring(purchase_amount)})
  else
    clear_and_add_message("SHOPKEEPER_PAY_SID")
  end

  -- Set all unpaid items on the player to paid
  set_items_paid(PLAYER_ID)
  add_message("SHOPKEEPER_THANKS_SID")
  play_sound_effect(CSOUND_EFFECT_SHOP)

  -- Paying for unpaid items mollifies angry shopkeepers throughout
  -- the game. But it doesn't remove the stolen_from property...
  local shopk_orig = get_creature_original_id(shopkeeper_id)

  remove_threat_from_all(PLAYER_ID, shopk_orig)
  remove_threat_from_all(shopk_orig, PLAYER_ID)

  transfer_item(shopkeeper_id, PLAYER_ID, CURRENCY_ID, purchase_amount)
end

local function get_purchase_amount(shopkeep_id, unpaid_amount)
  local purchase_amount = unpaid_amount
  local bargain, amount_pct = bargain_discount(PLAYER_ID)
  local class_id = get_class_id(PLAYER_ID)

  if bargain == true then
    purchase_amount = math.floor(purchase_amount * (1 - (amount_pct / 100)))
  end

  -- Thieves pay an extra 10% everywhere.
  if class_id == CLASS_ID_THIEF then
    purchase_amount = math.floor(purchase_amount * 1.1)
  end

  if fn.tobool(get_decision_strategy_property(shopkeep_id, CCREATURE_PROPERTIES_ROBBED)) then
    purchase_amount = math.floor(purchase_amount * 2)
  end
  
  return purchase_amount
end

-- Is there an amount owing?
local num_unpaid_items = get_num_unpaid_items(PLAYER_ID)
local unpaid_amount = get_unpaid_amount(PLAYER_ID)
local shopkeep_id = args[SPEAKING_CREATURE_ID]

if num_unpaid_items > 0 then
  -- Does the player have enough ivory to cover it?
  local currency_amount = count_currency(PLAYER_ID)
  local purchase_amount = get_purchase_amount(shopkeep_id, unpaid_amount)

  if (currency_amount >= purchase_amount) then
    -- Confirm the purchase
    purchase_sid = "SHOPKEEPER_CONFIRM_PURCHASE_SID"

    if purchase_amount > unpaid_amount then
      purchase_sid = "SHOPKEEPER_CONFIRM_PURCHASE_DISLIKE_SID"
    end

    if add_confirmation_message(purchase_sid, {tostring(purchase_amount)}) then
      complete_purchase(purchase_amount, unpaid_amount, shopkeep_id)
    else
      clear_and_add_message("SHOPKEEPER_WARNING_SID")
    end
  else
    clear_and_add_message("SHOPKEEPER_INSUFFICIENT_FUNDS_SID", {tostring(purchase_amount)})
  end
else
  -- Nothing owed.  Add a standard greeting.
  local has_space = get_shop_has_available_space(shopkeep_id)

  if has_space == true then
    clear_and_add_message("SHOPKEEPER_REPOP_SOON_SID")
  else
    clear_and_add_message("SHOPKEEPER_SPEECH_TEXT_SID")
  end
end

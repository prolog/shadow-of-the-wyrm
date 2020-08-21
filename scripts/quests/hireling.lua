require('constants')

-- Ignore witchling spells - these will be automatically gained by witchling
-- NPCs as part of the class scripts.
local function hireling_gain_spells(creature_id)
  local t_skills = get_trained_magic_skills(creature_id)

  local spell = {[CSKILL_MAGIC_CANTRIPS] = {"c_02_flame_dart", "c_05_spirit_bolt", "c_09_force_bolt", "c_11_blast"},
                 [CSKILL_MAGIC_ARCANE] = {"a_01_wreath_of_fire", "a_02_dragon_breath", "a_03_lightning_bolt", "a_04_shockwave", "a_06_cross_of_flame", "a_07_fireball", "a_09_frost_bolt", "a_15_vorpal_bolt"},
                 [CSKILL_MAGIC_DIVINE] = {"d_02_smite", "d_10_radiant_beam"},
                 [CSKILL_MAGIC_MYSTIC] = {"m_02_poison", "m_03_blind", "m_05_spellbind", "m_08_stone"}}

  for i,v in ipairs(t_skills) do
    local spell_list = spell[v]
    
    if spell_list ~= nil then
      local spell_id = spell_list[RNG_range(1, #spell_list)]
      local castings = RNG_range(3, 8)

      add_spell_castings(creature_id, spell_id, castings)
      log(CLOG_DEBUG, "Added " .. tostring(castings) .. " castings of " .. spell_id .. " for " .. creature_id)
    end
  end
end

local function request_hire(this_cr_id, name)
  local currency = count_currency(PLAYER_ID)
  local hire_fee_s = get_creature_additional_property(this_cr_id, "CREATURE_PROPERTIES_HIRE_FEE")
  local hire_fee = tonumber(hire_fee_s)
  local hire_msg = get_creature_additional_property(this_cr_id, "CREATURE_PROPERTIES_HIRELING_CHAT_SID")
  local map_id = get_current_map_id()

  if currency >= hire_fee then
    if add_confirmation_message(hire_msg, {name, hire_fee_s}) then
      remove_object_from_player(CURRENCY_ID, hire_fee)
      add_object_to_creature(map_id, this_cr_id, CURRENCY_ID, "", hire_fee)
      incr_str_to_unburdened(this_cr_id, false)

      set_creature_additional_property(this_cr_id, "CREATURE_PROPERTIES_LEADER_ID", PLAYER_ID)
      set_hirelings_hired(PLAYER_ID, get_hirelings_hired(PLAYER_ID) + 1)
      hireling_gain_spells(this_cr_id)
      
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


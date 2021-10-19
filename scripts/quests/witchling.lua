require('constants')

local pri_value = get_skill_value(PLAYER_ID, CSKILL_MAGIC_PRIMORDIAL)

if pri_value == 0 then
  local witchling_spells = {"p_01_shadow_flame", "p_03_cloak_of_shadows", "p_04_nether_bolt", "p_05_chaos_aura", "p_06_nightfire", "p_07_umbra"}

  add_spell_castings(PLAYER_ID, witchling_spells[RNG_range(1, #witchling_spells)], RNG_range(15, 30))
  set_skill_value(PLAYER_ID, CSKILL_MAGIC_PRIMORDIAL, RNG_range(3, 10))
  add_membership(PLAYER_ID, WITCHLINGS_MEMBERSHIP_ID, "WITCHLINGS_MEMBERSHIP_SID")

  add_message_with_pause("WITCHLING_TEA_TEXT_SID")
  add_message_with_pause("WITCHLING_TEA_TEXT2_SID")
  clear_and_add_message("WITCHLING_TEA_TEXT3_SID")

  local this_id = args[SPEAKING_CREATURE_ID]
  remove_chat_script(this_id)
else
  clear_and_add_message("WITCHLING_SPEECH_TEXT_SID")
end


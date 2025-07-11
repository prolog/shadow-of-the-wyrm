#pragma once
#include <string>
#include <memory>

class Creature;

class StatusAilmentTextKeys
{
  public:
    static std::string get_status_for_identifier(const std::string& status_id);

    // Hunger Keys:
    static const std::string STATUS_COUNTERACTED;
    static const std::string STATUS_HUNGER_STUFFED;
    static const std::string STATUS_MESSAGE_HUNGER_STUFFED;
    static const std::string STATUS_HUNGER_FULL;
    static const std::string STATUS_MESSAGE_HUNGER_FULL;
    static const std::string STATUS_HUNGER_NORMAL;
    static const std::string STATUS_MESSAGE_HUNGER_NORMAL;
    static const std::string STATUS_HUNGER_HUNGRY;
    static const std::string STATUS_MESSAGE_HUNGER_HUNGRY;
    static const std::string STATUS_HUNGER_STARVING;
    static const std::string STATUS_MESSAGE_HUNGER_STARVING;
    static const std::string STATUS_HUNGER_DYING;
    static const std::string STATUS_MESSAGE_HUNGER_DYING;

    // Burden keys:
    static const std::string STATUS_BURDEN_UNBURDENED;
    static const std::string STATUS_BURDEN_BURDENED;
    static const std::string STATUS_BURDEN_STRAINED;
    static const std::string STATUS_BURDEN_OVERBURDENED;
    
    // Other status ailments:
    static const std::string STATUS_POISON;
    static const std::string STATUS_POISON_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_POISONED;
    static const std::string STATUS_MESSAGE_PLAYER_POISON_CURED;
    static const std::string get_npc_poisoned_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_poison_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_MUTE;
    static const std::string STATUS_MUTE_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_MUTED;
    static const std::string STATUS_MESSAGE_PLAYER_MUTENESS_CURED;
    static const std::string get_npc_muted_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_muteness_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_PARALYSIS;
    static const std::string STATUS_PARALYSIS_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_PARALYZED;
    static const std::string STATUS_MESSAGE_PLAYER_PARALYSIS_CURED;
    static const std::string get_npc_paralyzed_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_paralysis_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_SLOWNESS;
    static const std::string STATUS_SLOWNESS_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_SLOWED;
    static const std::string STATUS_MESSAGE_PLAYER_SLOWNESS_CURED;
    static const std::string get_npc_slowed_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_slowness_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_HASTE;
    static const std::string STATUS_HASTE_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_HASTED;
    static const std::string STATUS_MESSAGE_PLAYER_HASTE_DONE;
    static const std::string get_npc_hasted_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_haste_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_MESSAGE_PLAYER_ILLITERATE;

    static const std::string STATUS_STONE;
    static const std::string STATUS_STONE_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_STONE;
    static const std::string STATUS_MESSAGE_PLAYER_STONE_CURED;
    static const std::string STATUS_MESSAGE_STONE_FINALIZE;
    static const std::string STATUS_MESSAGE_STONE_CRUMBLE;
    static const std::string get_npc_stone_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_stone_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_BLOODIED;
    static const std::string STATUS_BLOODIED_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_BLOODIED;
    static const std::string STATUS_MESSAGE_PLAYER_BLOODIED_CURED;
    static const std::string get_npc_bloodied_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_bloodied_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_STUNNED;
    static const std::string STATUS_STUNNED_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_STUNNED;
    static const std::string STATUS_MESSAGE_PLAYER_STUNNED_CURED;
    static const std::string get_npc_stunned_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_stunned_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_EXPOSED;
    static const std::string STATUS_EXPOSED_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_EXPOSED;
    static const std::string STATUS_MESSAGE_PLAYER_EXPOSED_CURED;
    static const std::string get_npc_exposed_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_exposed_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_DISFIGURED;
    static const std::string STATUS_DISFIGURED_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_DISFIGURED;
    static const std::string STATUS_MESSAGE_PLAYER_DISFIGURED_CURED;
    static const std::string get_npc_disfigured_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_disfigured_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_IMMOBILE;
    static const std::string STATUS_IMMOBILE_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_IMMOBILE;
    static const std::string STATUS_MESSAGE_PLAYER_IMMOBILE_CURED;
    static const std::string get_npc_immobile_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_immobile_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_BLINDED;
    static const std::string STATUS_BLINDED_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_BLINDED;
    static const std::string STATUS_MESSAGE_PLAYER_BLINDNESS_CURED;
    static const std::string STATUS_MESSAGE_BLIND_RANGED_COMBAT;
    static const std::string get_npc_blinded_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_blindness_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_INCORPOREAL;
    static const std::string STATUS_INCORPOREAL_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_INCORPOREAL;
    static const std::string STATUS_MESSAGE_PLAYER_INCORPOREAL_CURED;
    static const std::string get_npc_incorporeal_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_incorporeal_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_SATED;
    static const std::string STATUS_SATED_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_SATED;
    static const std::string STATUS_MESSAGE_PLAYER_SATED_CURED;
    static const std::string get_npc_sated_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_sated_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_WATER_BREATHING;
    static const std::string STATUS_WATER_BREATHING_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_WATER_BREATHING;
    static const std::string STATUS_MESSAGE_PLAYER_WATER_BREATHING_CURED;
    static const std::string get_npc_water_breathing_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_water_breathing_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_RAGE;
    static const std::string STATUS_RAGE_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_RAGE;
    static const std::string STATUS_MESSAGE_PLAYER_RAGE_CURED;
    static const std::string get_npc_rage_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_rage_message(std::shared_ptr<Creature> creature);

    // Hide is handled somewhat differently - it's handled on a turn by turn
    // basis, rather than a timer, and is invoked by using a skill.
    static const std::string STATUS_HIDE;
    static const std::string STATUS_HIDE_FULL;
    static const std::string get_npc_hide_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_hide_reveal_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_DRUNK;
    static const std::string STATUS_DRUNK_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_DRUNK;
    static const std::string STATUS_MESSAGE_PLAYER_SOBER;
    static const std::string get_npc_drunk_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_sober_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_FLYING;
    static const std::string STATUS_FLYING_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_FLYING;
    static const std::string STATUS_MESSAGE_PLAYER_FLYING_CURED;
    static const std::string get_npc_flying_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_flying_message(std::shared_ptr<Creature> creature);

    static const std::string STATUS_TIMEWALK;
    static const std::string STATUS_TIMEWALK_FULL;
    static const std::string STATUS_MESSAGE_PLAYER_TIMEWALK;
    static const std::string STATUS_MESSAGE_PLAYER_TIMEWALK_CURED;
    static const std::string get_npc_timewalk_message(std::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_timewalk_message(std::shared_ptr<Creature> creature);

  protected:
    StatusAilmentTextKeys();
    ~StatusAilmentTextKeys();

    static void initialize();

    static const std::string get_general_npc_message(const std::string& npc_description_sid, const std::string& message_sid);

    static const std::string STATUS_MESSAGE_NPC_POISONED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_POISON;

    static const std::string STATUS_MESSAGE_NPC_MUTED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_MUTENESS;

    static const std::string STATUS_MESSAGE_NPC_PARALYZED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_PARALYSIS;

    static const std::string STATUS_MESSAGE_NPC_SLOWED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_SLOWNESS;

    static const std::string STATUS_MESSAGE_NPC_HASTED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_HASTE;

    static const std::string STATUS_MESSAGE_NPC_STONE;
    static const std::string STATUS_MESSAGE_NPC_UNDO_STONE;

    static const std::string STATUS_MESSAGE_NPC_BLOODIED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_BLOODIED;

    static const std::string STATUS_MESSAGE_NPC_STUNNED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_STUNNED;

    static const std::string STATUS_MESSAGE_NPC_EXPOSED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_EXPOSED;

    static const std::string STATUS_MESSAGE_NPC_DISFIGURED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_DISFIGURED;

    static const std::string STATUS_MESSAGE_NPC_IMMOBILE;
    static const std::string STATUS_MESSAGE_NPC_UNDO_IMMOBILE;

    static const std::string STATUS_MESSAGE_NPC_BLINDED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_BLINDNESS;

    static const std::string STATUS_MESSAGE_NPC_INCORPOREAL;
    static const std::string STATUS_MESSAGE_NPC_UNDO_INCORPOREAL;

    static const std::string STATUS_MESSAGE_NPC_SATED;
    static const std::string STATUS_MESSAGE_NPC_UNDO_SATED;

    static const std::string STATUS_MESSAGE_NPC_WATER_BREATHING;
    static const std::string STATUS_MESSAGE_NPC_UNDO_WATER_BREATHING;

    static const std::string STATUS_MESSAGE_NPC_RAGE;
    static const std::string STATUS_MESSAGE_NPC_UNDO_RAGE;

    static const std::string STATUS_MESSAGE_NPC_HIDE;
    static const std::string STATUS_MESSAGE_NPC_HIDE_REVEAL;

    static const std::string STATUS_MESSAGE_NPC_DRUNK;
    static const std::string STATUS_MESSAGE_NPC_SOBER;

    static const std::string STATUS_MESSAGE_NPC_FLYING;
    static const std::string STATUS_MESSAGE_NPC_UNDO_FLYING;

    static const std::string STATUS_MESSAGE_NPC_TIMEWALK;
    static const std::string STATUS_MESSAGE_NPC_UNDO_TIMEWALK;

    static const std::string STATUS_FULL_BLIND;

    static std::map<std::string, std::string> status_id_sid;
};

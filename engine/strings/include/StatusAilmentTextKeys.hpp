#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

class Creature;

class StatusAilmentTextKeys
{
  public:
    // Hunger Keys:
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
    
    // Other status ailments:
    static const std::string STATUS_POISON;
    static const std::string STATUS_MESSAGE_PLAYER_POISONED;
    static const std::string STATUS_MESSAGE_PLAYER_POISON_CURED;
    static const std::string get_npc_poisoned_message(boost::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_poison_message(boost::shared_ptr<Creature> creature);

    static const std::string STATUS_MUTE;
    static const std::string STATUS_MESSAGE_PLAYER_MUTED;
    static const std::string STATUS_MESSAGE_PLAYER_MUTENESS_CURED;
    static const std::string get_npc_muted_message(boost::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_muteness_message(boost::shared_ptr<Creature> creature);

    static const std::string STATUS_PARALYSIS;
    static const std::string STATUS_MESSAGE_PLAYER_PARALYZED;
    static const std::string STATUS_MESSAGE_PLAYER_PARALYSIS_CURED;
    static const std::string get_npc_paralyzed_message(boost::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_paralysis_message(boost::shared_ptr<Creature> creature);

    static const std::string STATUS_SLOWNESS;
    static const std::string STATUS_MESSAGE_PLAYER_SLOWED;
    static const std::string STATUS_MESSAGE_PLAYER_SLOWNESS_CURED;
    static const std::string get_npc_slowed_message(boost::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_slowness_message(boost::shared_ptr<Creature> creature);

    static const std::string STATUS_HASTE;
    static const std::string STATUS_MESSAGE_PLAYER_HASTED;
    static const std::string STATUS_MESSAGE_PLAYER_HASTE_DONE;
    static const std::string get_npc_hasted_message(boost::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_haste_message(boost::shared_ptr<Creature> creature);

    static const std::string STATUS_STONE;
    static const std::string STATUS_MESSAGE_PLAYER_STONE;
    static const std::string STATUS_MESSAGE_PLAYER_STONE_CURED;
    static const std::string STATUS_MESSAGE_STONE_FINALIZE;
    static const std::string STATUS_MESSAGE_STONE_CRUMBLE;
    static const std::string get_npc_stone_message(boost::shared_ptr<Creature> creature);
    static const std::string get_npc_undo_stone_message(boost::shared_ptr<Creature> creature);

  protected:
    StatusAilmentTextKeys();
    ~StatusAilmentTextKeys();

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
};

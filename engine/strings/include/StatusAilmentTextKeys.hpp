#pragma once
#include <string>

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

    static const std::string STATUS_MUTE;
    static const std::string STATUS_MESSAGE_PLAYER_MUTED;
    static const std::string STATUS_MESSAGE_PLAYER_MUTENESS_CURED;

    static const std::string STATUS_PARALYSIS;
    static const std::string STATUS_MESSAGE_PLAYER_PARALYZED;
    static const std::string STATUS_MESSAGE_PLAYER_PARALYSIS_CURED;

  protected:
    StatusAilmentTextKeys();
    ~StatusAilmentTextKeys();
};

#pragma once
#include "MessageManager.hpp"
#include "NullMessageManager.hpp"

class Creature;

// The MessageTransmit values are intentionally kept short to keep the code
// neater.
enum struct MessageTransmit
{
  NONE = 0,
  SELF = 1,
  FOV = 2,
  MAP = 3
};

class MessageManagerFactory
{
  public:
    // Always get the real message manager
    static IMessageManager& instance();

    // Get the appropriate instance based on the creature details and the
    // message transmission type:
    //
    // If the message transmission type is MAP:
    // - Always return the real message manager
    //
    // If the message transmission type is FOV:
    // - Return the real message manager when the player is the creature or
    //   is in the creature's FOV.  
    // - Return the null message manager otherwise.
    //
    // If the message transmission type is SELF:
    // - Return the real message manager when the creature is the player.
    // - Return the null message manager otherwise.
    static IMessageManager& instance(const MessageTransmit mt, std::shared_ptr<Creature> creature, bool player_is_affected);

  protected:
    static MessageManager& mm_instance();
    static NullMessageManager& nmm_instance();
};

using MMF = MessageManagerFactory;


#pragma once

// An interface class that allows the player to "h"andle a particular
// feature.  Handling a door opens/shuts/unlocks it as appropriate.
// Handling a throne while on the square causes the player to sit.  etc.
class IHandleable
{
  public:
    virtual bool handle() = 0;
};

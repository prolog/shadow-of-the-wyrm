#pragma once

// An interface class that denotes that whatever it's attached to
// responds to kicking in some way.
class IKickable
{
  public:
    virtual bool kick() = 0;
};

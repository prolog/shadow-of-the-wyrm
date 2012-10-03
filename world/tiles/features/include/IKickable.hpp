#pragma once

// An interface class that denotes that whatever it's attached to
// responds to kicking in some way.
class IKickable
{
  public:
    IKickable() {};
    virtual ~IKickable() {};

    virtual bool kick() = 0;
};

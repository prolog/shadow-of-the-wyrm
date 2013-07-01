#pragma once
#include "StatusChange.hpp"

// StatusChangeFactory creates StatusChangePtrs for various status buffs/
// ailments based on the string identifier.  The identifiers correspond
// to those in world/include/StatusTypes.hpp, in class StatusIdentifier.
class StatusChangeFactory
{
  public:
    static StatusChangePtr create_status_change(const std::string& status_identifier);

  protected:
    StatusChangeFactory();
    ~StatusChangeFactory();
};


#pragma once
#include "IActionManager.hpp"

class VersionActionManager : public IActionManager
{
  public:
    void version() const;
    
  protected:
    uint get_current_action_cost() const;
};

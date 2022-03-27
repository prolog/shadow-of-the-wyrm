#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class OrderScreen : public Screen
{
  public:
    OrderScreen(DisplayPtr display, const bool new_followers_exist_in_fov, const bool new_can_summon);

  protected:
    void initialize() override;
    
    bool followers_exist_in_fov;
    bool can_summon;
};

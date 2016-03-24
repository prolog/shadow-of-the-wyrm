#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class HelpScreen : public Screen
{
  public:
    HelpScreen(DisplayPtr new_display);

  protected:
    void initialize() override;
};

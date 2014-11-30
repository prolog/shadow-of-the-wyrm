#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class WeavingSelectionScreen : public Screen
{
  public:
    WeavingSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

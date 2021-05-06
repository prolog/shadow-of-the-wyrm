#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class HairSelectionScreen : public Screen
{
  public:
    HairSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

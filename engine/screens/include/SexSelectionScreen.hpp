#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class SexSelectionScreen : public Screen
{
  public:
    SexSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

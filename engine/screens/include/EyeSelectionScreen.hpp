#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class EyeSelectionScreen : public Screen
{
  public:
    EyeSelectionScreen(DisplayPtr display, const std::string& synopsis);

  protected:
    void initialize() override;

    const std::string creature_synopsis;
};

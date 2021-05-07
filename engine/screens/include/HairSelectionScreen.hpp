#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class HairSelectionScreen : public Screen
{
  public:
    HairSelectionScreen(DisplayPtr display, const std::string& synopsis);

  protected:
    void initialize() override;

    const std::string creature_synopsis;
};

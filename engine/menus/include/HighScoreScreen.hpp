#pragma once
#include <string>
#include "Creature.hpp"
#include "Display.hpp"
#include "Menu.hpp"
#include "ScoreFile.hpp"

class HighScoreScreen : public Menu
{
  public:
    HighScoreScreen(DisplayPtr current_display, const std::vector<ScoreFileEntry>& sfe);

  protected:
    void initialize();

    std::vector<ScoreFileEntry> sfe;
};

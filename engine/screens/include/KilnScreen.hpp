#pragma once
#include <map>
#include <string>
#include "Screen.hpp"
#include "Display.hpp"

class KilnScreen : public Screen
{
  public:
    KilnScreen(DisplayPtr new_display, const bool fire_bombs, const std::string& fb_ingred, const bool shadow_bombs, const std::string& sb_ingred);

  protected:
    void initialize() override;

    bool allow_fire_bombs;
    bool allow_shadow_bombs;
    std::string fire_bomb_item_id;
    std::string shadow_bomb_item_id;
};

#pragma once
#include "Game.hpp"
#include "Deity.hpp"

class DeityUtils
{
  public:
    static DeityPtr get_random_deity(const Game& game);

  protected:
    DeityUtils();
    ~DeityUtils();
};


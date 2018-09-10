#pragma once
#include "Game.hpp"
#include "Deity.hpp"

class DeityUtils
{
  public:
    static std::pair<DeityPtr, AlignmentRange> get_random_deity_with_align(const Game& game);

  protected:
    DeityUtils();
    ~DeityUtils();
};


#pragma once
#include <string>

class MagicCommandKeys
{
  public:
    static const std::string SELECT_SPELL;
    static const std::string NEXT_PAGE;
    static const std::string PREVIOUS_PAGE;
    static const std::string EXIT_MAGIC;

  protected:
    MagicCommandKeys();
    ~MagicCommandKeys();
};

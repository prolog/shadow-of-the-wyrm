#pragma once
#include <string>

class CorpseTextKeys
{
  public:
    static std::string get_corpse_description(const std::string& creature_desc);

  protected:
    CorpseTextKeys();
    ~CorpseTextKeys();

    static const std::string CORPSE_MESSAGE;
};


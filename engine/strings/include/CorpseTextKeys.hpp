#pragma once
#include <string>

class CorpseTextKeys
{
  public:
    static std::string get_corpse_description(const std::string& creature_desc);
    static std::string get_skin_bones_description(const std::string& item_description, const std::string& creature_desc);

  protected:
    CorpseTextKeys();
    ~CorpseTextKeys();

    static const std::string CORPSE_MESSAGE;
	static const std::string SKIN_BONES_MESSAGE;
};


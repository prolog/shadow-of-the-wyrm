#pragma once
#include <string>
#include "common.hpp"

class PromptTextKeys
{
  public:
    static std::string get_appropriate_prompt_sid(const uint num_pages);

    static const std::string PROMPT_ANY_KEY;
    static const std::string PROMPT_ANY_KEY_PAGING;
    static const std::string PROMPT_SELECT_AN_OPTION;
    static const std::string PROMPT_ENTER_YOUR_NAME;
    static const std::string PROMPT_RUN_SCRIPT;
    static const std::string PROMPT_HELP;
    static const std::string PROMPT_SKILLS;
    static const std::string PROMPT_CREATE_ITEM;
    static const std::string PROMPT_ORDER;
    static const std::string PROMPT_EQUIPMENT;
    static const std::string PROMPT_INVENTORY;
    static const std::string PROMPT_INVENTORY_NO_SELECTION;
    static const std::string PROMPT_SKIN;
    static const std::string PROMPT_WEAVE;
    static const std::string PROMPT_KILN;

  protected:
    PromptTextKeys();
    ~PromptTextKeys();
};

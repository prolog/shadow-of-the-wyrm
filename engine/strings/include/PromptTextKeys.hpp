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

  protected:
    PromptTextKeys();
    ~PromptTextKeys();
};

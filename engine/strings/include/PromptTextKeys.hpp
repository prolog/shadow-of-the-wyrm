#pragma once
#include <string>

class PromptTextKeys
{
  public:
    static const std::string PROMPT_ANY_KEY;
    static const std::string PROMPT_ENTER_YOUR_NAME;
    static const std::string PROMPT_RUN_SCRIPT;

  protected:
    PromptTextKeys();
    ~PromptTextKeys();
};

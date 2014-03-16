#include "PromptTextKeys.hpp"

using namespace std;

// Prompts
PromptTextKeys::PromptTextKeys()
{
}

PromptTextKeys::~PromptTextKeys()
{
}

string PromptTextKeys::get_appropriate_prompt_sid(const uint num_pages)
{
  if (num_pages > 1)
  {
    return PROMPT_ANY_KEY_PAGING;
  }
  else
  {
    return PROMPT_ANY_KEY;
  }
}

const string PromptTextKeys::PROMPT_ANY_KEY = "PROMPT_ANY_KEY";
const string PromptTextKeys::PROMPT_ANY_KEY_PAGING = "PROMPT_ANY_KEY_PAGING";
const string PromptTextKeys::PROMPT_SELECT_AN_OPTION = "PROMPT_SELECT_AN_OPTION";
const string PromptTextKeys::PROMPT_ENTER_YOUR_NAME = "PROMPT_ENTER_YOUR_NAME";
const string PromptTextKeys::PROMPT_RUN_SCRIPT = "PROMPT_RUN_SCRIPT";

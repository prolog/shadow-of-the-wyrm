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
const string PromptTextKeys::PROMPT_HELP = "PROMPT_HELP";
const string PromptTextKeys::PROMPT_SKILLS = "PROMPT_SKILLS";
const string PromptTextKeys::PROMPT_CREATE_ITEM = "PROMPT_CREATE_ITEM";
const string PromptTextKeys::PROMPT_ORDER = "PROMPT_ORDER";
const string PromptTextKeys::PROMPT_EQUIPMENT = "PROMPT_EQUIPMENT";
const string PromptTextKeys::PROMPT_INVENTORY = "PROMPT_INVENTORY";
const string PromptTextKeys::PROMPT_INVENTORY_NO_SELECTION = "PROMPT_INVENTORY_NO_SELECTION";
const string PromptTextKeys::PROMPT_SKIN = "PROMPT_SKIN";
const string PromptTextKeys::PROMPT_WEAVE = "PROMPT_WEAVE";


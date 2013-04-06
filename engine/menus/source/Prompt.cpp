#include "Prompt.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

Prompt::Prompt(const PromptLocation prompt_location)
{
  type = PROMPT_TYPE_CHARACTER;
  location = prompt_location;
  initialize();
}

void Prompt::set_text_sid(const string& new_text_sid)
{
  text_sid = new_text_sid;
}

string Prompt::get_text_sid() const
{
  return text_sid;
}

string Prompt::get_text() const
{
  return StringTable::get(text_sid);
}

void Prompt::set_location(const PromptLocation new_location)
{
  location = new_location;
}

PromptLocation Prompt::get_location() const
{
  return location;
}

void Prompt::set_type(const PromptType new_type)
{
  type = new_type;
}

PromptType Prompt::get_type() const
{
  return type;
}

// This does all the work of setting up the prompt text, etc.
void Prompt::initialize()
{
  // Should be re-defined by all subclasses of prompt.
}

// AnyKeyPrompt

AnyKeyPrompt::AnyKeyPrompt() : Prompt(PROMPT_LOCATION_LOWER_RIGHT)
{
  initialize();
}

void AnyKeyPrompt::initialize()
{
  text_sid = PromptTextKeys::PROMPT_ANY_KEY;
}

// NullPrompt
NullPrompt::NullPrompt() : Prompt(PROMPT_LOCATION_LOWER_RIGHT)
{
  initialize();
}

void NullPrompt::initialize()
{
  text_sid = "";
}

// TextPrompt

TextPrompt::TextPrompt() : Prompt(PROMPT_LOCATION_DEFAULT)
{
  type = PROMPT_TYPE_TEXT;
}

void TextPrompt::initialize()
{
  // JCD REMOVE THIS LATER IF NOT USED
}

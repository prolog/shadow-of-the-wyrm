#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

enum PromptLocation
{
  PROMPT_LOCATION_DEFAULT = 0,
  PROMPT_LOCATION_LOWER_RIGHT = 1
};

enum PromptType
{
  PROMPT_TYPE_CHARACTER = 0,
  PROMPT_TYPE_TEXT = 1,
  PROMPT_TYPE_COMMAND = 2
};

class Prompt
{
  public:
    Prompt(const PromptLocation = PROMPT_LOCATION_DEFAULT);

    void set_text_sid(const std::string& new_prompt_text_sid);
    std::string get_text_sid() const;
    std::string get_text() const;

    void set_location(const PromptLocation new_location);
    PromptLocation get_location() const;

    void set_type(const PromptType new_type);
    PromptType get_type() const;

  protected:
    virtual void initialize();
    std::string text_sid;
    PromptLocation location;
    PromptType type;
};

class AnyKeyPrompt : public Prompt
{
  public:
    AnyKeyPrompt();

  protected:
    void initialize();
};

class TextPrompt : public Prompt
{
  public:
    TextPrompt();

  protected:
    void initialize();
};

typedef boost::shared_ptr<Prompt> PromptPtr;

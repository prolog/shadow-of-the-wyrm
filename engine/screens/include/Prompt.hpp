#pragma once
#include <string>
#include <memory>

enum struct PromptLocation
{
  PROMPT_LOCATION_DEFAULT = 0,
  PROMPT_LOCATION_LOWER_RIGHT = 1
};

enum struct PromptType
{
  PROMPT_TYPE_CHARACTER = 0,
  PROMPT_TYPE_TEXT = 1,
  PROMPT_TYPE_COMMAND = 2
};

class Prompt
{
  public:
    Prompt(const PromptLocation = PromptLocation::PROMPT_LOCATION_DEFAULT);

    void set_text_sid(const std::string& new_prompt_text_sid);
    std::string get_text_sid() const;
    std::string get_text() const;

    void set_location(const PromptLocation new_location);
    PromptLocation get_location() const;

    void set_type(const PromptType new_type);
    PromptType get_type() const;

    // Whether or not the input must be part of the range specified by the
    // screen.  Normally, this strict checking is what is desired.  For things
    // like the race/class selection screen, it doesn't make sense to pick
    // anything other than the options given.  But for in-game screens like
    // the spellcasting screen, where there are legitimate options that are
    // not in the screens ([z] to Exit, etc), the game should be more permissive,
    // and then delegate to the command processing mechanisms.
    void set_accept_any_input(const bool new_accept_any_input);
    bool get_accept_any_input() const;

  protected:
    virtual void initialize();
    std::string text_sid;
    PromptLocation location;
    PromptType type;
    bool accept_any_input;
};

class AnyKeyPrompt : public Prompt
{
  public:
    AnyKeyPrompt();

  protected:
    void initialize();
};

class NullPrompt : public Prompt
{
  public:
    NullPrompt();

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

typedef std::shared_ptr<Prompt> PromptPtr;

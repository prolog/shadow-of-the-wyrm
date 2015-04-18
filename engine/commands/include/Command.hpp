#pragma once
#include <map>
#include <string>
#include <memory>

class Command
{
  public:
    std::string get_name() const;

    virtual int get_key() const;

    virtual void set_custom_value(const std::string& key, const std::string& value);
    virtual std::string get_custom_value(const std::string& key) const;

    // Most commands can just check the existence of a command_confirmation
    // string, but some will need special logic.
    virtual bool requires_confirmation() const;
    std::string get_confirmation_sid() const;

  protected:
    friend class CommandFactory;
    Command(const std::string& name, int key);
    Command(const std::string& name, int key, const std::string& confirmation_text);
    virtual ~Command();

    std::string command_name;
    int key_pressed;
    std::string command_confirmation;
    std::map<std::string, std::string> custom_values;
};

typedef std::shared_ptr<Command> CommandPtr;

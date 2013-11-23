#pragma once
#include <string>
#include <memory>

class Command
{
  public:
    std::string get_name() const;
    
    // Most commands can just check the existence of a command_confirmation
    // string, but some will need special logic.
    virtual bool requires_confirmation() const;
    std::string get_confirmation_sid() const;

  protected:
    friend class CommandFactory;
    Command(const std::string& name);
    Command(const std::string& name, const std::string& confirmation_text);
    virtual ~Command();

    std::string command_name;
    std::string command_confirmation;
};

typedef std::shared_ptr<Command> CommandPtr;

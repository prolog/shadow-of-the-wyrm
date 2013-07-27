#pragma once
#include "Display.hpp"
#include "Messages.hpp"

// Defines the interface for the message managers.
class IMessageManager
{
  public:
    virtual ~IMessageManager() {};

    virtual void clear_if_necessary() = 0;
    virtual void send(const bool halt_afterwards = false, const bool reset_afterwards = false) = 0;
    virtual void send_and_halt() = 0;
    
		virtual bool add_new_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) = 0;
		virtual bool add_new_confirmation_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) = 0;
    virtual bool add_new_message_with_pause(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) = 0;
    virtual std::string add_new_message_with_prompt(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) = 0;
		
		virtual Messages get_unread_messages() const = 0;
		virtual Messages get_unread_messages_and_mark_as_read() = 0;

    virtual void set_display(DisplayPtr new_display) = 0;
};


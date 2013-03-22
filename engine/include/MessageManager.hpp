#pragma once
#include "Messages.hpp"
#include "Display.hpp"

class MessageManager
{
	public:
    static MessageManager& instance()
    {
      static MessageManager mm;
      return mm;
    }

    void clear_if_necessary();
    void send(const bool halt_afterwards = false, const bool reset_afterwards = false);
    void send_and_halt();
    
		bool add_new_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
		bool add_new_confirmation_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
    bool add_new_message_with_pause(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
    std::string add_new_message_with_prompt(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
		
		Messages get_unread_messages() const;
		Messages get_unread_messages_and_mark_as_read();

	private:
    std::string get_count_indicator(const Message& m);
    
    friend class SavageLandsEngine;
    MessageManager();
    MessageManager(const MessageManager&); // Do not implement!
    bool operator=(const MessageManager&); // Do not implement!
    ~MessageManager();

    void set_display(DisplayPtr new_display);

		Messages read;
		Messages unread;
		DisplayPtr user_display;
		bool buffer_has_messages;
};

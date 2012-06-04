#pragma once
#include "Messages.hpp"
#include "Display.hpp"

class MessageManager
{
	public:
    static MessageManager* instance();

    void clear_if_necessary();
    void send(const bool halt_afterwards = false);
    void send_and_halt();
		bool add_new_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
		Messages get_unread_messages() const;
		Messages get_unread_messages_and_mark_as_read();

	protected:
    friend class SavageLandsEngine;
    MessageManager();
    ~MessageManager();

    void set_display(DisplayPtr new_display);

		Messages read;
		Messages unread;
		DisplayPtr user_display;
		bool buffer_has_messages;

		static MessageManager* manager_instance;
};

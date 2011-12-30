#pragma once
#include "Messages.hpp"
#include "Display.hpp"

class MessageManager
{
	public:
    static MessageManager* instance();

    void send();
		bool add_new_message(const std::string& message, const MessageImportance& importance = MessageImportance_Normal);
		Messages get_unread_messages() const;
		Messages get_unread_messages_and_mark_as_read();

	protected:
    friend class SavageLandsEngine;
    ~MessageManager();

    void set_display(DisplayPtr new_display);

		Messages read;
		Messages unread;
		DisplayPtr user_display;

		static MessageManager* manager_instance;
};

#pragma once
#include "Messages.hpp"

class MessageManager
{
	public:
		bool add_new_message(const std::string& message, const MessageImportance& importance);
		Messages get_unread_messages() const;
		Messages get_unread_messages_and_mark_as_read();

	protected:
		Messages read;
		Messages unread;
};

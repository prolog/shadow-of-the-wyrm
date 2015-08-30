#pragma once

#include <vector>
#include "Message.hpp"

using MessageId = boost::uuids::uuid;

class Messages
{
	public:
		void add(const Message& message);
		std::vector<Message> get_messages() const;
		std::vector<Message>& get_messages_ref();
		void clear();
    bool empty() const;

	protected:
		std::vector<Message> messages;
};

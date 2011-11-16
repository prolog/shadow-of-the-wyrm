#pragma once

#include <vector>
#include "Message.hpp"

typedef boost::uuids::uuid MessageId;

class Messages
{
	public:
		void add(const Message& message);
		std::vector<Message> get_messages() const;
		void clear();

	protected:
		std::vector<Message> messages;
};

#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

enum MessageImportance
{
	MessageImportance_UNDEFINED = -1,
    MessageImportance_Normal = 0,
	MessageImportance_High = 1,
	MessageImportance_Critical = 2
};

class Message
{
	public:
		Message(const std::string& new_content, const MessageImportance& new_importance);

		void set_content(const std::string& new_content);
		std::string get_content() const;

		void set_importance(const MessageImportance& new_importance);
		MessageImportance get_importance() const;

		void set_id(const boost::uuids::uuid& new_id);
		boost::uuids::uuid get_id() const;

	private:
		std::string content;
		MessageImportance importance;
		boost::uuids::uuid id;
};

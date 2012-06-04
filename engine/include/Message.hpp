#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "Colours.hpp"

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
		Message(const std::string& new_content, const Colour colour, const MessageImportance& new_importance);

		void set_content(const std::string& new_content);
		std::string get_content() const;

    void set_colour(const Colour colour);
    Colour get_colour() const;
    
		void set_importance(const MessageImportance& new_importance);
		MessageImportance get_importance() const;

		void set_id(const boost::uuids::uuid& new_id);
		boost::uuids::uuid get_id() const;

	private:
		std::string content;
		Colour colour;
		MessageImportance importance;
		boost::uuids::uuid id;
};

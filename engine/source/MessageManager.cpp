#include <boost/foreach.hpp>
#include "Conversion.hpp"
#include "MessageManager.hpp"

using namespace std;

MessageManager* MessageManager::manager_instance = NULL;

MessageManager::MessageManager()
: buffer_has_messages(false)
{
}

MessageManager::~MessageManager()
{
}

// Get the singleton instance.
MessageManager* MessageManager::instance()
{
  if (manager_instance == NULL)
  {
    manager_instance = new MessageManager();
  }

  return manager_instance;
}

// Clear the display of any text.
void MessageManager::clear_if_necessary()
{
  if (buffer_has_messages)
  {
    get_unread_messages_and_mark_as_read();
    
    if (user_display)
    {
      user_display->clear_messages();
    }
    
    buffer_has_messages = false;
  }
}

// Send the currently-unread messages to the display.
void MessageManager::send(const bool halt_after, const bool reset_cursor_after)
{
  Messages unread_messages = get_unread_messages_and_mark_as_read();
  string message_text;
  
  if (user_display)
  {
    vector<Message> messages = unread_messages.get_messages();

    BOOST_FOREACH(Message m, messages)
    {
      message_text = m.get_content() + get_count_indicator(m) + " ";

      // Don't immediately clear, and only send text if the message buffer has something.
      if (!message_text.empty())
      {
        user_display->add_message(message_text, m.get_colour(), reset_cursor_after);
      }

      buffer_has_messages = true;
    }
  }
  
  if (halt_after)
  {
    user_display->halt_messages();
  }
}


void MessageManager::send_and_halt()
{
  send(true);
}

// Add a new message to the set of unread messages.
bool MessageManager::add_new_message
(
	const std::string& message_text
, const Colour colour
, const MessageImportance& importance
)
{
	Message message(message_text, colour, importance);
  boost::uuids::uuid id = boost::uuids::random_generator()();
	message.set_id(id);
	
	if (unread.empty())
	{
    unread.add(message);
	}
	else
	{
	  vector<Message>& messages = unread.get_messages_ref();
	  Message& last_message = messages[messages.size()-1];
	  
	  if (last_message.get_content() == message_text)
	  {
	    last_message.set_count(last_message.get_count()+1);
	  }
	  else
	  {
	    unread.add(message);
	  }
	}
	
	return true;
}

// This is a simpler method than add_new_message - it doesn't queue the message, and instead
// displays it directly.
bool MessageManager::add_new_confirmation_message
(
  const std::string& message_text
, const Colour colour
, const MessageImportance& importance
)
{
  buffer_has_messages = true;
  
	if (user_display)
	{
	  user_display->confirm(message_text);
	}

  return true;
}

// Get the current unread messages.
Messages MessageManager::get_unread_messages() const
{
	return unread;
}

// Get the current unread messages, and mark them as read by adding them
// to the list of read messages, and clearing the unread pile.
Messages MessageManager::get_unread_messages_and_mark_as_read()
{
	Messages unread_messages = get_unread_messages();
	unread.clear();
	return unread_messages;
}

void MessageManager::set_display(DisplayPtr new_display)
{
  user_display = new_display;
}

string MessageManager::get_count_indicator(const Message& m)
{
  string count_indicator;
  int count = m.get_count();

  if (count > 1)
  {
    count_indicator = " (x" + Integer::to_string(count) + ")"; 
  }
  
  return count_indicator;
}

#include <boost/foreach.hpp>
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

/*
 *********************************************************************

  Get the singleton instance.

 *********************************************************************/
MessageManager* MessageManager::instance()
{
  if (manager_instance == NULL)
  {
    manager_instance = new MessageManager();
  }

  return manager_instance;
}

/*
 ********************************************************************
 
  Clear the display of any text.
 
 ********************************************************************/
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

/*
 *********************************************************************

  Send the currently-unread messages to the display.

 *********************************************************************/
void MessageManager::send(const bool halt_after)
{
  Messages unread_messages = get_unread_messages_and_mark_as_read();
  string message_text;

  if (user_display)
  {
    vector<Message> messages = unread_messages.get_messages();

    BOOST_FOREACH(Message m, messages)
    {
      message_text = message_text + m.get_content() + " ";
      buffer_has_messages = true;
    }

    // Don't immediately clear, and only send text if the message buffer has something.
    if (!message_text.empty())
    {
      user_display->add_message(message_text, false);
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
/*
 *********************************************************************

 	Add a new message to the set of unread messages.

 *********************************************************************/
bool MessageManager::add_new_message
(
	const std::string& message_text
, const MessageImportance& importance
)
{
	Message message(message_text, importance);
	unread.add(message);

	return true;
}

/*
 **********************************************************************

 	Get the current unread messages.

 **********************************************************************/
Messages MessageManager::get_unread_messages() const
{
	return unread;
}

/*
 ***********************************************************************

 	Get the current unread messages, and mark them as read by adding them
	to the list of read messages, and clearing the unread pile.

 ***********************************************************************/
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

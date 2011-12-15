#include "MessageManager.hpp"

MessageManager* MessageManager::manager_instance = NULL;

MessageManager::~MessageManager()
{
}

/*
 *********************************************************************

  Get the singleton instance.

 *********************************************************************/
MessageManager* MessageManager::get_instance()
{
  if (manager_instance == NULL)
  {
    manager_instance = new MessageManager();
  }

  return manager_instance;
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

#include "NullMessageManager.hpp"

void NullMessageManager::clear_if_necessary()
{
}

void NullMessageManager::send(const bool halt_afterwards, const bool reset_afterwards)
{
}

void NullMessageManager::send_and_halt()
{
}
    
bool NullMessageManager::add_new_message(const std::string& message, const Colour colour, const MessageImportance& importance)
{
  return false;
}

bool NullMessageManager::add_new_confirmation_message(const std::string& message, const Colour colour, const MessageImportance& importance)
{
  return false;
}

bool NullMessageManager::add_new_message_with_pause(const std::string& message, const Colour colour, const MessageImportance& importance)
{
  return false;
}

std::string NullMessageManager::add_new_message_with_prompt(const std::string& message, const Colour colour, const MessageImportance& importance)
{
  std::string no_msg;
  return no_msg;
}
		
Messages NullMessageManager::get_unread_messages() const
{
  Messages empty;
  return empty;
}

Messages NullMessageManager::get_unread_messages_and_mark_as_read()
{
  return get_unread_messages();
}

void NullMessageManager::set_display(DisplayPtr display)
{
}
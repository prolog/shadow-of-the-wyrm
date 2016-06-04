#include "NullMessageManager.hpp"

using namespace std;

void NullMessageManager::clear_if_necessary()
{
}

void NullMessageManager::send(const MessageSpacing ms, const bool halt_afterwards, const bool reset_afterwards)
{
}

void NullMessageManager::send_and_halt()
{
}

void NullMessageManager::alert(const string& message)
{
}

void NullMessageManager::alert_text(const string& message)
{
}

bool NullMessageManager::add_new_message(const string& message, const Colour colour, const MessageImportance& importance)
{
  return false;
}

bool NullMessageManager::add_new_confirmation_message(const string& message, const Colour colour, const MessageImportance& importance)
{
  return false;
}

bool NullMessageManager::add_new_message_with_pause(const string& message, const Colour colour, const MessageImportance& importance)
{
  return false;
}

std::string NullMessageManager::add_new_message_with_prompt(const string& message, const Colour colour, const MessageImportance& importance)
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

void NullMessageManager::set_message_buffer(const MessageBuffer& new_message_buffer)
{
}

MessageBuffer NullMessageManager::get_message_buffer() const
{
  MessageBuffer mb;
  return mb;
}